#include<stdio.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
void client_info(struct sockaddr_in t)
{
	printf("%d\n",t.sin_family);
	printf("%d\n",t.sin_port);
	printf("%s\n",inet_ntoa(t.sin_addr));
}
void main(int argc ,char ** argv)
{
	int skd,askd,slen,clen,i=0,j=0;
	char ch[20],t;
	struct sockaddr_in server_id;
	skd=socket(AF_INET,SOCK_STREAM,0);
	if(skd<0)
	{
		perror("socket");
		return;
	}
	perror("socket");
	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(atoi(argv[1]));
	server_id.sin_addr.s_addr=inet_addr("127.0.0.1");
	slen=sizeof(server_id);
	if(bind(skd,(struct sockaddr *)&server_id,slen)<0)
	{
		perror("bind");
		return;
	}
	perror("bind");
	if(listen(skd,5)<0)
	{
		perror("listen");
		return;
	}
	perror("listen");
	printf("waiting for client request\n");
	struct sockaddr_in client_id;
	askd=accept(skd,(struct sockaddr *)&client_id,&slen);
	if(askd<0)
	{
		perror("accept");
		return;
	}
	perror("accept");
	client_info(client_id);
	while(1)
	{
	read(askd,&ch,sizeof(ch));
	perror("read");
	printf("%s\n",ch);
	for(i=0,j=strlen(ch)-1;i<j;i++,j--)
	{
		t=ch[i];
		ch[i]=ch[j];
		ch[j]=t;
	}
	write(askd,&ch,strlen(ch)+1);
	perror("write");
	}

}


