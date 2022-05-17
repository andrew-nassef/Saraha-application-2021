#include "StartPage.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include "User.h"
#include <vector>
#include <fstream>

using namespace sf;
using namespace std;

RenderWindow window(sf::VideoMode(1000, 800), "", Style::None);


User StartPage::start_program() {

    Vector2i grabbedOffset;
    bool grabbedWindow = false;
    window.setKeyRepeatEnabled(false);
    users = read_users_from_file();
    int curreent_user_index;


    // assigning tetxures
    Texture background_texture, buttons;


    background_texture.loadFromFile("Textures\\start.png");
    buttons.loadFromFile("Textures\\buttons.png");


    //asssigning sprites
    Sprite background_sprite, login_button_sprite, register_button_sprite;


    background_sprite.setTexture(background_texture);
    login_button_sprite.setTexture(buttons);
    register_button_sprite.setTexture(buttons);
    register_button_sprite.setTextureRect(IntRect(0, 224, 253, 73));
    login_button_sprite.setTextureRect(IntRect(0, 299, 253, 73));

    //sprites positions
    register_button_sprite.setPosition(360, 400);
    login_button_sprite.setPosition(360, 500);



    while (window.isOpen())
    {

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                curruser.set_id(0);
                return(curruser);
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    curruser.set_id(0);
                    return(curruser);
                    window.close();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                    grabbedWindow = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    grabbedWindow = false;
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (grabbedWindow)
                    window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
            }

            //check if register button pressed
            if (Mouse::getPosition(window).x >= 360 &&
                Mouse::getPosition(window).x <= 613 &&
                Mouse::getPosition(window).y >= 400 &&
                Mouse::getPosition(window).y <= 473)
            {
                register_button_sprite.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {
                    if (register_login_page(1))
                    {
                        window.close();
                        return(curruser);
                    }
                }
            }
            else
                register_button_sprite.setScale(1, 1);

            //check if login button is pressed 
            if (Mouse::getPosition(window).x >= 360 &&
                Mouse::getPosition(window).x <= 613 &&
                Mouse::getPosition(window).y >= 500 &&
                Mouse::getPosition(window).y <= 573)
            {
                login_button_sprite.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {
                    if (register_login_page(2))
                    {
                        window.close();
                        return(curruser);
                    }
                }
            }
            else
                login_button_sprite.setScale(1, 1);

        }

        // draw functions

        window.clear();
        window.draw(background_sprite);
        window.draw(login_button_sprite);
        window.draw(register_button_sprite);
        window.display();

    }


}

