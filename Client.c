#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main()
{
	//SOCKET
	int a=socket(AF_INET,SOCK_DGRAM,0);
	if(a==-1)
	{
		printf("\nSocket ERROR");
	}

	//BIND
	struct sockaddr_in Client;
	Client.sin_family=AF_INET;
	Client.sin_port=htons(5000);
	Client.sin_addr.s_addr=inet_addr("127.0.0.1");
	int b=bind(a,(const struct sockaddr *)(&Client),sizeof(Client));
	if(b==-1)
	{
		printf("\nBind ERROR");
	}

	while(1)
	{
		char str[100];
		printf("\nEnter Message to Send (MAX 100) (Type X to Close):");
		scanf("%s",str);
		if(strcmp(str,"X")==0)
		{
			break;
		}

		//SENDTO
		struct sockaddr_in Server;
		Server.sin_family=AF_INET;
		Server.sin_port=htons(5050);
		Server.sin_addr.s_addr=inet_addr("127.0.0.1");
		sendto(a,str,strlen(str),0,(const struct sockaddr *)(&Server),sizeof(Server));

		//RECEIVEFROM
		char str1[100];
		recvfrom(a,str1,sizeof(str1),0,(struct sockaddr *)(&Server),(int *)sizeof(Server));
		printf("\nReceived:%s",str1);
	}

	//CLOSE
	close(a);
	return 0;
}
