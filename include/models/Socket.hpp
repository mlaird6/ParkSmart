//---------------------------------------------------------//
//  Socket.h 					  						   //	
//  CS3307_stage3										   //		
//  Created by Jake McLaughlin on 2018-11.				   //		
//  Copyright © 2018 Jake McLaughlin. All rights reserved. //
//---------------------------------------------------------//

#include <arpa/inet.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <string.h> 
#include <string> 
#include <iostream>

#include "../Threads.hpp"

#ifndef SOCKET_H
#define SOCKET_H
#define BUFFER_LEN 2048
class Socket {
    private:
        int socket;
        char *sndbuffer;
        char *rcvbuffer;
        pthread_t thread;
    public:
        Socket(int new_socket, pthread_t thread);
        void send_msg(char * message);
        std::string receive();
};

#endif