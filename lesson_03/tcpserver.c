/*
 * Author: Philipp Aeschlimann - September 2009
 * Version 1.0
 * tcpserver.c - A simple TCP-Server
 *
 * tcpserver.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

//Fehler sauber ausgeben
void error(char *msg) {
    perror(msg);
	exit(0);
}

//void main routine
int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    if (argc < 2) {
        fprintf(stderr, "ERROR, kein Port angegeben\n");
		exit(0);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error("ERROR, konnte Socket nicht öffnen\n");
		exit(0);
	}
    bzero((char *) & serv_addr, sizeof (serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // listen on TCP socket
    if (bind(sockfd, (struct sockaddr *) & serv_addr,sizeof (serv_addr)) < 0){
        error("ERROR, konnte Socket nicht anbinden\n");
		exit(0);
	}
    listen(sockfd, 5);
    clilen = sizeof (cli_addr);
    printf("Listening on port %d now\n", portno);

    // accept client and create TCP connection
    newsockfd = accept(sockfd, (struct sockaddr *) & cli_addr, &clilen);
    if (newsockfd < 0){
        error("ERROR, konnte Client nicht anbinden");
		exit(0);
	}
    printf("Accepted client with descriptor number %d now now\n", newsockfd);

    // communicate with client
    int msg_length = 99;
    char message_from_client[msg_length];

    while (1) {
      // receive message
      recv(newsockfd, message_from_client, msg_length, 0);
      printf("Message from client: %s", message_from_client);// TODO: test printf with pointers

      // send message
      char *msg = "Thx client received message!\n";
      send(newsockfd, msg, strlen(msg), 0);

      // clear buffer
      memset(&message_from_client[0], '\0', sizeof(message_from_client));// this ensures that no fractals of the old message are printed with the new message
    }

    return 0;
}
