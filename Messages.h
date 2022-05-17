#pragma once
#include <iostream>

using namespace std;

class Messages
{

private:

public:
	string id;
	string sender;
	string reciever;
	string message;
	int globalIndex;
	int favIndex = -1;
	int isFavorite;
	void displayMessage();
};

