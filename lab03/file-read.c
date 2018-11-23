#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    int fd;
    size_t size;
    char buffer[15]; //block to read = 14+1
    char filename[] = "myfile.txt";

    if((fd = open(filename,O_RDONLY)) < 0)
    {
        printf("Can\'t open file\n");
        exit(-1);
    }
    while((size = read(fd,buffer,14))>0)
    {
        buffer[size]=0;
        fputs(buffer,stdout);
    }

    if(close(fd) < 0)
    {
        printf("Can\'t close file\n");
    }

	return 0;
} 