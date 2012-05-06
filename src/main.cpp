#include <iostream>
#include "ACPFile.h"
#include <unistd.h>
#include <stdio.h>

unsigned int get_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    
    long size = ftell(file);
    
    fseek(file, 0, SEEK_SET);
    
    return size;
}

int main(int argc, char **argv) 
{
    ACPFile file;
    
    
    

    FILE* material  = fopen("/home/rangeli/sources/acp-generator/Sinbad.mesh", "rb");

    unsigned int size = get_size(material);
    
    void* buffer = malloc(size);
    
    fread(buffer, size, sizeof(char), material);
    
    file.createChunk()->load("Sinbad.mesh", buffer, size);
    
    fclose(material);
    
    material = fopen("/home/rangeli/sources/acp-generator/Sinbad.skeleton", "rb");
    
    size = get_size(material);
    
    buffer = malloc(size);
    
    fread(buffer, size, sizeof(char), material);
    
    file.createChunk()->load("Sinbad.skeleton", buffer, size);
    
    file.save("/home/rangeli/sources/acp-generator/Sinbad.mp3");
    
    
    
    ACPFile acpFile;
    acpFile.load("/home/rangeli/sources/acp-generator/Sinbad.mp3");
    
    size_t chunks = acpFile.getChunkCount();

    std::cout << chunks << std::endl;

    
    return 0;
}




