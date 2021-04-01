
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

void pr( char *str)
{
char buf1[50];
//Vulnerable function: buf1[50] <-- str[2000]
strcpy(buf1,str);
}

int main(int argc,char *argv[])
{
	struct sockaddr_in local;
	int s;
	int s1;
	int rc;
	char buf[2000]="";
	local.sin_family=AF_INET;
	//Listen port - 505 by default
	local.sin_port=htons(505);
	local.sin_addr.s_addr=htonl(INADDR_ANY);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	err = WSAStartup (wVersionRequested, &wsaData);
    s=socket(AF_INET, SOCK_STREAM, 6);
	if (s < 0)
		{
			perror("socket error");
			exit(1);
		}
	rc=bind(s,(struct sockaddr *)&local, sizeof(local));
	if (rc < 0)
		{
			perror("bind error");
			exit(1);
		}
	rc=listen(s,5);
    puts("Server started, use CTRL+C to terminate");
    s1 = accept(s, NULL, NULL);
	rc=send (s1, "Welcome...\n", 11, 0);
	rc = recv( s1, buf, 2000, 0 );
	pr(buf);
	rc=send (s1, "By", 2, 0);
    WSACleanup();
	exit(0);
}
