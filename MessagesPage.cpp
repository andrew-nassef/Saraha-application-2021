#include "MessagesPage.h"
#include "StartPage.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include "User.h"
#include <vector>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;


MessagesPage::MessagesPage(User curruser)
{
    this->curruser1 = curruser;
}

int MessagesPage::Show_Page()
{
    RenderWindow window1(sf::VideoMode(1000, 800), "", sf::Style::None);
    window1.setKeyRepeatEnabled(false);
    Vector2i grabbedOffset;
    bool grabbedWindow = false;

    Messages tmp, tmp1, tmp2;
    tmp.id = "Sorry,";
    tmp.message = "You have no recieved messages";
    tmp.reciever = "Sorry,";
    tmp.sender = "Sorry,";
    tmp.isFavorite = 0;
    tmp1.id = "Sorry,";
    tmp1.message = "You have no sent messages";
    tmp1.reciever = "Sorry,";
    tmp1.sender = "Sorry,";
    tmp1.isFavorite = 0;
    tmp2.id = "Sorry,";
    tmp2.message = "You have no favorite messages";
    tmp2.reciever = "Sorry,";
    tmp2.sender = "Sorry,";
    tmp2.isFavorite = 0;

    recived_msg.push_back(tmp);
    sent_msg.push_back(tmp1);
    fav_msg.push(tmp2);

    int msgindex = 1, whichvec = 0;

    Texture design1, buttons1;

    design1.loadFromFile("Textures\\design.png");
    buttons1.loadFromFile("Textures\\buttons.png");

    Sprite design, messages, contacts, buttonf, buttons, buttont, star, stary, arrowr, arrowl, chat;

    design.setTexture(design1);
    buttonf.setTexture(buttons1);
    buttons.setTexture(buttons1);
    buttont.setTexture(buttons1);
    buttonf.setTextureRect(IntRect(0, 0, 253, 73));
    buttons.setTextureRect(IntRect(0, 74, 253, 73));
    buttont.setTextureRect(IntRect(0, 148, 253, 73));
    messages.setTexture(buttons1);
    contacts.setTexture(buttons1);
    chat.setTexture(buttons1);
    star.setTexture(buttons1);
    stary.setTexture(buttons1);
    arrowr.setTexture(buttons1);
    arrowl.setTexture(buttons1);
    messages.setTextureRect(IntRect(106, 455, 85, 75));
    contacts.setTextureRect(IntRect(200, 455, 85, 75));
    chat.setTextureRect(IntRect(15, 563, 663, 439));
    star.setTextureRect(IntRect(313, 461, 49, 50));
    stary.setTextureRect(IntRect(590, 461, 49, 50));
    arrowl.setTextureRect(IntRect(397, 451, 76, 75));
    arrowr.setTextureRect(IntRect(500, 453, 76, 75));

    messages.setPosition(65, 168);
    contacts.setPosition(164, 168);
    chat.setPosition(312, 294);
    buttonf.setPosition(30, 303);
    buttons.setPosition(30, 411);
    buttont.setPosition(30, 521);
    arrowl.setPosition(366, 641);
    arrowr.setPosition(691, 643);
    star.setPosition(908, 310);
    stary.setPosition(908, 310);

    readFile();

    while (window1.isOpen())
    {
        if (whichvec == 0)
        {
            if (recived_msg.size() <= 1)
                msgindex = 0;
            currmsg = recived_msg[msgindex];
        }
        else if (whichvec == 1)
        {
            if (sent_msg.size() <= 1)
                msgindex = 0;
            currmsg = sent_msg[msgindex];
        }
        else if (whichvec == 2)
        {
            if (fav_msg.size() <= 1)
                msgindex = 0;
            currmsg = fav_msg.top();
        }

       

        Font font;
        font.loadFromFile("Fonts\\Basic-Regular.TTF");

        Text  msg, id, reciever;
        id.setString(currmsg.id);
        id.setCharacterSize(20);
        id.setFillColor(Color::White);
        id.setPosition(374, 305);
        id.setFont(font);

        reciever.setString(currmsg.reciever);
        reciever.setCharacterSize(20);
        reciever.setFillColor(Color::White);
        reciever.setPosition(374, 305);
        reciever.setFont(font);


        msg.setString(currmsg.message);
        msg.setCharacterSize(25);
        msg.setFillColor(Color::White);
        msg.setPosition(327, 350);
        msg.setFont(font);

        Event event;

        while (window1.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window1.close();
                return 3;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window1.close();
                    return 3;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    grabbedOffset = window1.getPosition() - sf::Mouse::getPosition();
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
                    window1.setPosition(sf::Mouse::getPosition() + grabbedOffset);
            }

            //when the mouse hovers over meesages icon.
            if (sf::Mouse::getPosition(window1).x >= 65 && sf::Mouse::getPosition(window1).y >= 167
                && sf::Mouse::getPosition(window1).x <= 141 && sf::Mouse::getPosition(window1).y <= 238
                )
            {
                messages.setScale(1.11, 1.11);
            }
            else
                messages.setScale(1, 1);

            //when the mouse hovers over contacts icon.
            if (sf::Mouse::getPosition(window1).x >= 162 && sf::Mouse::getPosition(window1).y >= 167
                && sf::Mouse::getPosition(window1).x <= 238 && sf::Mouse::getPosition(window1).y <= 238
                )
            {
                contacts.setScale(1.11, 1.11);
                if (event.type == Event::MouseButtonPressed)
                {
                    return 2;
                }
            }
            else
                contacts.setScale(1, 1);

             // when the recieved button is pressed
            if (sf::Mouse::getPosition(window1).x >= 30 && sf::Mouse::getPosition(window1).y >= 303
                && sf::Mouse::getPosition(window1).x <= 282 && sf::Mouse::getPosition(window1).y <= 375
                )
            {
                buttonf.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {
                    whichvec = 0;
                    msgindex = 1;
                    for (int i = 0; i < fav_msg_sub.size(); i++)
                    {
                        cout << i << endl;
                        fav_msg.push(fav_msg_sub.top());
                        fav_msg_sub.pop();
                    }
                }
            }
            else
                buttonf.setScale(1, 1);

            // when the sent button is pressed
            if (sf::Mouse::getPosition(window1).x >= 30 && sf::Mouse::getPosition(window1).y >= 411
                && sf::Mouse::getPosition(window1).x <= 282 && sf::Mouse::getPosition(window1).y <= 483
                )
            {
                buttons.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {
                    msgindex = 1;
                    whichvec = 1;
                    for (int i = 0; i < fav_msg_sub.size(); i++)
                    {
                        cout << i << endl;
                        fav_msg.push(fav_msg_sub.top());
                        fav_msg_sub.pop();
                    }
                }
            }
            else
                buttons.setScale(1, 1);

            // when the favorite button is pressed
            if (sf::Mouse::getPosition(window1).x >= 30 && sf::Mouse::getPosition(window1).y >= 521
                && sf::Mouse::getPosition(window1).x <= 282 && sf::Mouse::getPosition(window1).y <= 593
                )
            {
                buttont.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {
                    whichvec = 2;
                    msgindex = 1;
                    for (int i = 0; i < fav_msg_sub.size(); i++)
                    {
                        cout << i << endl;
                        fav_msg.push(fav_msg_sub.top());
                        fav_msg_sub.pop();
                    }
                }
            }
            else
                buttont.setScale(1, 1);

            // when the right arrow button is pressed
            if (sf::Mouse::getPosition(window1).x >= 691 && sf::Mouse::getPosition(window1).y >= 641
                && sf::Mouse::getPosition(window1).x <= 765 && sf::Mouse::getPosition(window1).y <= 717
                )
            {
                arrowr.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {
                    if (whichvec == 0 && msgindex < recived_msg.size() - 1)
                        msgindex++;
                    if (whichvec == 1 && msgindex < sent_msg.size() - 1)
                        msgindex++;
                    if (whichvec == 2 && msgindex < fav_msg.size() + fav_msg_sub.size() - 1)
                    {
                        msgindex++;
                        fav_msg_sub.push(fav_msg.top());
                        fav_msg.pop();
                    }
                }
            }
            else
                arrowr.setScale(1, 1);

            // when the left arrow button is pressed
            if (sf::Mouse::getPosition(window1).x >= 366 && sf::Mouse::getPosition(window1).y >= 643
                && sf::Mouse::getPosition(window1).x <= 442 && sf::Mouse::getPosition(window1).y <= 719
                )
            {
                arrowl.setScale(1.08, 1.08);
                if (event.type == Event::MouseButtonPressed)
                {
                    if (msgindex >= 2)
                    {
                        msgindex--;
                        if (whichvec == 2)
                        {
                            //recived_msg[fav_msg.top().favIndex].isFavorite = 0;
                            fav_msg.push(fav_msg_sub.top());
                            fav_msg_sub.pop();
                        }
                    }
                }
            }
            else
                arrowl.setScale(1, 1);

            // when the star is pressed
            if (sf::Mouse::getPosition(window1).x >= 908 && sf::Mouse::getPosition(window1).y >= 310
                && sf::Mouse::getPosition(window1).x <= 957 && sf::Mouse::getPosition(window1).y <= 360
                )
            {
                star.setScale(1.05, 1.05);
                stary.setScale(1.05, 1.05);
                if (event.type == Event::MouseButtonPressed && msgindex != 0 && (whichvec==0 || whichvec == 2))
                {
                    if (currmsg.isFavorite == 0)
                    {
                        currmsg.isFavorite = 1;
                        currmsg.favIndex = msgindex;
                        recived_msg[msgindex].isFavorite = 1;
                        writeFile(recived_msg[msgindex].globalIndex, 1);
                        fav_msg.push(currmsg);
                    }
                    else
                    {
                        if (whichvec == 2 && msgindex == 1)
                        {
                            currmsg.isFavorite = 0;
                            recived_msg[currmsg.favIndex].isFavorite = 0;
                            writeFile(recived_msg[currmsg.favIndex].globalIndex, 0);
                            fav_msg.pop();
                        }
                    }
                }
            }
            else
            {
                star.setScale(1, 1);
                stary.setScale(1, 1);
            }
        }

        // draw functions
        window1.clear();
        window1.draw(design);
        window1.draw(messages);
        window1.draw(contacts);
        window1.draw(chat);
        window1.draw(buttonf);
        window1.draw(buttons);
        window1.draw(buttont);
        window1.draw(arrowl);
        window1.draw(arrowr);
        window1.draw(msg);

        if (currmsg.isFavorite == 1 && (whichvec == 0 || whichvec == 2))
        {
            window1.draw(stary);
        }
        else if (whichvec == 0 || whichvec == 2)
        {
            window1.draw(star);
        }

        if (whichvec == 1)
            window1.draw(reciever);
        else
            window1.draw(id);
        window1.display();

    }
}

