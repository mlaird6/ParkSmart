/** @file WebServer.cpp
 *  @brief Main entry point to start server
 *
 *  Opens a socket to listen for connecting clients, once a client connects
 *  creates thread to handle that specific client with a new Socket object
 *
 *  @author Melina Laird
 *  @author Mike Levis
 *  @author Jake Mclaughlin; primary author
 *  @author Nicholas Tocco
 *  @author Katherine Zambrano
 *  @bug No know bugs.
 */

#include "../../include/servers/WebServer.hpp"
#define REGISTER 1
#define LOGIN 2
#define QUIT 3

#define NUMBER_OF_SENSORS 5
#define BLOCK_ADDRESS 0x04

using namespace std;
//project level global variable to lock and unlock as needed
pthread_mutex_t lock;
//database singleton for acces to MySQL server
DatabaseProxy database = database.instance();

/** @method sensor_main
 *  @brief function to handle the sensor subsystem
 *
 *  This function instantiates the parkinglot and parkingspace objects based on 
 *  the data stored in the database. After instantiation, it will periodically update the 
 *  database based on the values being read form the sensor
 *
 *  @author Mike Levis
 *  @params nothing
 */
void* sensormain(void* arg){
    vector<string> parkingLotV = database.getParkingLot(1);//id,address,rate,opentime(10:00),closingtime,lotname
    vector<vector<string>> parkingSpacesV = database.getParkingSpaces(1);//id,lotid,type,occupied,reserved

    //set up lot
    struct tm openingTime;
    struct tm closingTime;
    int lotID;
    double parkingRate;

    string temp;
    temp=parkingLotV[3].substr(0,2);
    stringstream converter(temp);
    converter>>openingTime.tm_hour;
    converter<<parkingLotV[3].substr(3,2);
    converter>>openingTime.tm_min;

    converter<<parkingLotV[4].substr(0,2);
    converter>>closingTime.tm_hour;
    converter<<parkingLotV[4].substr(3,2);
    converter>>closingTime.tm_min;

    converter<<parkingLotV[0];
    converter>>lotID;

    converter<<parkingLotV[2];
    converter>>parkingRate;

    ParkingLot lot(parkingLotV[5],parkingLotV[1],lotID,parkingRate,closingTime,openingTime);
    //ParkingLot(std::string name, std::string address, int lotID, double parkingRate, tm closingTime, tm openingTime)

    //create and add spaces to lot
    for (int i=0; i<parkingSpacesV.size();i++){
        ParkingSpace space(stoi(parkingSpacesV[i][0]),parkingSpacesV[i][2]);
        lot.addSpace(space);
    }

    //setup sensorblock

    SensorBlock block(NUMBER_OF_SENSORS,BLOCK_ADDRESS);
    lot.addSensorBlock(block);

    //map sensors to space
    for (int i=0; i<NUMBER_OF_SENSORS;i++){
        lot.mapSensorToLot(i,i);
    }

    while(true){
        sleep(10);
        lot.update();
        cout<<"Database Updated"<<endl;
    }

}


/** @method main
 *  @brief entry point into application, running the listening server 
 *
 *  Creates threads to handle each client, starts sensor subsystem and listens for clients
 *
 *  @author Jake Mclaughlin
 *  @params client socket
 */
int main() {
    //-----Thread to handle sensor update----//
    pthread_t sensorSystem;
    pthread_create(&sensorSystem, NULL, sensormain, NULL);
    //----Gets IP of machine and prints----//
    const char* IP_ADDRESS = "10.170.90.191";

    printf("Server IP: %s\n", IP_ADDRESS);
    //----Socket variables----//
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    //----Create Listening Socket----//
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    //----Bind----//
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NO);
    serverAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    bind(serverSocket, (struct sockaddr * ) & serverAddr, sizeof(serverAddr));
    //----Listen----//
    if (listen(serverSocket, 50) == 0)
        cout << "Listening" << endl;
    else
        cout << "Error" << endl;
    //----While loop to accept clients----//
    pthread_t tid[60];
    int i = 0;
    while (true) {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof(serverStorage);
        newSocket = accept(serverSocket, (struct sockaddr * ) & serverStorage, & addr_size);
        //thread for each connecting client
        if (pthread_create( & tid[i++], NULL, handle_client, & newSocket) != 0) {
            cout << "Failed to create thread" << endl;
        }
        //joins threads once it reaches max connections
        if (i >= 50) {
            i = 0;
            while (i < 50) {
                pthread_join(tid[i++], NULL);
            }
            i = 0;
        }
    }
    return 0;
    pthread_join(sensorSystem, NULL);
}

/** @method handle_client.cpp
 *  @brief function for handling individual clients
 *
 *  @author Jake Mclaughlin
 *  @params client socket
 */
