#include "Textbox.h"
#include <iostream>
#include <sstream>
#include <SFML\Graphics.hpp>
#define  DELETE_KEY 8
#define  ENTER_KEY  13
#define  ESCAPE_KEY 27


Textbox::Textbox(int size, bool select) {
	textbox.setCharacterSize(size);
	textbox.setFillColor(sf::Color::White);


	isselected = select;
	if (select) {
		textbox.setString("_");

	}
	else {
		textbox.setString("");
	}

}

void Textbox::setfont(sf::Font& font) {
	textbox.setFont(font);
}

void Textbox::setposition(sf::Vector2f pos) {
	textbox.setPosition(pos);
}

void Textbox::selected(bool sel) {
	isselected = sel;
	if (!sel) {
		std::string t = text.str();
		std::string newt = "";
		for (int i = 0; i < t.length(); i++) {
			newt = t[i];
		}
		textbox.setString(newt);
	}
}

std::string Textbox::gettext() {
	return text.str();
}

void Textbox::drawTo(sf::RenderWindow& window) {
	textbox.setPosition(335, 350);
	window.draw(textbox);
}

void Textbox::validateInput(sf::Event Input) {
	if (isselected) {
		int chartyped = Input.text.unicode;
		if (chartyped < 128) {
			userinput(chartyped);
		}
	}

}

void Textbox::userinput(int input) {
	if (input != DELETE_KEY && input != ENTER_KEY && input != ESCAPE_KEY) {
		text << static_cast<char>(input);
		if (text.str().length() % 40 == 0)
		{
			text << "\n";
		}
	}

	else if (input == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	textbox.setString(text.str());

}

void Textbox::deleteLastChar() {
	std::string t = text.str();
	std::string newt = "";
	for (int i = 0; i < t.length()-1; i++) {
		newt += t[i];
	}
	text.str("");
	text << newt;
	textbox.setString(text.str());
}