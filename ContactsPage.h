#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include"Textbox.h"
#include <locale>
#include"User.h"

using namespace sf;
using namespace std;

class ContactsPage
{
public:
    User curruser2;

    void viewMyContacts(Text contacts[], RenderWindow& Window, vector<string> v, bool myContacts, int p);
    void viewUserContacts(Text contacts[], RenderWindow& Window, vector<string> v, bool myContacts);
    void sendmsg(double sender, string reciever, string msg, string senderUsername);
    vector<string> search(string username, int currentUser_id);
    int viewSend(User curruser);
    void undo();
    bool findUsername(vector<User>users, string username
        , string currentUsername);
    double getContactId(vector<User>users, string username);
    string getUsername(vector<User>users, double id);
};

