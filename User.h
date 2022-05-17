#pragma once
#include <iostream>
#include <vector>


using namespace std;
class User
{
    private:
	 double id ;
	 string username;
	 string password;
	 //add here contacts and messages variables

public:
	void add_new_user(string username, string password , vector <User> users);
	void set_user(User user);
	double random_id(vector<User>);
	string get_username();
	string get_password();
	double get_id();
	void set_username(string username);
	void set_password(string password);
	void set_id(double id);

};

