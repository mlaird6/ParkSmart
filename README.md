# CS3307: ParkSmart

ParkSmart provides detailed parking lot availability data to users. Our application will classify
each parking spot in the lot as either taken or available and report the data to users using a
clean graphical interface. Hardware elements include distance sensors which are necessary to
detect cars and return data. Increased functionality may include a mobile application, off-site
data storage, and increased data about specific parking spots (proximity to buildings, shade,
timing, etc.).

## Getting Started

To run this project you must be using the Raspbian Operating System, whether as a virtual machine or on the device.
Git is required for this project.
```
#clone this project
git clone ssh://git@repo.csd.uwo.ca:7999/compsci3307_f2018/group30.git

#download MySQL
sudo apt-get install mysql-server

#install mysql c++ connector
sudo apt-get install libmysqlcppconn-dev

#setup the database in mysql
create database ParkSmart;
create user 'username'@'%' identified by 'password';
grant all privileges on ParkSmart to 'username'@'%';

#run the script in data folder to instantiate a version of the mysql database
cd data
mysql -u username -p password ParkSmart < instantiate.sql

#build the project
cd build
make

#start the server
./server_run

#start the sensor sub system
./sensor_run

#open a telnet client to connect to the server with the ip address and port number in WebServer.hpp
```

## Contributing

To contribute to this project create a new branch for your feature
```
git branch <branch_name>
git checkout <branch_name>
```
Code away! When ready to push commit your changes and push to your branch
```
git push origin <branch_name>
```
Then create a pull request in the BitBucket repository.

## Project Structure

* `bin` - holds executables
* `build` - holds makefile and test scripts
* `data` - holds additional data for startup
* `include` - holds header files
* `src` - holds C++ files
   * `models` - models used in system
   * `actions` - implementations of actions
   * `servers` - implementations of seperate servers (WebServer, AuthenticationServer, DatabaseServer)

## Authors

* **Jake McLaughlin** - (https://github.com/jakemclaughlin6)
* **Melina Laird** - (https://github.com/mlaird6)
* **Nicholas Tocco** - (https://github.com/toccon)
* **Mike Levis** - (https://github.com/opop10)
* **Katherine Zambrano** - (https://repo.csd.uwo.ca/users/kzambran)

