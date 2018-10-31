#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "unistd.h"
#include "netinet/in.h"
#include "netdb.h"

int main(int argc,char *argv[])
{
        int sockfd,new_fd;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        int sin_size,portnumber;
        char hello[]="Hello! Are You Fine? ";

        if ( argc!=2 )  {
                fprintf(stderr,"Usage:%s portnumbera ",argv[0]);
                exit(1);
        }

        if((portnumber=atoi(argv[1]))<0)  {
                fprintf(stderr,"Usage:%s portnumbera ",argv[0]);
                exit(1);
        }


        /* 服务器端开始建立socket描述符 */ 
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)  {
                fprintf(stderr,"Socket error:%s a",strerror(errno));
                exit(1);
        }

        /* 服务器端填充 sockaddr结构 */ 
        bzero(&server_addr,sizeof(struct sockaddr_in)); 
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        server_addr.sin_port=htons(portnumber);

        /* 捆绑sockfd描述符 */ 
        if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)  {
                fprintf(stderr,"Bind error:%s a",strerror(errno));
                exit(1);
        }

        /* 监听sockfd描述符 */ 
        if(listen(sockfd,5)==-1)  {
                fprintf(stderr,"Listen error:%s a",strerror(errno));
                exit(1);
        }

        while(1)  {
                /* 服务器阻塞,直到客户程序建立连接 */ 
                sin_size=sizeof(struct sockaddr_in);
                if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)  {
                        fprintf(stderr,"Accept error:%s a",strerror(errno));
                        exit(1);
                }
                fprintf(stderr,"Server get connection from %s ",inet_ntoa(client_addr.sin_addr));
                if(write(new_fd,hello,strlen(hello))==-1)  {
                        fprintf(stderr,"Write Error:%s ",strerror(errno));
                        exit(1);
                }
                close(new_fd);
        }
        close(sockfd);
        exit(0);
}
