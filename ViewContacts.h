#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include"Textbox.h"
#include <locale>

using namespace sf;
using namespace std;

class ViewContacts
{
public:
 
    //void search(Text contacts[], string username, RenderWindow& Window);
    void viewMyContacts(Text contacts[], RenderWindow& Window, vector<string> v, bool myContacts,int p);
    void sendmsg(double sender, double reciever, string msg) ;
    int viewSend() ;

};

