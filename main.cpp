#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "User.h"
#include "StartPage.h"
#include "MessagesPage.h"
#include "ContactsPage.h"

using namespace std;
using namespace sf;


int main()
{
	const int startpage = 4, messagespage = 1, contactspage = 2, terminate = 3;
	int running = startpage;
	User curruser2;
	

	while (true)
	{

		if (running == startpage)
		{
			StartPage first;
			curruser2.set_user(first.start_program());
			if (curruser2.get_id() != 0)
				running = messagespage;
			else
				running = terminate;
		}

		if (running == messagespage)
		{
			MessagesPage second(curruser2);
			running = second.Show_Page();
		}

		if (running == contactspage)
		{
			ContactsPage s;
			running = s.viewSend(curruser2);
		}

		if (running == terminate)
		{
			cout << "Program has been terminated :)";
			return 0;
		}
	}

}