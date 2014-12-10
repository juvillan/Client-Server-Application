/**********************************************************************\
*                Copyright (C) Justin Villani, 2014.                   *
*                                                                      *
* This program is free software. You may use, modify, and redistribute *
* it under the terms of the GNU Affero General Public License as       *
* published by the Free Software Foundation, either version 3 or (at   *
* your option) any later version. This program is distributed without  *
* any warranty.                                                        *
\**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "client.h"


int main(int argc, char* argv[])
{
   int opt = 0 , purpose = -1;
   char servername[16];
   int x, y;

   printf("Please supply -c [servername] for client operation or -s for server operation.\n");

   while((opt = getopt(argc, argv, "c:s")) != -1)
   {
      switch(opt)
      {
         case 'c':
         {
            purpose = opt;
            strcpy(servername,optarg);
            break;
         }
         case 's':
         {
            purpose = opt;
            break;
         }
         default:
         {
            printf("Please supply -c [servername] for client operation or -s for server operation\n");
            break;
         }
      }
   }

   switch(purpose)
   {
      case 'c':
      {
         client_main(servername);

          if (argc < 3)
          {
               printf("Please supply -c [servername] for client operation or -s for server operation\n");
          } 

          break; 
      } 
      case 's':
      {

         server_main();

         if(argc != 1)
         {
               printf("Please supply -c [servername] for client operation or -s for server operation\n");
         }

         break;
      } 
   }

}

//please supply -c [servername] for client operation or -s for server operation