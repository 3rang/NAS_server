/**************************************************
*File Name   :- server.c
*description :- UDP server end for getting data and
*               store in file 
*Date        :- 19-Sep-2020
*Author      :- Tarang
**************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include<strings.h>
#include<sys/types.h>


#define BUFF_SIZE 100
#define PATH "/home/pi/sambashare/myfile.txt"
#define IP "0.0.0.0"
#define PORT 3333


int main (int argc,char **argv)
{
	
	if (argc != 2)
	{
		printf("Error: in input Ex:- ./server msgcount\n");
		return 0;
	}
    struct sockaddr_in udpSocket,udpBase;
    char buFFer[BUFF_SIZE];
    FILE *fp;
    int sfd,len,ret;
    static int coUnt=0;

    fp=fopen(PATH,"w");
	
	if(fp == NULL)
	{
		printf("Error in File opening..\n");
		return 0;
	}	


    sfd=socket(AF_INET,SOCK_DGRAM,0);
    if (sfd<0) {
        perror("socket");
        return 1;
    }
    perror("socket");

    udpSocket.sin_family=AF_INET;
    udpSocket.sin_port=htons(PORT);
    udpSocket.sin_addr.s_addr=inet_addr(IP);

    len=sizeof(udpSocket);
    bind (sfd,(struct sockaddr *)&udpSocket,len);
    perror("bind");
    while(coUnt<atoi(argv[1])) {
        ret = recvfrom(sfd,buFFer,sizeof(buFFer),0,(struct sockaddr *)&udpBase,&len);
	fprintf (fp,"%s\n",buFFer);
        printf ("ret = %d\ndata:%s\n", ret, buFFer);
	coUnt++;
    }
    fclose(fp);
}
