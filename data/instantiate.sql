create table user (id MEDIUMINT NOT NULL AUTO_INCREMENT, username CHAR(30) NOT NULL, password CHAR(30),
 					fname CHAR(30), lname CHAR(30), vehicle_type CHAR(15), license_num CHAR(20), 
 					pregnant TINYINT, disability TINYINT, driver TINYINT, lot_owner TINYINT, PRIMARY KEY (id));
create table parkingLot (id MEDIUMINT NOT NULL, address CHAR(30), rate CHAR(30), open_time CHAR(5), close_time CHAR(5), lot_name CHAR(30), PRIMARY KEY (id));
create table parkingSpace (id MEDIUMINT NOT NULL, lotid MEDIUMINT NOT NULL REFERENCES parkingLot(id), type CHAR(10), occupied TINYINT, reserved TINYINT, PRIMARY KEY (id));
insert into parkingLot (id, address, rate, open_time, close_time, lot_name) values (1, "1 addy lane", "8", "10:00", "17:00", "lot1");
insert into parkingSpace (id, lotid, type, occupied, reserved) values (1, 1, "normal", 0, 0),
	(2, 1, "normal", 0, 0),
	(3, 1, "normal", 0, 0),
	(4, 1, "normal", 0, 0),
	(5, 1, "normal", 0, 0);

