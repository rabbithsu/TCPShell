#include <stdio.h>
#include "md5.h"

char *s3cr3t = "22a4d9b04fe95c9893b41e2fde83a427";//"bd1733f3b772d18d2ea42da6109bcd78";

int main(){
	printf("Enter: ");
	char *pass;
	char inputp[10];
	scanf("%10s", inputp);
	pass = findmd5(inputp);
	printf("%s", pass);
	if( strcmp(s3cr3t, pass)== 0){
		printf("Pass!");
		char *p = "/bin/sh";
		execl(p, p, NULL);
	}
	else{
		printf("Reject!");
	}
	return 0;
}
