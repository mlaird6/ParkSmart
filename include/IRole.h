#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "IAction.h"

#ifndef IROLE
#define IROLE

/** @file IRole.h
 *  @brief Interface for each role
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; primary author
 *  @author Nicholas Tocco; primary author
 *  @author Katherine Zambrano
 */

class IRole {
	public:
		std::vector<IAction*> actions;

		/** @method getActions
		 *  @brief returns the actions associated to the role
		 *
		 *  @author Jake Mclaughlin
		 *  @author Nicholas Tocco
		 *  @return actions: vector of IActions
		 */
		std::vector<IAction*> getActions(){
			return actions;
		}
};
#endif
