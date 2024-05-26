#include<stdio.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main()
{
	int skd,slen;
	char ch[20];
	skd=socket(AF_INET,SOCK_STREAM,0);
	if(skd<0)
	{
		perror("socket");
		return;
	}
	perror("socket");
	struct sockaddr_in server_id;
	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(3000);
	server_id.sin_addr.s_addr=inet_addr("127.0.0.1");
	slen=sizeof(server_id);
	if(connect(skd,(struct sockaddr *)&server_id,slen)<0)
	{
		perror("connect");
		return;
	}
	perror("connect");
	while(1)
	{
	printf("enter data\n");
	scanf("%s",ch);
	write(skd,&ch,strlen(ch)+1);
	perror("write");
	read(skd,&ch,sizeof(ch));
	perror("read");
	printf("%s\n",ch);
	}

}
