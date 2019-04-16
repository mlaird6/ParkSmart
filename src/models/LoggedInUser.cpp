/** @file LoggedInUser.cpp
 *  @brief Logged in User information.
 *
 *  Once a user has been logged in its information and possible actions can be retrieved.
 *
 *  @param username; string
 *  @param UID; int
 *  @param license_num; string
 *  @param pregnant;  int
 *  @param disability; int
 *  @param vehicle_type; int
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */

#include "../../include/models/LoggedInUser.hpp"
#include "../roles/Driver.cpp"
#include "../roles/LotOwner.cpp"
#include <algorithm>

bool is_in(IAction* act, std::vector<IAction*> acts){
	for(int i = 0; i< acts.size(); i++){
		if(act->getName() == acts[i]->getName()){
			return true;
		}
	}
	return false;
}

/** @brief Initializes data for a user object.
 *  @param new_username - string
 *  @param new_id - int
 *  @param new_license_num - int
 *  @param new_pregnant - int
 *  @param new_disability - int
 *  @param new_vehicle_type - int
 *  @param isdriver - int
 *  @param isowner - int
 *  @return N/A
 */
LoggedInUser::LoggedInUser(std::string new_username, int new_id, std::string new_license_num, int new_pregnant,
							int new_disability, std::string new_vehicle_type, int isdriver, int isowner) {

	username = new_username;
	UID = new_id;
	license_num = new_license_num;
	pregnant = new_pregnant;
	disability = new_disability;
	vehicle_type = new_vehicle_type;

	if(isdriver){
		Driver driver;
		roles.push_back(driver);
	}
	if(isowner){
		LotOwner owner;
		roles.push_back(owner);
	}
}

/** @brief Iterates through users roles to get actions they can perform.
 *  @param N/A
 *  @return actions - vector of actions
 */
std::vector<IAction*> LoggedInUser::getActions() {
	std::vector<IAction*> actions;
	for(int i = 0; i< roles.size(); i++){
		for( int j = 0; j<roles[i].getActions().size(); j++){
			if(!is_in(roles[i].getActions()[j], actions)){
				actions.push_back(roles[i].getActions()[j]);
			}
		}
	}
	return actions;
}

/**  @brief gets user id
 *   @param N/A
 *   @return user id - int
 */
int LoggedInUser::getID(){
	return this->UID;
}