void MessagesPage::readFile()
{


    Messages tmp_msg;
    ifstream message_file;
    message_file.open("files\\Messages.txt");

    int whichentry = 1, globalIndex = 0, recievedIndex = 0, favi = 0;
    string tmp4;

    while (getline(message_file, tmp4))
    {
        switch (whichentry)
        {
        case 1:
            tmp_msg.id = tmp4;
            whichentry = 2;
            break;
        case 2:
            tmp_msg.sender = tmp4;
            whichentry = 3;
            break;
        case 3:
            tmp_msg.reciever = tmp4;
            if (curruser1.get_username() == tmp_msg.reciever)
                recievedIndex++;
            whichentry = 4;
            break;
        case 4:
            tmp_msg.message = tmp4;
            tmp_msg.displayMessage();
            whichentry = 5;
            break;
        case 5:
            globalIndex++;
            tmp_msg.isFavorite = stoi(tmp4);
            tmp_msg.globalIndex = globalIndex;
            tmp_msg.favIndex = recievedIndex;
            if (tmp_msg.sender == curruser1.get_username())
            {
                sent_msg.push_back(tmp_msg);
            }
            else if (tmp_msg.reciever == curruser1.get_username())
            {
                if (tmp_msg.isFavorite == 1)
                {
                    fav_msg.push(tmp_msg);
                    tmp_msg.favIndex = favi;
                    favi++;
                }
                recived_msg.push_back(tmp_msg);
            }
            whichentry = 1;
            break;
        }
    }
    message_file.close();
}

void MessagesPage::writeFile(int index, int fav)
{

    string tmp;
    fstream f, s;
    f.open("files\\Messages.txt");
    vector<Messages>tmp_msgs;
    Messages tmp_msg;
    while (!f.eof())
    {
        getline(f, tmp);
        tmp_msg.id = tmp;
        getline(f, tmp);
        tmp_msg.sender = tmp;
        getline(f, tmp);
        tmp_msg.reciever = tmp;
        getline(f, tmp);
        tmp_msg.message = tmp;
        getline(f, tmp);
        tmp_msg.isFavorite = stoi(tmp);
        tmp_msgs.push_back(tmp_msg);
    }
    f.close();
    s.open("files\\Messages.txt");
    for (int i = 0; i < tmp_msgs.size(); i++)
    {
        s << tmp_msgs[i].id << endl;
        s << tmp_msgs[i].sender << endl;
        s << tmp_msgs[i].reciever << endl;
        s << tmp_msgs[i].message << endl;
        if (i == index - 1)
        {
            s << fav;
            if (i + 1 != tmp_msgs.size())
                s << endl;
        }
        else
        {
            s << tmp_msgs[i].isFavorite;
            if (i + 1 != tmp_msgs.size())
                s << endl;
        }
    }
    s.close();
}