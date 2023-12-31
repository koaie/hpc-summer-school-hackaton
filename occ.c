#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 

#define FILENAME "test.txt"
 
char* allocate_buffer_of(size_t length)
{
    return (char*)malloc(sizeof(char) * length);
}
 
int main(int argc, char* argv[])
{
    double start = omp_get_wtime();
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
   
   size_t line_count = 0;
   int i =0;
   #pragma omp parallel for default(none) firstprivate(buffer,file_size) reduction(+:line_count)   
   for(int i= 0; i < file_size; i++)
   	{
	if (buffer[i] == '\n')
		{
		line_count += 1;
		}
	}
 
    fclose(f);
    double end = omp_get_wtime();
    printf("time to run: %f\n",end-start);
    return EXIT_SUCCESS;
}
