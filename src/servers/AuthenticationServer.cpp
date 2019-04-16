/** @file AuthenticationServer.cpp
 *  @brief Authenticates user
 *  Used to check username and password before loggin in an user
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; primary author
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 */

#include "../../include/servers/AuthenticationServer.hpp"

AuthenticationServer::AuthenticationServer() {
}
/**@brief authenticates username
 * @param username - string
 * @return true or false - bool
 */
bool AuthenticationServer::AuthenticateUsername(std::string username) {
    return true;
}
/**@brief authenticates password
 * @param password - string
 * @return true or false - bool
 */
bool AuthenticationServer::AuthenticatePassword(std::string password) {
    if (password.length() < 8) {
        return false;
    }
    return true;
}
/**@brief authenticates license number
 * @param license_num
 * @return true or false - bool
 */
bool AuthenticationServer::AuthenticateLicense(std::string license_num) {
    if (license_num.length() == 15) {
        return true;
    }
    return false;
}

