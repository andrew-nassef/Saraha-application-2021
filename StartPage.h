#pragma once
#include <vector>
#include "User.h"


class StartPage
{
public:
    vector<User> users;
    User curruser;


public:
    User start_program();
    bool register_login_page(int x);
    bool is_username_availble(string username, string password);
    int username_password_match(string username, string password);
    void print_user_to_file(User entered_user);
    vector<User> read_users_from_file();

};