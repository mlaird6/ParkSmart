CC=g++
CFLAGS=-c
CMATH=-lm
PFLAG=-pthread
SQL=-lmysqlcppconn

all: clean run

run: ParkingSession.o ActiveParkingSessions.o Socket.o AuthenticationServer.o LoggedInUser.o WebServer.o DatabaseProxy.o ParkingLot.o ParkingSpace.o SensorBlock.o SensorPacket.o I2CPi.o
	$(CC) -o $@ $^ $(CMATH) $(PFLAG) $(SQL)

LoggedInUser.o: ../src/models/LoggedInUser.cpp
	$(CC) $(CFLAGS) -o $@ $<

WebServer.o: ../src/servers/WebServer.cpp
	$(CC) $(CFLAGS) -o $@ $<

AuthenticationServer.o: ../src/servers/AuthenticationServer.cpp
	$(CC) $(CFLAGS) -o $@ $<

Socket.o: ../src/models/Socket.cpp
	$(CC) $(CFLAGS) -o $@ $<

ActiveParkingSessions.o: ../src/models/ActiveParkingSessions.cpp
	$(CC) $(CFLAGS) -o $@ $<

ParkingSession.o: ../src/models/ParkingSession.cpp
	$(CC) $(CFLAGS) -o $@ $<

DatabaseProxy.o: ../src/DatabaseProxy.cpp
	$(CC) $(CFLAGS) -o $@ $<
	
ParkingLot.o: ../Hardware/ParkingLot.cpp
	$(CC) $(CFLAGS) -o $@ $<
	
ParkingSpace.o: ../Hardware/ParkingSpace.cpp
	$(CC) $(CFLAGS) -o $@ $<
		
SensorBlock.o: ../Hardware/SensorBlock.cpp
	$(CC) $(CFLAGS) -o $@ $<
		
SensorPacket.o: ../Hardware/SensorPacket.cpp
	$(CC) $(CFLAGS) -o $@ $<
		
I2CPi.o: ../Hardware/I2CPi.cpp
	$(CC) $(CFLAGS) -o $@ $<
		
clean:
	rm -f *.o
