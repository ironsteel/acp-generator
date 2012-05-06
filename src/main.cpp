#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include "ACPFile.h"

using namespace std;

namespace acpgen 
{
    enum filetype 
    {
        DIR,
        FILE,
        UNKNOWN
    };
    
}

unsigned int get_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    
    long size = ftell(file);
    
    fseek(file, 0, SEEK_SET);
    
    return size;
}

/* Simple file type check routine */
acpgen::filetype get_type(string& path)
{
    struct stat buf;
    
    if(stat(path.c_str(), &buf) != 0) {
        return acpgen::UNKNOWN;
    }
    
    
    if(S_ISDIR(buf.st_mode)) {
        return acpgen::DIR;
    } else {
        return acpgen::FILE;
    }
}


vector<string> list_files(DIR *dir, const char *base_path)
{
    struct dirent *dp;
    vector<string> files; 
    
    while ((dp = readdir(dir)) != NULL) {
        string filename = dp->d_name;
        filename = base_path + filename;
        
        /* We are interested only in regular files */
        if(get_type(filename) == acpgen::FILE) {
            files.push_back(filename);
        } 
    }
    
    closedir(dir);
    return files;
}

ACPFile *generate_acp_archive(vector<string> &files)
{
    ACPFile *archive = new ACPFile;
    
    FILE *file; 
    
    void *buffer;
    
    unsigned int size;
    
    for(int i = 0; i < files.size(); ++i) {
        
        string filename = files.at(i);
        
        file = fopen(filename.c_str(), "rb");
        size = get_size(file);
        buffer = malloc(size);
        
        fread(buffer, size, sizeof(char), file);
        
        string name = filename.substr(filename.find_last_of('/') + 1, filename.size());
        
        archive->createChunk()->load(name.c_str(), buffer, size);
        fclose(file);
    }
    
    return archive;
}

void print_usage(const char *executable)
{
    cout << "Usage: " << executable <<" [directory] [outfile]" << endl;
}

int main(int argc, char *argv[]) 
{
    if(argc < 3) {
        print_usage(argv[0]);
        return 1;
    }
   
    DIR *dir = opendir(argv[1]);
    
    if(dir == NULL) {
        cout << "Cannot open directory" << endl;
        return 1;
    }
    
    vector<string> files = list_files(dir, argv[1]);
    
    for(int i = 0; i < files.size(); i++) {
        cout << files.at(i) << endl;
    }
    
    ACPFile *acp_archive = generate_acp_archive(files);
    
    acp_archive->save(argv[2]);
    
    delete acp_archive;
    
    return 0;
}




