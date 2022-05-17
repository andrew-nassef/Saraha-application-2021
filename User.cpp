#include "User.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

void User::add_new_user(string username ,string password , vector<User> users ) {
	this->username = username;
	this->password = password;
	id = random_id(users);
}

void User::set_user(User user)
{
	username = user.get_username();
	id = user.get_id();
	password = user.get_password();
}

 double User::get_id() {
	 return id;
 }

 double User::random_id(vector<User> users) {
	 // check if the created user id doesnt match any of the others id's
	// return rand();
	 double id;
	 while (true) {
		 int counter = 0;
		 id = rand();
		 for (int i = 0; i < users.size(); i++) {
			 if (id == users[i].get_id())
				 counter--;
			 counter++;
		 }
		 if (counter == users.size())
			 break;
	 }
	 return id;

 }

 string User::get_username() {
	 return username;
 }

 string User::get_password() {
	 return password;
 }

 void User::set_username(string username) {
	 this->username = username;
 }

 void User::set_password(string password) {
	 this->password = password;
 }

 void User::set_id(double id) {
	 this->id = id;
 }