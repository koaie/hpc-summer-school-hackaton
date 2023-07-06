#include <stdio.h>
#include <stdlib.h>
 
#define FILENAME "test.txt"
 
char* allocate_buffer_of(size_t length)
{
    return (char*)malloc(sizeof(char) * length);
}
 
int main(int argc, char* argv[])
{
    FILE* f = fopen(FILENAME, "r");
    if(f == NULL)
    {
        printf("The file loading failed.\n");
    }
    fseek(f, 0L, SEEK_END);
    size_t file_size = ftell(f);
    char* buffer = allocate_buffer_of(file_size + 1);
    buffer[file_size] = '\0';
 
    fseek(f, 0L, SEEK_SET);
    fread(buffer, 1, file_size, f);
 
    printf("Content of the file:\n%s", buffer);
 
    fclose(f);
 
    return EXIT_SUCCESS;
}