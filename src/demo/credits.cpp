/*
* Umbra
* Copyright (c) 2009 Dominik Marczuk
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The name of Dominik Marczuk may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "main.hpp"
#include <stdio.h>

TCODRandom * MatrixLead::random;
TCODConsole * MatrixLead::matrix;

MatrixLead::MatrixLead (void) {
    if (!random) random = new TCODRandom();
    y = 0;
    x = random->getInt(0,engine.getRootWidth()-1);
    lastY = TCODSystem::getElapsedMilli();
    yDuration = random->getInt(20,70);
    if (!matrix) matrix = new TCODConsole(engine.getRootWidth(),engine.getRootHeight());
}

void MatrixLead::render (uint32 time) {
    char c = random->getInt('A','Z');
    if (random->getInt(0,1) == 1)
        c += 0x20;
    else if (random->getInt(0,5) == 5)
        c = random->getInt('0','9');
    if (time >= lastY+yDuration) {
        matrix->setFore(x,y,TCODColor::green);
        lastY = time;
        y++;
        if (y >= engine.getRootHeight()) return;
    }
    matrix->setForegroundColor(TCODColor::lightGreen);
    matrix->putChar(x,y,c,TCOD_BKGND_NONE);
}

Credits::Credits () {
    sprintf (credits, "Hello world!\nPress SPACE to end module...");
}

bool Credits::update (void) {
    if (!MatrixLead::random) MatrixLead::random = new TCODRandom();
    if (MatrixLead::random->getInt(0,100) > 75) leads.push(new MatrixLead());
    return isActive();
}

void Credits::render (void) {
    uint32 t = TCODSystem::getElapsedMilli();
    if (leads.size() > 0) {
        for (MatrixLead ** mx = leads.begin(); mx != leads.end(); mx++) {
            (*mx)->render(t);
            if ((*mx)->y >= engine.getRootHeight())  {
                MatrixLead * tmp = (*mx);
                mx = leads.removeFast(mx);
                delete tmp;
            }
        }

        TCODConsole::blit(MatrixLead::matrix,0,0,engine.getRootWidth(),engine.getRootHeight(),TCODConsole::root,0,0,0.95f,0.0f);
        TCODConsole::blit(TCODConsole::root,0,0,engine.getRootWidth(),engine.getRootHeight(),MatrixLead::matrix,0,0,1.0f,0.0f);
    }

    TCODConsole::root->setForegroundColor(TCODColor::white);
    TCODConsole::root->printLeft(0,0,TCOD_BKGND_NONE,"%s",credits);
}

void Credits::keyboard (TCOD_key_t &key) {
    if (key.vk == TCODK_SPACE) setActive ( false );
}
