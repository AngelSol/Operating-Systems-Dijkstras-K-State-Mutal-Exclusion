//Angel Solis 5000220181
//CS 370 project6
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

int clientcreator(char*sockname);
int servercreator(char*sockname);
void bottom_algorithm(int id, int n);
void middle_algorithm(int id, int n);
void top_algorithm(int id, int n);


int main()
{
	int n,id;
	scanf("%d",&id);
	scanf("%d",&n);

	
	if (id==0)
		bottom_algorithm(id,n);
	else if(id == n-1)
		top_algorithm(id,n);
	else
		middle_algorithm(id,n);
}

int clientcreator(char*sockname)
{
	int cdescriptor;
	cdescriptor = socket(AF_UNIX, SOCK_STREAM,0);
	if (cdescriptor <0)
	{
		printf("Error creating socket %s\n",sockname);
		return -1;
	}
	
	struct sockaddr_un address;
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, sockname);
	unsigned int addressLength = sizeof(address);
	if (connect (cdescriptor, (struct sockaddr*) &address, addressLength)<0)
	{
		printf("Error connecting socket %s\n",sockname);
		return -1;
	}
	return cdescriptor;
	
}
int servercreator(char*sockname)
{
	int sdescriptor;
	sdescriptor = socket(AF_UNIX, SOCK_STREAM,0);
	if (sdescriptor <0)
	{
		printf("Error connecting socket %s\n",sockname);
		return -1;
	}
	
	struct sockaddr_un address;
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, sockname);
	unsigned int addressLength = sizeof(address);
	
	unlink(sockname);
	
	if (bind(sdescriptor,(struct sockaddr*) &address, addressLength)<0)
	{
		printf("Error binding socket\n");
		return -1;
	}
	
	if (listen(sdescriptor,1)<0)
	{
		printf("Error listening to socket\n");
		return -1;
	}
	int connecteddescr;
	connecteddescr= accept(sdescriptor, (struct sockaddr*) &address, &addressLength);
	if (connecteddescr<0)
	{
		printf("Error accepting socket connection\n");
		return -1;
	}	
	return connecteddescr;
}
void bottom_algorithm(int id, int n)
{
	int rightclient, leftclient, lvalue;
	int value = rand()%n;
	
		//create server to right
		rightclient = servercreator("out");
		//printf("right connected\n");
		
		//create sever to left
		leftclient = servercreator("around");
		//printf("left connected\n");
	while(1)
	{

		recv(leftclient,&lvalue,sizeof(int),0);
		send(rightclient,&value,sizeof(int),0);
		
		if (lvalue == value)
		{
			printf("##################################\n");
			printf("	 In Critical Section\n");
			printf("##################################\n");
			
			value= (value+1)%n;
			//sleep(1);
		}
		else 
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		
		
	}
	
}
void middle_algorithm(int id, int n)
{
	int right, left, lvalue;
	int value = rand()%n;
	
		
		//create client left
		left = clientcreator("out");
		//printf("leftconnect\n");
		
		
		
		//create server to right
		right = servercreator("out");
		//printf("rightconnect\n");
		
	while(1)
	{
		recv(left,&lvalue,sizeof(int),0);
		send(right,&value,sizeof(int),0);
		
		if (lvalue != value)
		{
			printf("##################################\n");
			printf("	 In Critical Section\n");
			printf("##################################\n");
			
			value= lvalue;
			//sleep(1);
		}
		else 
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		
		
	}
}
void top_algorithm(int id, int n)
{
	int rightserver, leftserver, lvalue;
	int value = rand()%n;
	
		//create client to left
		leftserver = clientcreator("out");
	//	printf("leftconnect\n");

		//create client to right
		rightserver = clientcreator("around");
		//printf("rightconnect\n");
		
	while(1)
	{

		if (rightserver <0 || leftserver <0)
			exit(-1);
		
		send(rightserver,&value,sizeof(int),0);
		recv(leftserver,&lvalue,sizeof(int),0);

		
		if (lvalue != value)
		{
			printf("##################################\n");
			printf("	 In Critical Section\n");
			printf("##################################\n");
			
			value= lvalue;
			//sleep(1);
		}
		else 
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		
		
	}
}