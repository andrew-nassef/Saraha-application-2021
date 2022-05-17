#include "Messages.h"
#include <iostream>

void  Messages::displayMessage()
{
    for (int i = 51; i < message.size(); i += 51)
    {
        message.insert(i, "-\n");
    }
}
