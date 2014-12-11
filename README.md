Client-Server-Application Directions for the assignment
=========================

This homework will require you to write a C or C++ application that can run in one of two different modes: as a client or as a server (use a command switch). 
When running as the server, the process must create a FIFO and print the name for it. When running as a client, the process must request the name of the server and then ”connect” to it. 
The client then sends shell commands to execute to the server and the server must respond with the command output (standard out). Additonally, there is a list of commands that the client must support. 
The application must perform the requirements below.

1. You shall submit all source code and a makefile in a tar file.
        (a) The makefile shall be able to build your source in a 32 bit PeppermintOS VM.
2. The program shall support two modes of operation: server and client. These two modes should be specified via a command switch.
3. The program shall indicate how to start the program in each mode. This only needs to be done if no valid command argument is specified.
4. The server shall create a uniquely named FIFO when it starts. The name of the FIFO must be less than 16 characters and it has to be different each time the server runs. You must support multiple running servers at a time.
5. The server shall print the name of the FIFO when it starts. This name will then be used by the client.
6. The server shall create a Message Queue. This queue should be reasonably unique to the server and the client will need to know its name somehow. 1
7. The server shall read commands from the message queue and perform the following actions:
          (a) If the quit command is sent, the server shall terminate, cleaning up resources as appropriate.
          (b) If the help command is sent, the server shall print the name of it’s FIFO and it’s process ID.
          (c) If the shell command is sent, the server shall execute a specified shell command. The shell command should be transmitted to the server as part of the message.
8. Each message in the queue shall contain all the necessary information to perform its action.
9. The output of each shell command executed by the server shall be written to the FIFO.
10. The server shall clean up any FIFO or Message Queue that it creates.
11. The client shall accept the name of the FIFO on the command line.
12. The client shall print all data in the FIFO to standard out.
13. The client shall read commands from standard in continuously as follows:
          (a) If the user enters the exit command, the client shall terminate.
          (b) If the user enters the server quit command, the client shall send the quit command to the server.
          (c) If the user enters the help command, the client shall send the help command to the server as well as print out client help information.
          (d) If the user enters the shell command, the client shall send the user specified command to the server for execution. The user should then be able to enter the command. You can allow them to be entered together (shell ls) or prompt again for the command.
14. The client shall only send the quit command to the server when the user specifically requests it to be sent.
15. The client shall terminate if the server specified is not running. You should not attempt to keep sending commands to a server that has terminated. The client should terminate if it is unable to send commands or read results. This should work even if the server abnormally terminates.
16. The client shall be able to receive commands even when printing out information from the FIFO. Printing the FIFO contents should not delay reading commands from the user and vice versa.
