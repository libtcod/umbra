/*
* Umbra
* Copyright (c) 2009, 2010 Mingos, Jice
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The names of Mingos or Jice may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY MINGOS & JICE ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL MINGOS OR JICE BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "matrix.hpp"

#include <stdio.h>

#include <SDL_timer.h>

#include "globals.hpp"

TCODRandom * MatrixLead::random;
TCODConsole * MatrixLead::matrix;

MatrixLead::MatrixLead () {
    if (!random) random = new TCODRandom();
    y = 0;
    x = random->get(0,engine.getRootWidth()-1);
    lastY = SDL_GetTicks();
    yDuration = random->get(50,250);
    if (!matrix) matrix = new TCODConsole(engine.getRootWidth(),engine.getRootHeight());
}

void MatrixLead::render (uint32_t time) {
    char c = random->get('A','Z');
    if (random->get(0,1) == 1)
        c += 0x20;
    else if (random->get(0,5) == 5)
        c = random->get('0','9');
    if (time >= lastY+yDuration) {
        matrix->setCharForeground(x,y,TCODColor::green);
        lastY = time;
        y++;
        if (y >= engine.getRootHeight()) return;
    }
    matrix->setDefaultForeground(TCODColor::lightGreen);
    matrix->putChar(x,y,c,TCOD_BKGND_NONE);
}

bool Matrix::update () {
    if (!MatrixLead::random) MatrixLead::random = new TCODRandom();
    if (MatrixLead::random->get(0,3) == 0) leads.push(new MatrixLead());
    return getActive();
}

void Matrix::render () {
    uint32_t t = SDL_GetTicks();
    if (leads.size() > 0) {
        for (MatrixLead ** mx = leads.begin(); mx != leads.end(); mx++) {
            (*mx)->render(t);
            if ((*mx)->y >= engine.getRootHeight())  {
                MatrixLead * tmp = (*mx);
                mx = leads.removeFast(mx);
                delete tmp;
            }
        }
        TCODConsole::blit(MatrixLead::matrix,0,0,engine.getRootWidth(),engine.getRootHeight(),TCODConsole::root,0,0,0.98f,0.0f);
        TCODConsole::blit(TCODConsole::root,0,0,engine.getRootWidth(),engine.getRootHeight(),MatrixLead::matrix,0,0,1.0f,0.0f);
    }
}

void Matrix::onActivate() {
	getEngine()->printCredits(51,1);
}
