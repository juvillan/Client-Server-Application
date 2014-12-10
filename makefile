##this is a make file

##******************************************************
##client.h:
	##All the actions will be down in the client
##server.h:
	##Creates the FIFO and the POSIX Message Queue
##substring.h:
	##This is where i will just call the applications of the server and client to run it
##******************************************************

main: Hw11.c client.h server.h substring.h
	gcc -g -o main Hw11.c client.h server.h substring.h -lrt -pthread

clean:
	rm main

tar:
	tar -cf Hw11.tar Hw11.c server.h client.h substring.h makefile

