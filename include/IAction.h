#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "./models/Socket.hpp"

#ifndef IACTION
#define IACTION

/** @file IAction.h
 *  @brief Interface for each action
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; primary author
 *  @author Nicholas Tocco; primary author
 *  @author Katherine Zambrano
 */

class IAction {
	private:
		std::string name;
	public:

		std::string getName(){
			return name;
		}

		void setName(std::string new_name){
			name = new_name;
		}

		/** @method Perform
		 *  @brief Perform method executes code associated to the specific action
		 *
		 *  @author Jake Mclaughlin
		 *  @author Nicholas Tocco
		 *  @param userid: id of calling user
		 *  @param sock: socket of calling client
		 */
		virtual void perform(int userid, Socket sock) = 0;

};
#endif
