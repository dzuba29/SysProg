#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int fd[2];
    int fd1[2];
    pid_t forked_pid;
    pid_t pid;
    pid_t temp1,temp2;

    //pipes
    if(pipe(fd) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    if(pipe(fd1) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }

    //fork
    forked_pid = fork();
    pid = getpid();
    if (forked_pid == -1) 
    {   
        printf("Error fork\n");
        exit(-1);
    }
    else if (forked_pid == 0) 
    {   
        //Child proc
            //pipe 1
        close(fd[1]);
        read(fd[0],&temp2,sizeof(pid_t));
        printf("Iam CHILD,my pid =%d , get from PARENT pid = %d\n", (int)pid,(int)temp2); 
        close(fd[0]);
            //pipe 2
        close(fd1[0]);
        write(fd1[1],&pid,sizeof(pid_t));
        close(fd1[1]);
        exit(0);
    
    } 
    else 
    {
        //Parent proc
            //pipe1
        close(fd[0]);
        write(fd[1],&pid,sizeof(pid_t));
        close(fd[1]);
        wait(0);
            //pipe2
        close(fd1[1]);
        read(fd1[0],&temp1,sizeof(pid_t));
        printf("Iam PARENT,my pid =%d, get from CHILD pid = %d\n",(int)pid ,(int)temp1); 
        close(fd1[0]);


    }

    return 0;
} 