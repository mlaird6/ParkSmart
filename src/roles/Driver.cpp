#include "../../include/IRole.h"
#include "../actions/Reserve.cpp"
#include "../actions/view.cpp"

/** @file Driver.cpp
 *  @brief Contains Driver user actions
 *  Used to set and later retrieve the type of actions a driver user can perform
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; primary author
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */
class Driver: public IRole {
	public:
		Driver(){
			Reserve *reserve = new Reserve();
			reserve->setName("Reserve");
			this->actions.push_back(reserve);

			view *View = new view();
			View->setName("View Parking Lot");
			this->actions.push_back(View);
		}

};
