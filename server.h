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
//#include "client.h"
//#include "structure.h"

int server_main()
{
	char message[50];
	char command[50];
	char buffer_for_fifo[1000];
	char path[17];
	char* temp;
	mqd_t queue;
	int FIFO_fd;
	ssize_t len;

	struct mq_attr attr = {};
   	attr.mq_maxmsg = 10;
   	attr.mq_msgsize = 2048;

	//Creating unique FIFO 
	//****************************************************************************
   	strcpy(path,"JustinFIFOXXXXXX");
	temp = mktemp(path);
	if(mkfifo(temp, S_IRUSR | S_IWUSR | S_IXUSR) == -1) //This is making the FIFO
	{
		perror("The FIFO was not created.\n");
	}
	printf("%s is online\n", temp);
	//****************************************************************************

	strcpy(message,"/");
	strcat(message,temp);

	//Creating message queue
	//****************************************************************************
	queue = mq_open(message, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);

   	if( queue == (mqd_t)-1)
   	{
      perror("open");
      return EXIT_FAILURE;
   	}
   	//****************************************************************************

	//Opening FIFO
	//****************************************************************************
	FIFO_fd = open(temp,O_WRONLY);
	//****************************************************************************

	for(;;) //This will be recieving things from the message queue, which is sent there from the client
	{

		len = mq_receive(queue, command , attr.mq_msgsize , 0);

		if(len == -1)
		{
			perror("Error reading the following request: throwing away.");
		}
		else if(strcmp(substring(command, 0 , len-1),"h") == 0)
		{
			//FIFO name and proccess ID
			printf("%s \n", temp);
			printf("Process ID: %d\n",getpid());
			printf("\n");
		}
		else if(strcmp(substring(command, 0 , len-1),"q") == 0)
		{
			break;
		}
		else
		{
			FILE* fp = popen(substring(command, 0 , len),"r");

			while(fgets(buffer_for_fifo, 1000 , fp) != NULL)
			{
				len = write(FIFO_fd, buffer_for_fifo, strlen(buffer_for_fifo));
			}

			pclose(fp);
		}

	}

	//Cleaning up the message queue and the FIFO
	close(queue);
	close(FIFO_fd);
	mq_unlink(message);
	remove(temp);

}