void * handle_client(void * arg) {
    int new_socket = *((int * ) arg);
    pthread_t self = pthread_self();
    Socket socket(new_socket, self); //socket object representing this client
    LoggedInUser *user = NULL; //user object for this client
    AuthenticationServer auth; //authentication server for this client

    socket.send_msg((char * )
        "**********  Welcome to ParkSmart  ***********\n");
    /****************************************************************
    * User interaction loop
    /****************************************************************/
    while (true) {
        /****************************************************************
        * Provide basic operations for non logged in client
        /****************************************************************/
        if (user == NULL) {
            socket.send_msg((char * )
                "1. Register\n2. Log in\n3. Quit\nInput: ");
            //Take user request and transform into int
            int request;
            try {
                request = stoi(socket.receive());
            } catch (...) {
                socket.send_msg((char *) "Invalid request.");
                continue;
            }
            /****************************************************************
            * Ask for information to register user in system
            /****************************************************************/
            if (request == REGISTER) {
                user = register_menu(socket, auth);
            }
            /****************************************************************
            * Ask for login information to log user in
            /****************************************************************/
            else if (request == LOGIN) {
                user = login_menu(socket, auth);
            }
            /****************************************************************
            * Quit thread
            /****************************************************************/
            else if (request == QUIT) {
                break;
            }
        }
        /****************************************************************
        * If the user is logged in then provide the user with
        * their verified actions
        /****************************************************************/
        else {

            //gets the actions this user can perform and presents them to the client
            std::vector<IAction*> useractions = user->getActions();
            socket.send_msg((char *) "Actions:\n");
            for(int i = 0; i < useractions.size(); i++){
                string msg = "[" + to_string(i+1) + "] " + useractions[i]->getName() + "\n";
                socket.send_msg((char *) msg.c_str());
            }
            string msg = "[" + to_string(useractions.size()+1) + "] Logout\n";
            socket.send_msg((char *) msg.c_str());
            //gets user input and performs the chosen action based on it
            socket.send_msg((char *) "Enter your choice: ");
            int choice;
            try{
                choice = stoi(socket.receive());
                if(choice == useractions.size()+1){
                    user = NULL;
                }else{
                    useractions[choice-1]->perform(user->getID(), socket);
                }
            }
            catch(...){
                //If the choice isn't valid it will fall through and try again
                socket.send_msg((char *) "Invalid choice.");
            }
        }
    }

    delete user;
    cout<<"Thread #" << to_string(self) << ": quits." << endl;
    close(new_socket);
    pthread_exit(NULL);
}

/** @method register_menu
 *  @brief displays the menu for registering a user
 *
 *  @author Jake Mclaughlin; primary author
 *  @params socket: socket to communicate with user
 *  @params auth: authentication server for authenticating user input
 */
LoggedInUser* register_menu(Socket socket, AuthenticationServer auth) {
    //----Ask for username----//
    socket.send_msg((char * )
        "Enter Username: ");
    string username = socket.receive();
    username = username.substr(0, username.length() - 2);
    while (!auth.AuthenticateUsername(username)) {
        socket.send_msg((char * )
            "Username already taken.");
        socket.send_msg((char * )
            "Enter Username: ");
        username = socket.receive();
        username = username.substr(0, username.length() - 2);
    }
    //----Ask for password----//
    socket.send_msg((char * )
        "Enter Password: ");
    string password = socket.receive();
    password = password.substr(0, password.length() - 2);
    while (!auth.AuthenticatePassword(password)) {
        socket.send_msg((char * )
            "Passwords must be over 8 characters.");
        socket.send_msg((char * )
            "Enter Password: ");
        password = socket.receive();
        password = password.substr(0, password.length() - 2);
    }
     //----Ask for username----//
    socket.send_msg((char * )
        "Enter Firstname: ");
    string fname = socket.receive();
    fname = fname.substr(0, fname.length() - 2);
     //----Ask for username----//
    socket.send_msg((char * )
        "Enter Lastname: ");
    string lname = socket.receive();
    lname= lname.substr(0, lname.length() - 2);
    //----Ask for license number----//
    socket.send_msg((char * )
        "Enter License Number: ");
    string license_num = socket.receive();
    license_num = license_num.substr(0, license_num.length() - 2);
    while (!auth.AuthenticateLicense(license_num)) {
        socket.send_msg((char * )
            "License numbers are 15 characters (no dashes).");
        socket.send_msg((char * )
            "Enter License Number: ");
        license_num = socket.receive();
        license_num = license_num.substr(0, license_num.length() - 2);
    }
    //----Ask for pregnancy----//
    socket.send_msg((char * )
        "Are you pregnant? (Y/n): ");
    string response = socket.receive();
    response = response.substr(0, response.length() - 2);
    int preg;
    if(response == "Y" || response == "y"){
        preg = 1;
    }else{
        preg = 0;
    }
    //----Ask for disability----//
    socket.send_msg((char * )
        "Do you have a disability? (Y/n): ");
    response = socket.receive();
    response = response.substr(0, response.length() - 2);
    int disability;
    if(response == "Y" || response == "y"){
        disability = 1;
    }else{
        disability = 0;
    }
     //----Ask for driver role----//
    socket.send_msg((char * )
        "Are you a driver? (Y/n): ");
    response = socket.receive();
    response = response.substr(0, response.length() - 2);
    int driver;
    if(response == "Y" || response == "y"){
        driver = 1;
    }else{
        driver = 0;
    }
    //----Ask for lotowner role----//
    socket.send_msg((char * )
        "Are you a Lot Owner? (Y/n): ");
    response = socket.receive();
    response = response.substr(0, response.length() - 2);
    int lot_owner;
    if(response == "Y" || response ==  "y"){
        lot_owner = 1;
    }else{
        lot_owner = 0;
    }
    //----Ask for vehicle type----//
    socket.send_msg((char * )
        "Enter Vehicle Type: ");
    string vehicle_type = socket.receive();
    vehicle_type = vehicle_type.substr(0, vehicle_type.length() - 2);

    //----Create user with info----//
    return create_user(username, password, fname, lname, license_num, preg, disability, vehicle_type, driver, lot_owner);
}

