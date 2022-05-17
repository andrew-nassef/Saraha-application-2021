#pragma once
#include <iostream>
#include "User.h"
#include "Messages.h"
#include <stack>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>


using namespace std;

class MessagesPage
{
private:
	User curruser1;


public:
	vector <Messages> recived_msg;
	vector <Messages> sent_msg;
	stack <Messages> fav_msg;
	stack <Messages> fav_msg_sub;
	Messages currmsg;

	MessagesPage(User curruser);
	int Show_Page();
	void readFile();
	void writeFile(int index, int fav);

};

