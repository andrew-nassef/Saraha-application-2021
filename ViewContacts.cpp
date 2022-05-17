#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include <locale>
#include <stack>
#include "Contacts.h"
#include"Textbox.h"
#include"StartPage.h"
#include"User.h"
#include"MessagesPage.h"

#define  DELETE_KEY 8
#define  ENTER_KEY  13
#define  ESCAPE_KEY 27
#define  SPACE 17

using namespace sf;
using namespace std;

vector<User>users;
vector<string> v;
vector<string> userContacts;

string getUsername(vector<User>users, double id) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].get_id() == id) {
            return users[i].get_username();
            break;
        }
    }
}
double getContactId(vector<User>users, string username) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].get_username() == username) {
            return users[i].get_id();
            break;
        }
    }
}

void undo() {
    stack<string>s;
    string ch;
    fstream my_file;
    my_file.open("files\\Messages.txt", ios::in);
    if (!my_file) {
        cout << "Not Found";
    }
    else {

        while (getline(my_file, ch)) {
            s.push(ch);
            cout << s.top();
            cout << "\n";
            if (my_file.eof())
                break;
        }

        for (int i = 0; i <= 4; i++) {
            s.pop();

        }

        stack<string>s2;
        while (!s.empty()) {
            s2.push(s.top());
            s.pop();

        }
        ofstream newfile;
        newfile.open("files\\Messages.txt", std::ofstream::out | std::ofstream::trunc);
        while (!s2.empty()) {
            newfile << s2.top() << '\n';
            s2.pop();

        }


    }
}

vector<string> Contacts::search(string username, int currentUser_id) {
    vector <string>findContacts;
    fstream sfile;
    Font font;
    font.loadFromFile("Fonts\\Basic-Regular.ttf");
    sfile.open("files\\text.txt", ios::in);
    string line;
    int count = 0;

    int i = 0;  bool flag = false;

    while (1) {
        sfile >> line;
        if (sfile.eof())
            break;
        else if (i % 2 == 0) {
            flag = false;
            if (line == to_string((int)currentUser_id)) {
                flag = true;

            }
        }
        else {
            if (flag) {
                if (line == username) {
                    // cout << line;
                    findContacts.push_back(line);
                    count++;
                }

            }
        }



        i++;

    }
    if (count == 0) {
        //cout << "NOT FOUND";
    }
    return findContacts;
}

void Contacts::viewUserContacts(Text contacts[], RenderWindow& Window, vector<string> v, bool myContacts) {
    Font font;
    font.loadFromFile("Fonts\\Basic-Regular.ttf");


    for (int i = 0; i < v.size(); i++) {
        contacts[i].setString(v[i]);
        contacts[i].setFont(font);
        contacts[i].setCharacterSize(38);
        contacts[i].setPosition(453, 355 + 40 * i);
        Window.draw(contacts[i]);

    }
}

void Contacts::viewMyContacts(Text contacts[], RenderWindow& Window, vector<string> v, bool myContacts, int p) {
    Font font;
    font.loadFromFile("Fonts\\Basic-Regular.ttf");
    if (p >= 6) {

        for (int i = p - 6; i < p; i++) {

            contacts[i].setString(v[i]);
            contacts[i].setFont(font);
            contacts[i].setCharacterSize(38);
            contacts[i].setPosition(453, 375 + 40 * (i - p + 6));
            contacts[p - 1].setFillColor(Color::Red);
            Window.draw(contacts[i]);
            contacts[p - 1].setFillColor(Color::Blue);
        }
    }
    else {
        int size;
        if (v.size() > 6) {
            size = 6;
        }
        else
        {
            size = v.size();
        }
        for (int i = 0; i < size; i++) {
            contacts[i].setString(v[i]);
            contacts[i].setFont(font);
            contacts[i].setCharacterSize(38);
            if (myContacts)
                contacts[i].setPosition(453, 375 + 40 * i);
            else
                contacts[i].setPosition(453, 355 + 40 * i);
            Window.draw(contacts[i]);

        }
    }



}

