#include <stdio.h>
//#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "csapp.h"


int main(int argc,char **argv){

    printf("Hello World!\n");
    printf("Hello World!\n");

//    return 0;
}

//int fd1,fd2;
//fd1 = Open("foo.txt",O_RDONLY,0);
//printf("fd1:%d\n",fd1);
//Close(fd1);
//fd2 = Open("baz.txt",O_RDONLY,0);
//printf("fd2:%d\n",fd2);
//exit(0);

//char c;
//while(Read(STDIN_FILENO,&c,1) != 0)
//Write(STDOUT_FILENO,&c,1);
//
//exit(0);


// ***************查询并处理文件的st_mode位***************
//struct stat stat;
//char *type, *readok;
//
//Stat(argv[1],&stat);
//if (S_ISREG(stat.st_mode))
//type = "regular";
//else if (S_ISDIR(stat.st_mode))
//type = "directory";
//else
//type = "other";
//
//if ((stat.st_mode & S_IRUSR))
//readok = "yes";
//else
//readok = "no";
//
//printf("type:%s,read:%s\n",type,readok);


// ***********************遍历目录中的文件，并打印文件类型******************
//DIR *streamp;
//struct dirent *dep;
//errno = 0;
//char *type;
//struct stat stat;
//
//streamp = Opendir(argv[1]);
//
//while((dep = readdir(streamp)) != NULL){
//Stat(dep->d_name,&stat);
//if (S_ISREG(stat.st_mode))
//type = "regular";
//else if (S_ISDIR(stat.st_mode))
//type = "directory";
//else
//type = "other";
//printf("Found file:%s,type:%s\n",dep->d_name,type);
//}
//if (errno != 0)
//unix_error("readdir error");
//Closedir(streamp);
//
//exit(0);

//************************IP地址十六进制转点分十进制************************
//printf("IP address:%s\n",argv[1]);
//
//const char *hexstring = argv[1];
//int number = (int)strtol(hexstring, NULL, 0);
//int big_endian_number = htonl(number);
//
//char *dst;
//const char *result;
//struct in_addr inaddr;
//inaddr.s_addr = big_endian_number;
//if(!inet_ntop(AF_INET,&inaddr,dst,MAXBUF))
//unix_error("inet_ntop");
//
//printf("Number:%s\n",dst);


//************************IP地址分十进制转十六进制************************
//struct in_addr inaddr;
//int success = inet_pton(AF_INET,argv[1],&inaddr);
//int number = ntohl(inaddr.s_addr);
//printf("IP address:%#x\n",number);
