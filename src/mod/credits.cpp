#include "main.hpp"
#include <stdio.h>

Credits::Credits (void) {
    sprintf (credits, "Hello world!");
}

bool Credits::render (void) {
    TCODConsole::root->setForegroundColor(TCODColor::white);
    TCODConsole::root->printLeft(0,0,TCOD_BKGND_NONE,"%s",credits);
    return false;
}
