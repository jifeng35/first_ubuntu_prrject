//
// Created by lee on 2022/3/31.
//
/*
 * 程序名：book245.cpp，此程序用于演示用C语言的方法封装socket客户端
 * 作者：C语言技术网(www.freecplus.net) 日期：20190525
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// TCP客户端连服务端的函数，serverip-服务端ip，port通信端口
int connecttoserver(const char *serverip,const int port);

int main()
{
    // 向服务器发起连接请求
    int sockfd=connecttoserver("118.89.50.198",5051);
    if (sockfd<=0) { printf("连接服务器失败，程序退出。\n"); return -1; }

    char strbuffer[1024];

    // 与服务端通信，发送一个报文后等待回复，然后再发下一个报文。
    for (int ii=0;ii<10;ii++)
    {
        memset(strbuffer,0,sizeof(strbuffer));
        sprintf(strbuffer,"这是第%d个超级女生，编号%03d。",ii+1,ii+1);
        if (send(sockfd,strbuffer,strlen(strbuffer),0)<=0) break;
        printf("发送：%s\n",strbuffer);

        memset(strbuffer,0,sizeof(strbuffer));
        if (recv(sockfd,strbuffer,sizeof(strbuffer),0)<=0) break;
        printf("接收：%s\n",strbuffer);
    }

    close(sockfd);
}

// TCP客户端连服务端的函数，serverip-服务端ip，port通信端口
// 返回值：成功返回已连接socket，失败返回-1。
int connecttoserver(const char *serverip,const int port)
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0); // 创建客户端的socket

    struct hostent* h; // ip地址信息的数据结构
    if ( (h = gethostbyname(serverip)) == 0 )
    { perror("gethostbyname"); close(sockfd); return -1; }

    // 把服务器的地址和端口转换为数据结构
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    memcpy(&servaddr.sin_addr,h->h_addr,h->h_length);

    // 向服务器发起连接请求
    if (connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)) != 0)
    { perror("connect"); close(sockfd); return -1; }

    return sockfd;
}