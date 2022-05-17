#pragma once
#include <iostream>
#include <sstream>
#include <SFML\Graphics.hpp>

class Textbox
{
public:
	  std::ostringstream text;

	  Textbox(int size, bool select);
	  void setfont(sf::Font& font);
	  void setposition(sf::Vector2f pos);
	  void selected(bool sel);
	  std::string gettext();
	  void drawTo(sf::RenderWindow& window);
	  void validateInput(sf::Event Input);


private:
	sf::Text textbox;

	bool isselected = false;
	bool haslimit = false;
	int limit;

	void userinput(int input);
	void deleteLastChar();

};