#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
    struct sockaddr_in clientaddr,serveraddr;
    int serversock,newserversock,n,portnum;
    socklen_t clientsize;
    char fileContent[50],buffer[50],outputFilename[50];
    fflush(stdin);
    serversock=socket(AF_INET,SOCK_STREAM,0);
    char *pdf_extension, *png_extension;

    portnum = atoi(argv[1]);
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(portnum);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(serversock,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(serversock,5);
    FILE *fp;
	clientsize= sizeof(clientaddr);
    newserversock=accept(serversock,(struct sockaddr*)&clientaddr,&clientsize);
    
    read(newserversock,buffer,100);
    strcpy(outputFilename,buffer);
    printf("\nOutput filename = %s \n",outputFilename);
    fp = fopen(outputFilename,"ab");
    bzero(fileContent,50);
    n=read(newserversock,fileContent,10);
    pdf_extension = strstr(outputFilename,"pdf");
    png_extension = strstr(outputFilename,"png");
    while(n>0)
    {
        if(pdf_extension == NULL && png_extension == NULL)
        {
            printf("Data received from client = %s \n",fileContent);
        }
        fwrite(fileContent,5,2,fp);
        bzero(fileContent,50);
        n=read(newserversock,fileContent,10);
    }
	
    printf("File was received successfully\n");
	printf("New file created is %s\n",outputFilename);        
	close(serversock);
    close(newserversock);
}


