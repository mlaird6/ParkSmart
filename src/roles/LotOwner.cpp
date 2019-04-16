#include "../../include/IRole.h"
#include "../actions/changeRate.cpp"
#include "../actions/changeTime.cpp"
#include "../actions/changeLotName.cpp"
#include "../actions/changeLotAddress.cpp"

using namespace std;

/** @file LotOwner.cpp
 *  @brief Contains Lot owner actions
 *  Used to set and later retrieve the type of actions a lot owner user can perform
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; primary author
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */
class LotOwner: public IRole {
    public:
        LotOwner(){
            changeRate *chngrate = new changeRate();
            chngrate->setName("Change Rate");
            this->actions.push_back(chngrate);

            changeTime *chngtime = new changeTime();
            chngtime->setName("Change Time");
            this->actions.push_back(chngtime);

            changeLotName *chnglotname = new changeLotName();
            chnglotname->setName("Change Lot Name");
            this->actions.push_back(chnglotname);

            changeLotAddress *chnglotaddy = new changeLotAddress();
            chnglotaddy->setName("Change Lot Address");
            this->actions.push_back(chnglotaddy);
        }
};