void sendmsg(double sender, string reciever, string msg, string senderUsername) {

    bool favorite = false;
    string senderID = to_string(sender);
    string recieverUsername = reciever;
    string messege = msg;
    string username = senderUsername;
    ifstream file;
    file.open("files\\Messages.txt");

    ofstream newfile;

    newfile.open("files\\Messages.txt", ios::out | ios::app | ios::binary | ios::ate);
    newfile << senderID << '\n';
    newfile << username << '\n';
    newfile << recieverUsername << '\n';
    newfile << messege << '\n';
    newfile << favorite << '\n';


    newfile.close();


}

int Contacts::viewSend(User curruser)
{

    bool grabbedWindow = false;
    Vector2i grabbedOffset;
    Textbox textmsg(20, false);
    Textbox ContactSearch(20, false);
    string  contactUsername;
    cout << curruser.get_id();
    double  currentUser_id = curruser.get_id();
    string currentUsername = getUsername(users, currentUser_id);

    StartPage s;
    users = s.read_users_from_file();

    Font arial;
    arial.loadFromFile("Fonts\\Basic-Regular.ttf");
    textmsg.setfont(arial);
    ContactSearch.setfont(arial);

    Texture background, buttons;
    background.loadFromFile("Textures\\design.png");
    buttons.loadFromFile("Textures\\buttons.png");

    Sprite back_button_sprite, messages, contacts, text_bar_sprite, backgroundSprite, textBar, searchtxt, undoButton,
        sendButton, addButton, chat;

    backgroundSprite.setTexture(background);
    back_button_sprite.setTexture(buttons);
    text_bar_sprite.setTexture(buttons);
    textBar.setTexture(buttons);
    searchtxt.setTexture(buttons);

    undoButton.setTexture(buttons);
    sendButton.setTexture(buttons);
    addButton.setTexture(buttons);
    chat.setTexture(buttons);
    messages.setTexture(buttons);
    contacts.setTexture(buttons);

    back_button_sprite.setTextureRect(IntRect(0, 450, 100, 94));
    messages.setTextureRect(IntRect(106, 455, 85, 75));
    contacts.setTextureRect(IntRect(200, 455, 85, 75));
    text_bar_sprite.setTextureRect(IntRect(0, 375, 330, 73));
    textBar.setTextureRect(IntRect(0, 375, 330, 73));
    searchtxt.setTextureRect(IntRect(654, 449, 36, 36));

    sendButton.setTextureRect(IntRect(252, 74, 253, 73));
    undoButton.setTextureRect(IntRect(252, 149, 253, 73));
    addButton.setTextureRect(IntRect(252, 222, 253, 73));
    chat.setTextureRect(IntRect(15, 563, 663, 439));


    back_button_sprite.setPosition(60, 60);
    messages.setPosition(65, 168);
    contacts.setPosition(164, 168);
    text_bar_sprite.setPosition(333, 300);
    textBar.setPosition(Vector2f(232, 300));
    searchtxt.setPosition(Vector2f(600, 320));

    undoButton.setPosition(30, 303);
    sendButton.setPosition(30, 411);
    addButton.setPosition(380, 630);
    chat.setPosition(312, 294);

    Font font;
    font.loadFromFile("Fonts\\Basic-Regular.ttf");

    Text User;
    User.setFont(font);
    User.setString("Enter User Name");
    User.setCharacterSize(30);
    User.setPosition(390, 400);
    User.setFillColor(Color(61, 144, 227));


    Text message;
    message.setFont(font);
    message.setString("Enter a message");
    message.setCharacterSize(30);
    message.setPosition(30, 95);

    Text enterStr;
    enterStr.setFont(font);
    enterStr.setCharacterSize(24);
    enterStr.setFillColor(Color::Black);
    enterStr.setPosition(350, 330);

    Text contactsText[50];
    Text contactsText2[50];

    for (int i = 0; i < 50; i++) {
        contactsText[i].setFillColor(Color::Blue);
        contactsText2[i].setFillColor(Color::Blue);
    }

    string line;
    list<Text> textList;
    Text text("", font, 50);
    ifstream file;
    file.open("files\\text.txt");
    ofstream newfile;
    newfile.open("files\\text.txt", ios::out | ios::app | ios::binary | ios::ate);

    textmsg.setfont(arial);
    textmsg.setposition({ 100,100 });
    bool Contacts = true, addContact = false;
    bool sendmessage = false, viewContact = false;
    bool flag = true;

    while (true) {

        bool isSearch = false;
        string enterUsername;
        vector <string>searchVector;

        if (Contacts) {

            v.clear();
            string ch;
            fstream my_file;
            my_file.open("files\\text.txt", ios::in);

            if (!my_file) {
                cout << "Not Found";
            }
            else {
                int i = 0;  bool flag = false;
                while (1) {
                    my_file >> ch;
                    if (my_file.eof())
                        break;
                    if (i % 2 == 0) {
                        flag = false;
                        if (ch == to_string((int)currentUser_id)) {
                            flag = true;
                        }
                    }
                    else {

                        if (flag)
                            v.push_back(ch);
                    }
                    i++;
                }
            }

            int p = -1;
            string str;
            locale loc;
            enterStr.setPosition(355, 320);

            RenderWindow contactsWindow(VideoMode(1000, 800), "", sf::Style::None);

            while (contactsWindow.isOpen())
            {
                Event event;
                while (contactsWindow.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        contactsWindow.close();
                        return 0;
                    }
                    else if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            contactsWindow.close();
                            return 0;
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            grabbedOffset = contactsWindow.getPosition() - sf::Mouse::getPosition();
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
                            contactsWindow.setPosition(sf::Mouse::getPosition() + grabbedOffset);
                    }

                    //when the mouse hovers over meesages icon.
                    if (sf::Mouse::getPosition(contactsWindow).x >= 65 && sf::Mouse::getPosition(contactsWindow).y >= 167
                        && sf::Mouse::getPosition(contactsWindow).x <= 141 && sf::Mouse::getPosition(contactsWindow).y <= 238
                        )
                    {
                        messages.setScale(1.11, 1.11);
                        if (event.type == Event::MouseButtonPressed)
                        {
                            return 1;
                        }
                    }
                    else
                        messages.setScale(1, 1);

                    //when the mouse hovers over contacts icon.
                    if (sf::Mouse::getPosition(contactsWindow).x >= 162 && sf::Mouse::getPosition(contactsWindow).y >= 167
                        && sf::Mouse::getPosition(contactsWindow).x <= 238 && sf::Mouse::getPosition(contactsWindow).y <= 238
                        )
                    {
                        contacts.setScale(1.11, 1.11);
                    }
                    else
                        contacts.setScale(1, 1);

                    int Mx = Mouse::getPosition(contactsWindow).x;
                    int My = Mouse::getPosition(contactsWindow).y;

                    switch (event.type) {
                    case Event::KeyPressed:

                        if (Keyboard::isKeyPressed(Keyboard::Down))
                        {
                            contactsText[p].setFillColor(Color::Blue);
                            p++;
                            if (p > v.size())
                                p = 0;
                            contactsText[p].setFillColor(Color::Red);
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Up))
                        {
                            contactsText[p].setFillColor(Color::Blue);
                            p--;
                            if (p < 0)
                                p = v.size();
                            contactsText[p].setFillColor(Color::Red);
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                            if (isSearch) {
                                if (!searchVector.empty()) {
                                    currentUsername = searchVector[p];
                                }
                            }
                            else {
                                if (!v.empty()) {
                                    currentUsername = v[p];
                                }
                            }

                            sendmessage = true;
                            Contacts = false;
                            contactsWindow.close();
                        }

                        contactsWindow.setKeyRepeatEnabled(false);
                        break;
                    case Event::MouseButtonPressed:
                        if (Mx > 375 && Mx < 630 && My>625 && My < 710) {
                            Contacts = false;
                            addContact = true;
                            contactsWindow.close();
                        }
                        if (Mx > 600 && Mx < 640 && My>320 && My < 360) {
                            isSearch = true;
                        }

                        break;

                    case Event::TextEntered:

                        if (event.text.unicode == 0x000008) {
                            if (!str.empty())
                                str.pop_back();
                        }
                        else if (event.text.unicode < 128
                            && event.text.unicode != DELETE_KEY
                            && event.text.unicode != ENTER_KEY
                            && event.text.unicode != ESCAPE_KEY
                            && !isspace(event.text.unicode, loc)) {

                            str.push_back(event.text.unicode);
                        }

                        break;


                    default:
                        break;
                    }
                }

                enterStr.setString(str);
                enterStr.setPosition(350, 330);

                contactsWindow.clear();
                contactsWindow.draw(backgroundSprite);

                if (isSearch && !str.empty()) {
                    searchVector = search(str, currentUser_id);
                    if (searchVector.empty()) {
                        contactsText[0].setString("Not Found");
                        contactsText[0].setFont(font);
                        contactsText[0].setCharacterSize(35);
                        contactsText[0].setPosition(410, 375);
                        contactsWindow.draw(contactsText[0]);
                    }
                    else {
                        for (int i = 0; i < searchVector.size(); i++) {
                            contactsText[i].setString(searchVector[i]);
                            contactsText[i].setFont(font);
                            contactsText[i].setCharacterSize(35);
                            contactsText[i].setPosition(430, 375 + 40 * i);
                            contactsWindow.draw(contactsText[i]);
                        }

                    }

                }
                else
                    viewMyContacts(contactsText, contactsWindow, v, true, p);

                contactsWindow.draw(addButton);
                contactsWindow.draw(contacts);
                contactsWindow.draw(messages);
                contactsWindow.draw(text_bar_sprite);
                contactsWindow.draw(searchtxt);
                contactsWindow.draw(enterStr);
                contactsWindow.display();
            }
        }

        else if (addContact) {

            RenderWindow addContactWindow(VideoMode(1000, 800), "", sf::Style::None);

            ifstream file;
            file.open("files\\text.txt");

            ofstream newfile;

            newfile.open("files\\text.txt", ios::out | ios::app | ios::binary | ios::ate);
            string str = "";

            while (addContactWindow.isOpen())
            {

                Event event;
                while (addContactWindow.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        Contacts = true;
                        addContact = false;
                        addContactWindow.close();
                    }
                    else if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            Contacts = true;
                            addContact = false;
                            addContactWindow.close();
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            grabbedOffset = addContactWindow.getPosition() - sf::Mouse::getPosition();
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
                            addContactWindow.setPosition(sf::Mouse::getPosition() + grabbedOffset);
                    }

                    if (Mouse::getPosition(addContactWindow).x >= 60 &&
                        Mouse::getPosition(addContactWindow).x <= 160 &&
                        Mouse::getPosition(addContactWindow).y >= 60 &&
                        Mouse::getPosition(addContactWindow).y <= 155) {
                        back_button_sprite.setScale(1.08, 1.08);
                        if (event.type == sf::Event::MouseButtonPressed)
                        {
                            Contacts = true;
                            addContact = false;
                            addContactWindow.close();
                        }
                    }
                    else
                        back_button_sprite.setScale(1, 1);

                    //when the mouse hovers over meesages icon.
                    if (sf::Mouse::getPosition(addContactWindow).x >= 65 && sf::Mouse::getPosition(addContactWindow).y >= 167
                        && sf::Mouse::getPosition(addContactWindow).x <= 141 && sf::Mouse::getPosition(addContactWindow).y <= 238
                        )
                    {
                        messages.setScale(1.11, 1.11);
                        if (event.type == Event::MouseButtonPressed)
                        {
                            return 1;
                        }
                    }
                    else
                        messages.setScale(1, 1);

                    //when the mouse hovers over contacts icon.
                    if (sf::Mouse::getPosition(addContactWindow).x >= 162 && sf::Mouse::getPosition(addContactWindow).y >= 167
                        && sf::Mouse::getPosition(addContactWindow).x <= 238 && sf::Mouse::getPosition(addContactWindow).y <= 238
                        )
                    {
                        contacts.setScale(1.11, 1.11);
                    }
                    else
                        contacts.setScale(1, 1);

                    int Mx = Mouse::getPosition(addContactWindow).x;
                    int My = Mouse::getPosition(addContactWindow).y;
                    locale loc;

                    switch (event.type) {

                    case Event::MouseButtonPressed:

                        if (Mx > 375 && Mx < 640 && My>625 && My < 720) {

                            if (newfile.is_open())
                            {
                                newfile << currentUser_id << '\n';
                                newfile << str << '\n';
                                cout << "new user is added\n";
                            }
                            newfile.close();
                        }
                        break;

                    case Event::TextEntered:

                        if (event.text.unicode == 0x000008) {
                            if (!str.empty())
                                str.pop_back();
                        }
                        else if (event.text.unicode < 128
                            && event.text.unicode != DELETE_KEY
                            && event.text.unicode != ENTER_KEY
                            && event.text.unicode != ESCAPE_KEY
                            && !isspace(event.text.unicode, loc)) {

                            str.push_back(event.text.unicode);
                        }

                        break;

                    default:
                        break;
                    }
                }




                enterStr.setString(str);

                addContactWindow.clear();
                addContactWindow.draw(backgroundSprite);
                addContactWindow.draw(contacts);
                addContactWindow.draw(messages);
                addContactWindow.draw(text_bar_sprite);
                addContactWindow.draw(enterStr);
                addContactWindow.draw(addButton);
                addContactWindow.draw(User);
                addContactWindow.draw(back_button_sprite);
                addContactWindow.display();
            }
        }

        else if (sendmessage) {

            RenderWindow Sendmessege(VideoMode(1000, 800), "", sf::Style::None);
            while (Sendmessege.isOpen())
            {
                Event event;

                while (Sendmessege.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        Contacts = true;
                        addContact = false;
                        Sendmessege.close();
                    }
                    else if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            Contacts = true;
                            addContact = false;
                            Sendmessege.close();
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            grabbedOffset = Sendmessege.getPosition() - sf::Mouse::getPosition();
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
                            Sendmessege.setPosition(sf::Mouse::getPosition() + grabbedOffset);
                    }

                    if (Mouse::getPosition(Sendmessege).x >= 60 &&
                        Mouse::getPosition(Sendmessege).x <= 160 &&
                        Mouse::getPosition(Sendmessege).y >= 60 &&
                        Mouse::getPosition(Sendmessege).y <= 155) {
                        back_button_sprite.setScale(1.08, 1.08);
                        if (event.type == sf::Event::MouseButtonPressed)
                        {
                            Contacts = true;
                            addContact = false;
                            Sendmessege.close();
                        }
                    }
                    else
                        back_button_sprite.setScale(1, 1);

                    //when the mouse hovers over meesages icon.
                    if (sf::Mouse::getPosition(Sendmessege).x >= 65 && sf::Mouse::getPosition(Sendmessege).y >= 167
                        && sf::Mouse::getPosition(Sendmessege).x <= 141 && sf::Mouse::getPosition(Sendmessege).y <= 238
                        )
                    {
                        messages.setScale(1.11, 1.11);
                        if (event.type == Event::MouseButtonPressed)
                        {
                            return 1;
                        }
                    }
                    else
                        messages.setScale(1, 1);

                    //when the mouse hovers over contacts icon.
                    if (sf::Mouse::getPosition(Sendmessege).x >= 162 && sf::Mouse::getPosition(Sendmessege).y >= 167
                        && sf::Mouse::getPosition(Sendmessege).x <= 238 && sf::Mouse::getPosition(Sendmessege).y <= 238
                        )
                    {
                        contacts.setScale(1.11, 1.11);
                    }
                    else
                        contacts.setScale(1, 1);

                    if (sf::Mouse::getPosition(Sendmessege).x >= 30 && sf::Mouse::getPosition(Sendmessege).y >= 303
                        && sf::Mouse::getPosition(Sendmessege).x <= 282 && sf::Mouse::getPosition(Sendmessege).y <= 375
                        )
                    {
                        undoButton.setScale(1.08, 1.08);
                        if (event.type == Event::MouseButtonPressed)
                        {
                            undo();
                        }
                    }
                    else
                        undoButton.setScale(1, 1);

                    if (sf::Mouse::getPosition(Sendmessege).x >= 30 && sf::Mouse::getPosition(Sendmessege).y >= 411
                        && sf::Mouse::getPosition(Sendmessege).x <= 282 && sf::Mouse::getPosition(Sendmessege).y <= 483
                        )
                    {
                        sendButton.setScale(1.08, 1.08);
                        if (event.type == Event::MouseButtonPressed)
                        {
                            double id = getContactId(users, currentUsername);
                            string s;
                            s = textmsg.gettext();
                            sendmsg(currentUser_id, contactUsername, s, currentUsername);
                            cout << "Message sent\n";
                        }
                    }
                    else
                        sendButton.setScale(1, 1);

                    int Mx = Mouse::getPosition().x;
                    int My = Mouse::getPosition().y;

                    switch (event.type) {

                    case Event::MouseButtonPressed:
                        if (Mx > 315 && Mx < 970 && My>300 && My < 500)
                        {
                            textmsg.selected(true);
                        }
                        break;

                    case Event::TextEntered:
                        textmsg.validateInput(event);
                        break;

                    default:
                        break;
                    }
                }

                Sendmessege.clear();
                Sendmessege.draw(backgroundSprite);
                Sendmessege.draw(contacts);
                Sendmessege.draw(messages);
                Sendmessege.draw(undoButton);
                Sendmessege.draw(sendButton);
                Sendmessege.draw(back_button_sprite);
                Sendmessege.draw(chat);
                textmsg.drawTo(Sendmessege);
                Sendmessege.display();
            }
        }

        else if (viewContact) {

            userContacts.clear();
            double id = getContactId(users, currentUsername);
            string ch;
            fstream my_file;
            my_file.open("text.txt", ios::in);
            if (!my_file) {
                cout << "Not Found";
            }
            else {
                int i = 0;  bool flag = false;
                while (1) {
                    my_file >> ch;
                    if (my_file.eof())
                        break;
                    if (i % 2 == 0) {
                        flag = false;
                        if (ch == to_string((int)id)) {
                            flag = true;
                        }
                    }
                    else {

                        if (flag)
                            userContacts.push_back(ch);
                    }
                    i++;
                }
            }


            RenderWindow ViewContact(VideoMode(1000, 800), "", sf::Style::None);
            while (ViewContact.isOpen())
            {
                Event event;

                while (ViewContact.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        Contacts = true;
                        addContact = false;
                        ViewContact.close();
                    }
                    else if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            Contacts = true;
                            addContact = false;
                            ViewContact.close();
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            grabbedOffset = ViewContact.getPosition() - sf::Mouse::getPosition();
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
                            ViewContact.setPosition(sf::Mouse::getPosition() + grabbedOffset);
                    }

                    if (Mouse::getPosition(ViewContact).x >= 60 &&
                        Mouse::getPosition(ViewContact).x <= 160 &&
                        Mouse::getPosition(ViewContact).y >= 60 &&
                        Mouse::getPosition(ViewContact).y <= 155) {
                        back_button_sprite.setScale(1.08, 1.08);
                        if (event.type == sf::Event::MouseButtonPressed)
                        {
                            Contacts = true;
                            addContact = false;
                            ViewContact.close();
                        }
                    }
                    else
                        back_button_sprite.setScale(1, 1);

                    //when the mouse hovers over meesages icon.
                    if (sf::Mouse::getPosition(ViewContact).x >= 65 && sf::Mouse::getPosition(ViewContact).y >= 167
                        && sf::Mouse::getPosition(ViewContact).x <= 141 && sf::Mouse::getPosition(ViewContact).y <= 238
                        )
                    {
                        messages.setScale(1.11, 1.11);
                        if (event.type == Event::MouseButtonPressed)
                        {
                            return 1;
                        }
                    }
                    else
                        messages.setScale(1, 1);

                    //when the mouse hovers over contacts icon.
                    if (sf::Mouse::getPosition(ViewContact).x >= 162 && sf::Mouse::getPosition(ViewContact).y >= 167
                        && sf::Mouse::getPosition(ViewContact).x <= 238 && sf::Mouse::getPosition(ViewContact).y <= 238
                        )
                    {
                        contacts.setScale(1.11, 1.11);
                    }
                    else
                        contacts.setScale(1, 1);

                    int Mx = Mouse::getPosition().x;
                    int My = Mouse::getPosition().y;

                    switch (event.type) {

                    case Event::MouseButtonPressed:

                        if (sf::Mouse::getPosition(ViewContact).x >= 65
                            && sf::Mouse::getPosition(ViewContact).y >= 167
                            && sf::Mouse::getPosition(ViewContact).x <= 141
                            && sf::Mouse::getPosition(ViewContact).y <= 238
                            ) {
                            sendmessage = true;
                            viewContact = false;
                            ViewContact.close();
                        }
                        break;

                    default:
                        break;
                    }
                }

                ViewContact.clear();
                ViewContact.draw(backgroundSprite);
                ViewContact.draw(back_button_sprite);
                ViewContact.draw(contacts);
                ViewContact.draw(messages);
                viewUserContacts(contactsText2, ViewContact, userContacts, false);

                ViewContact.display();
            }
        }

    }

    return 0;
}