bool StartPage::register_login_page(int x) {

    window.setKeyRepeatEnabled(false);
    Vector2i grabbedOffset;
    bool grabbedWindow = false;
    User  user_regestration;
    int curreent_user_index;


    // assigning tetxures
    Texture background_texture, buttons;

    background_texture.loadFromFile("Textures\\start.png");
    buttons.loadFromFile("Textures\\buttons.png");

    //asssigning sprites
    Sprite background_sprite, register_button_sprite, login_button_sprite, text_bar_sprite, text_bar2_sprite, back_button_sprite;

    background_sprite.setTexture(background_texture);
    register_button_sprite.setTexture(buttons);
    login_button_sprite.setTexture(buttons);
    text_bar_sprite.setTexture(buttons);
    text_bar2_sprite.setTexture(buttons);
    back_button_sprite.setTexture(buttons);
    register_button_sprite.setTextureRect(IntRect(0, 224, 253, 73));
    login_button_sprite.setTextureRect(IntRect(0, 299, 253, 73));
    text_bar_sprite.setTextureRect(IntRect(0, 375, 330, 73));
    text_bar2_sprite.setTextureRect(IntRect(0, 375, 330, 73));
    back_button_sprite.setTextureRect(IntRect(0, 450, 100, 94));


    //sprites positions

    text_bar_sprite.setPosition(333, 370);
    text_bar2_sprite.setPosition(333, 490);
    register_button_sprite.setPosition(370, 610);
    login_button_sprite.setPosition(370, 610);
    back_button_sprite.setPosition(70, 100);

    //strings properties and variables
    sf::String UsernameInput, PasswordInput;
    Text entered_user_username_text, username_text, entered_user_password_text, password_text,
        username_error_text;
    Font font;
    font.loadFromFile("Fonts\\Basic-Regular.TTF");

    //username

    username_text.setString("Username");
    username_text.setPosition(430, 330);
    username_text.setCharacterSize(30);
    username_text.setFillColor(Color(61, 144, 227));
    username_text.setFont(font);

    entered_user_username_text.setPosition(350, 385);
    entered_user_username_text.setCharacterSize(30);
    entered_user_username_text.setFillColor(Color::Black);
    entered_user_username_text.setFont(font);

    bool is_username_typed = false;

    username_error_text.setString("error Invalid information");
    username_error_text.setPosition(270, 700);
    username_error_text.setCharacterSize(40);
    username_error_text.setFillColor(Color::Red);
    username_error_text.setFont(font);

    bool is_username_error_typed = false;
    bool is_invadlid_username_or_password_typed = false;


    //password

    password_text.setString("Password");
    password_text.setPosition(430, 450);
    password_text.setCharacterSize(30);
    password_text.setFillColor(Color(61, 144, 227));
    password_text.setFont(font);

    entered_user_password_text.setPosition(350, 505);
    entered_user_password_text.setCharacterSize(30);
    entered_user_password_text.setFillColor(Color::Black);
    entered_user_password_text.setFont(font);

    bool is_password_typed = false;


    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                curruser.set_id(0);
                return false;
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    curruser.set_id(0);
                    return false;
                    window.close();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                    grabbedWindow = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    grabbedWindow = false;
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (grabbedWindow)
                    window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
            }


            //check if username text bar is pressed
            if (Mouse::getPosition(window).x >= 333 &&
                Mouse::getPosition(window).x <= 663 &&
                Mouse::getPosition(window).y >= 370 &&
                Mouse::getPosition(window).y <= 443) {
                if (event.type == Event::MouseButtonPressed)
                {
                    text_bar_sprite.setScale(1.05, 1.05);
                    text_bar2_sprite.setScale(1, 1);
                    is_username_typed = true;
                    is_password_typed = false;
                }

            }


            //check if password text bar is pressed
            if (Mouse::getPosition(window).x >= 333 &&
                Mouse::getPosition(window).x <= 663 &&
                Mouse::getPosition(window).y >= 490 &&
                Mouse::getPosition(window).y <= 563) {
                if (event.type == Event::MouseButtonPressed)
                {
                    text_bar2_sprite.setScale(1.05, 1.05);
                    text_bar_sprite.setScale(1, 1);
                    is_username_typed = false;
                    is_password_typed = true;
                }
            }


            //check if back button is pressed
            if (Mouse::getPosition(window).x >= 70 &&
                Mouse::getPosition(window).x <= 170 &&
                Mouse::getPosition(window).y >= 100 &&
                Mouse::getPosition(window).y <= 190)
            {
                back_button_sprite.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {
                    is_username_typed = false;
                    is_password_typed = false;
                    is_username_error_typed = false;
                    is_invadlid_username_or_password_typed = false;

                    //functions to clear the username and password when going back 
                    UsernameInput.clear();
                    entered_user_username_text.setString("");
                    PasswordInput.clear();
                    entered_user_password_text.setString("");

                    return false;
                }
            }
            else
                back_button_sprite.setScale(1, 1);


            // register button is pressed 
            if (Mouse::getPosition(window).x >= 370 &&
                Mouse::getPosition(window).x <= 623 &&
                Mouse::getPosition(window).y >= 610 &&
                Mouse::getPosition(window).y <= 683 && x == 1) {

                register_button_sprite.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {

                    if (is_username_availble(UsernameInput, PasswordInput) == false) {
                        is_username_error_typed = true;
                    }
                    else {

                        is_username_error_typed = false;
                        user_regestration.add_new_user(UsernameInput, PasswordInput, users);
                        curruser = user_regestration;
                        users.push_back(user_regestration);
                        cout << user_regestration.get_id();
                        print_user_to_file(user_regestration);
                        UsernameInput.clear();
                        entered_user_username_text.setString("");
                        PasswordInput.clear();
                        entered_user_password_text.setString("");

                        return true;

                    }
                }

            }
            else
                register_button_sprite.setScale(1, 1);

            // login button is pressed 
            if (Mouse::getPosition(window).x >= 370 &&
                Mouse::getPosition(window).x <= 623 &&
                Mouse::getPosition(window).y >= 610 &&
                Mouse::getPosition(window).y <= 683 && x == 2) {

                login_button_sprite.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {

                    if (username_password_match(UsernameInput, PasswordInput) == -1) {

                        is_invadlid_username_or_password_typed = true;
                    }
                    else {
                        curreent_user_index = username_password_match(UsernameInput, PasswordInput);
                        curruser.set_username(users[curreent_user_index].get_username());
                        curruser.set_password(users[curreent_user_index].get_password());
                        curruser.set_id(users[curreent_user_index].get_id());
                        return true;
                    }

                }

            }
            else
                login_button_sprite.setScale(1, 1);


            // keyboard events

            if (event.type == Event::TextEntered && is_username_typed == true)
            {
                if (event.text.unicode == '\b' && UsernameInput.getSize() > 0) // function to delete char when backspace is pressed
                    UsernameInput.erase(UsernameInput.getSize() - 1, 1);
                else if (event.text.unicode < 128)
                    UsernameInput += static_cast<char>(event.text.unicode);
                entered_user_username_text.setString(UsernameInput);
                if (UsernameInput.getSize() > 19) // function to put limit to entered string 
                    UsernameInput.erase(UsernameInput.getSize() - 1, 1);

            }


            else if (event.type == Event::TextEntered && is_password_typed == true)
            {
                if (event.text.unicode == '\b' && PasswordInput.getSize() > 0) // function to delete char when backspace is pressed
                    PasswordInput.erase(PasswordInput.getSize() - 1, 1);
                else if (event.text.unicode < 128)
                    PasswordInput += static_cast<char>(event.text.unicode);
                if (PasswordInput.getSize() > 19) // function to put limit to entered string 
                    PasswordInput.erase(PasswordInput.getSize() - 1, 1);

                entered_user_password_text.setString(PasswordInput);

            }



        }


        // draw functions
        window.clear();
        window.draw(background_sprite);
        window.draw(text_bar_sprite);
        window.draw(text_bar2_sprite);
        window.draw(username_text);
        window.draw(password_text);
        window.draw(entered_user_username_text);
        window.draw(entered_user_password_text);
        window.draw(back_button_sprite);
        if (x == 1)
            window.draw(register_button_sprite);
        else
            window.draw(login_button_sprite);
        if (is_username_error_typed == true || is_invadlid_username_or_password_typed)
            window.draw(username_error_text);
        window.display();

    }

}

