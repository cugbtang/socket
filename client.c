#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "unistd.h"
#include "netinet/in.h"
#include "netdb.h"

int main(int argc, char *argv[])
{
        int sockfd;
        char buffer[1024];
        struct sockaddr_in server_addr;
        struct hostent *host;
        int portnumber,nbytes;

        if(argc!=3) {
                fprintf(stderr,"Usage:%s hostname portnumbera ",argv[0]);
                exit(1);
        }

        if((host=gethostbyname(argv[1]))==NULL) {
                fprintf(stderr,"Gethostname error ");
                exit(1);
        }

        if((portnumber=atoi(argv[2]))<0) {
                fprintf(stderr,"Usage:%s hostname portnumbera ",argv[0]);
                exit(1);
        }

        /*客户程序开始建立 sockfd描述符*/
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) {
                fprintf(stderr,"Socket Error:%sa ",strerror(errno));
                exit(1);
        }

        /*客户程序填充服务端的资料*/
        bzero(&server_addr,sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(portnumber);
        server_addr.sin_addr=*((struct in_addr *)host->h_addr);

        /*客户程序发起连接请求*/
        if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) {
                fprintf(stderr,"Connect Error:%sa ",strerror(errno));
                exit(1);
        }

        if((nbytes=read(sockfd,buffer,1024))==-1) {
                fprintf(stderr,"Read Error:%s ",strerror(errno));
                exit(1);
        }
        buffer[nbytes]='';
        printf("I have received:%s ",buffer);
        close(sockfd);
        exit(0);
}
