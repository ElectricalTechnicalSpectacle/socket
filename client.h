/* 
 * Name:        Abdulrahman S Hassan
 * File:        client.h
 */
 
#ifndef _CLIENT_H
#define _CLIENT_H

#define _BSD_SOURCE
#define _POSIX_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

void init_connection();
void send_test();
void recv_test();
void monitor_connection();
void register_signals();
void *monitor(void *args);
void cleanup(int signo);

#endif