bool StartPage::is_username_availble(string username, string password) {
    int x = 0;
    if (username.length() < 3 || password.length() < 3)
        x++;
    for (int i = 0; i < users.size(); i++) {
        if (users[i].get_username() == username)
            x++;
    }
    if (x == 0)
        return true;
    else return false;
}

int StartPage::username_password_match(string username, string password) {
    /* if it return -1 then username or password doesnt match else username and password
    are correct and the returned number is the index of the logged in user*/

    int x = -1;
    for (int i = 0; i < users.size(); i++) {
        if (users[i].get_username() == username && users[i].get_password() == password) {
            x = i;
            break;
        }

    }

    return x;

}

void StartPage::print_user_to_file(User entered_user) {
    ofstream out("files\\users_data_file.txt", ios::app);
    out << entered_user.get_username() << endl;
    out << entered_user.get_password() << endl;
    out << entered_user.get_id() << endl;
    out.close();

}

vector<User> StartPage::read_users_from_file() {

    vector<User> user_vector;
    User current_user;
    string current_username, current_password;
    double current_id;

    ifstream in("files\\users_data_file.txt");
    while (!in.eof()) {
        in >> current_username;
        in >> current_password;
        in >> current_id;
        current_user.set_username(current_username);
        current_user.set_password(current_password);
        current_user.set_id(current_id);
        user_vector.push_back(current_user);
    }
    in.close();
    return user_vector;
}