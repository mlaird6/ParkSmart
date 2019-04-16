/** @file Socket.cpp
 *  @brief Creates a socket object.
 *
 *  A Socket class can be used to create socket objects which can send and receive messages.
 *
 *  @param socket;
 *  @param thread;
 *  @param rcvbuffer ;
 *  @param sndbuffer
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; primary author
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */
#include "../../include/models/Socket.hpp"

using namespace std;
//@brief Create a new socket object
Socket::Socket(int new_socket, pthread_t new_thread){
	socket = new_socket;
	thread = new_thread;
    rcvbuffer = (char * ) malloc(BUFFER_LEN);
    sndbuffer = (char * ) malloc(BUFFER_LEN);
	memset(sndbuffer, 0, BUFFER_LEN);
	memset(rcvbuffer, 0, BUFFER_LEN);
}
//@brief Use socket Object to send a message
void Socket::send_msg(char* message){
    strcpy(sndbuffer, message);
	send(socket, sndbuffer, strlen(sndbuffer), 0);
  	memset(sndbuffer, 0, BUFFER_LEN);
}
//@brief Use socket Object to receive a message
std::string Socket::receive(){
  	int bytesRcvd = recv(socket, rcvbuffer, BUFFER_LEN, 0);
	std::string request = std::string(rcvbuffer, 0, bytesRcvd);
	memset(rcvbuffer, 0, BUFFER_LEN);
	cout << "Thread #" << thread << ": " << request;
	return request;
}
