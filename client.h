/**********************************************************************\
*                Copyright (C) Justin Villani, 2014.                   *
*                                                                      *
* This program is free software. You may use, modify, and redistribute *
* it under the terms of the GNU Affero General Public License as       *
* published by the Free Software Foundation, either version 3 or (at   *
* your option) any later version. This program is distributed without  *
* any warranty.                                                        *
\**********************************************************************/

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "substring.h"

void client_fifo_read(void *arg)
{
	char buffer[1000];
	ssize_t len;
	int fifo_fd;

	//Open the FIFO
	fifo_fd = open((char*)arg, O_RDONLY);

	//Contiuing to read
	while((len = read(fifo_fd, buffer, 1000)) != 0)
	{
		write(STDIN_FILENO, buffer, len);
	}

	close(fifo_fd);

	return NULL;
}


int client_main(char servername[])
{
	pthread_t thread_fifo;
	pthread_create(&thread_fifo,NULL,client_fifo_read,(void *)servername);

	char message[50];
	char input[50];
	char command_from_shell[50];

	ssize_t command;
	ssize_t led;

	struct mq_attr attr = {};
   	attr.mq_maxmsg = 10;
   	attr.mq_msgsize = 2048;
   	mqd_t queue;

	//Writing to the message queue
	//*****************************************************************

	strcpy(message,"/");
	strcat(message,servername);

	queue = mq_open(message, O_WRONLY, S_IRUSR | S_IWUSR | S_IXUSR, &attr);

   	if(queue == (mqd_t)-1)
   	{
      perror("open");
      return EXIT_FAILURE;
   	}
   	//*******************************************************************

	for(;;) //This will be recieving things from the message queue, which is sent there from the client
	{
		printf("Please enter one of commands: e[exit], k[killsvr], h[help], s[shell]\n");

		led = read(STDIN_FILENO, input , 50);

		if( led == -1)
		{
			perror("Error reading the following request: throwing away.");
		}
		else if(strcmp(substring(input, 0 , led-1),"h") == 0)
		{
			//FIFO name and proccess ID
			printf("********Client Helpful Info********");
			printf("\nPlease enter one of commands: e[exit], k[killsvr], h[help], s[shell]\n");
			printf("***********************************\n\n");
			mq_send(queue,input,led,0);	
		}
		else if(strcmp(substring(input, 0 , led-1),"e") == 0)
		{
			break;
		}
		else if(strcmp(substring(input, 0 , led-1),"k") == 0)
		{
			//send the quit command to the server
			mq_send(queue,"q", led, 0);
			break;
		}
		else if(strcmp(substring(input, 0 , led-1),"s") == 0)
		{
			printf("Enter Command:");
			printf("\n");
			command = read(STDIN_FILENO, command_from_shell, 50);

			if( command == -1)
			{
				perror("Error reading the following request: throwing away.");
			}
			
			mq_send(queue, substring(command_from_shell, 0 , command-1), command, 0);
		}
		else
		{
			continue;
		}

	}

}
