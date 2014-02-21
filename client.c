/* 
 * Name:        Abdulrahman S Hassan
 * File:        client.c
 */
 
#include "client.h"

#define PORT           59481
#define BUFF_SIZE       2048

int socket_fd;

int main(int argc, char *argv[])
{
    init_connection();
    //monitor_connection();
    //register_signals
    for (int i = 0; i < 100; i++) {
        send_test();
        recv_test();
        usleep(200000);
    }

    exit(EXIT_SUCCESS);
}

void init_connection()
{
    struct sockaddr_in servaddr;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Problem creating the socket");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    printf("Establishing connection to the server...\n");
    if (connect(socket_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("Problem connecting to the server");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    
    listen(socket_fd , 3);
}

void send_test()
{
    char sendline[BUFF_SIZE] = "";

    printf("Sending data to the server...\n");
    sprintf(sendline, "%s", "Test");
    if (send(socket_fd, sendline, strlen(sendline), 0) == 0) {
        perror("Could not send data to server.");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Sent '%s' to server...\n", sendline);
}

void recv_test()
{
    char recvline[BUFF_SIZE] = "";

    printf("Receiving data from the server...\n");
    if (recv(socket_fd, recvline, BUFF_SIZE, 0) == 0) {
        perror("The server terminated prematurely.");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Received '%s' from server\n", recvline);
}

/* The below functions are to keep the connection alive in threaded fashion */
void register_signals()
{
    struct sigaction handler;
    
    handler.sa_handler = cleanup;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGHUP, &handler, NULL);
    sigaction(SIGINT, &handler, NULL);
    sigaction(SIGQUIT, &handler, NULL);
}


void cleanup(int signo)
{
    printf("Caught signal: %d\n", signo);
    printf("Closing the socket and cleaning up the mess...\n");
    close(socket_fd);
    exit(EXIT_FAILURE);
}

void monitor_connection()
{
    pthread_t thread;

    pthread_create(&thread, NULL, monitor, NULL);
    pthread_detach(thread);
}

void *monitor(void *args)
{
    char recvline[BUFF_SIZE];

    printf("Started monitoring the connection...\n");
    while (1) {
        if (recv(socket_fd, recvline, BUFF_SIZE, 0) == 0) {
            perror("The server terminated prematurely.");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }
        printf("Received %s\n", recvline);
    }
    free(args);
    pthread_exit(NULL);
    return NULL;
}
