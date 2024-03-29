#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
using namespace std; 
#define PORT    6000
#define MAXLINE 65535
 
int main() {
    int sockfd;

    struct sockaddr_in servaddr, cliaddr;
     
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
     
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
     
    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.0.103");		
    servaddr.sin_port = htons(PORT);
     
    
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }


    int len;
    ofstream outfile;
    char fileNameChar[256];
    char buffer[MAXLINE];

    len = recvfrom(sockfd, fileNameChar , 256, MSG_WAITALL, ( struct sockaddr *) &cliaddr, (socklen_t*)&len);
    len = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, (socklen_t*)&len);
	
    string fileName(fileNameChar);

    outfile.open( fileName , ios::out | ios::binary);

    outfile.write( buffer , len );

    cout<<"File Received"<<endl;
    outfile.close();
    return 0;
}