/** @method login_menu
 *  @brief displays the menu for logging in
 *
 *  @author Jake Mclaughlin; primary author
 *  @params socket: socket to communicate with user
 *  @params auth: authentication server for authenticating user input
 */
LoggedInUser* login_menu(Socket socket, AuthenticationServer auth) {
    //----Ask for username----//
    socket.send_msg((char * )
        "Enter Username: ");
    string username = socket.receive();
    username = username.substr(0, username.length() - 2);
    while (!auth.AuthenticateUsername(username)) {
        socket.send_msg((char * )
            "Username already taken.");
        socket.send_msg((char * )
            "Enter Username: ");
        username = socket.receive();
        username = username.substr(0, username.length() - 2);
    }
    //----Ask for password----//
    socket.send_msg((char * )
        "Enter Password: ");
    string password = socket.receive();
    password = password.substr(0, password.length() - 2);
    while (!auth.AuthenticatePassword(password)) {
        socket.send_msg((char * )
            "Passwords must be over 8 characters.");
        socket.send_msg((char * )
            "Enter Password: ");
        password = socket.receive();
        password = password.substr(0, password.length() - 2);
    }
    LoggedInUser* user = login(username, password);
    return user;
}

/** @method create_user
 *  @brief takes in user input and enters user into database
 *
 *  @author Jake Mclaughlin; primary author
 *  @params username: string
 *  @params password: string
 *  @params fname: string
 *  @params lname: string
 *  @params license_num: string
 *  @params pregnant: int (0 for false, 1 for true)
 *  @params disability: int (0 for false, 1 for true)
 *  @params vehicle_type: string
 *  @params driver: int (0 for false, 1 for true)
 *  @params lot_owner: int (0 for false, 1 for true)
 *  @return LoggedInUser object
 */
LoggedInUser* create_user(string username, string password, string fname, string lname, string license_num, int pregnant, int disability, string vehicle_type, int driver, int lot_owner) {
    int id = database.createUser(username, password, fname, lname,license_num, pregnant, disability, vehicle_type, driver, lot_owner);
    if(id == -1) return NULL;
    LoggedInUser* user = new LoggedInUser(username, id, license_num, pregnant, disability, vehicle_type, driver, lot_owner);
    return user;
}

/** @method log_in
 *  @brief takes in user input to log the user in
 *
 *  @author Jake Mclaughlin; primary author
 *  @params username: string
 *  @params password: string
 *  @return LoggedInUser object
 */
LoggedInUser* login(string username, string password) {
    vector<string> data = database.getUser(username,password);
    if(data.size() > 0){
        string username = data[0];
        int id = stoi(data[1]);
        string license_num = data[2];
        int pregnant = stoi(data[3]);
        int disability = stoi(data[4]);
        string vehicle_type = data[5];
        int driver = stoi(data[6]);
        int lot_owner = stoi(data[7]);

        LoggedInUser* user = new LoggedInUser(username, id, license_num, pregnant, disability, vehicle_type, driver, lot_owner);
        return user;
    }
    return NULL;
}

/** @method getIPaddress()
 *  @brief gets the ip address of the machine
 *
 *  @author Jake Mclaughlin; primary author
 *  @params username: string
 *  @params password: string
 *  @return LoggedInUser object
 */
string getIPAddress () {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    char addressBuffer[INET_ADDRSTRLEN];

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET || ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            if(strstr(ifa->ifa_name, "eth0") != NULL){
                string str(addressBuffer);
                return str;
            }
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
}
