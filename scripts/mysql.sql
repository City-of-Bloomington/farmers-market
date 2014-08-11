-- @copyright 2014 City of Bloomington, Indiana
-- @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
-- @author Cliff Ingham <inghamn@bloomington.in.gov>
create table people (
	id int unsigned not null primary key auto_increment,
	firstname varchar(128) not null,
	lastname varchar(128) not null,
	email varchar(255) not null,
	username varchar(40) unique,
	password varchar(40),
	authenticationMethod varchar(40),
	role varchar(30)
);

create table vendors (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null,
	website varchar(255),
	address varchar(128),
	city varchar(128),
	state varchar(2),
	zip varchar(5),
	phone varchar(15),
	email varchar(128)
);

create table vendor_people (
	vendor_id int unsigned not null,
	person_id int unsigned not null,
	primary key (vendor_id, person_id),
	foreign key (vendor_id) references vendors(id),
	foreign key (person_id) references people (id)
);

create table spaces (
	id int unsigned not null primary key auto_increment,
	name varchar(10) not null
);

create table vendor_spaces (
	id int unsigned not null primary key auto_increment,
	vendor_id int unsigned not null,
	space_id  int unsigned not null,
	year year(4),
	foreign key (vendor_id) references vendors(id),
	foreign key (space_id)  references spaces (id)
);
