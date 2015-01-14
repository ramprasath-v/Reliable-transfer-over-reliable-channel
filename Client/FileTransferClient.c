#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
    struct sockaddr_in serveraddr;
    int clientsock,n,portno;
    char inputFilename[50],outputFilename[50], buffer[50];
    bzero((char*)&serveraddr,sizeof(serveraddr));
    char *pdf_extension, *png_extension;
    
    portno = atoi(argv[1]); 
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port= htons(portno);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    clientsock=socket(AF_INET,SOCK_STREAM,0);
    if(connect(clientsock,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
    {
        printf("\nError:Cannot connect...");
        exit(0);
    }
    
    FILE *fp;
    printf("Enter the name of the input file = ");
    scanf("%s",inputFilename);
    printf("Enter the name of the output file = ");
    scanf("%s",outputFilename);
    printf("Filename =  %s\n", inputFilename);
    
    write(clientsock,outputFilename, sizeof (outputFilename));
    fp=fopen(inputFilename,"rb");
    pdf_extension = strstr(outputFilename,"pdf");
    png_extension = strstr(outputFilename,"png");

    if(fp==NULL)
    {
        perror("Error in opening file");
        return(-1);
    }
    else
    {
        while(!feof(fp))
        {
            bzero(buffer,50);
            n = fread(buffer, 10, 1, fp);
            if(n>0)
            {
                write(clientsock,buffer,10);
                if(pdf_extension == NULL && png_extension == NULL)
                {
                    printf("Data sent to server = %s \n",buffer);
                }
            }
        }
    }
    printf("\nFile was sent successfully\n");
    close(clientsock);
    fclose(fp);
    return 0;
        
}
