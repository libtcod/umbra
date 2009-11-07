/*
* Umbra
* Copyright (c) 2009 Dominik Marczuk, Jice
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The names of Dominik Marczuk or Jice may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK & JICE ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK OR JICE BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "main.hpp"
#include <stdio.h>

Demo::Demo (void) {
    sprintf (credits, "Goodbye world!\nPress ESC to quit.");
    random = TCODRandom::getInstance();
    noise = new TCODNoise(3,random);
    img = new TCODImage(UmbraConfig::rootWidth*2,UmbraConfig::rootHeight);
    offset = 0.0f;
}

bool Demo::update (void) {
    int i, j;
    int xres = UmbraConfig::rootWidth*2;
    for (i = 0; i < xres; i++) for (j = 0; j < UmbraConfig::rootHeight; j++) {
        float f[3];
        f[0] = 8.0f * i / xres;
        f[1] = 8.0f * j / UmbraConfig::rootHeight;
        f[2] = offset;
        uint8 val = (uint8)((noise->getFbmSimplex(f,4.0f)+1.0f) * 64.0f);
        img->putPixel(i,j,TCODColor(val,val,val));
    }
    offset += 0.05f;
    return isActive();
}

void Demo::render (void) {
    TCODConsole::root->setForegroundColor(TCODColor::red);
    TCODConsole::root->printLeft(0,0,TCOD_BKGND_NONE,"%s",credits);
    img->blit2x(TCODConsole::root,0,UmbraConfig::rootHeight/4);
}

void Demo::keyboard (TCOD_key_t &key) {
    if (key.vk == TCODK_SPACE) getEngine()->activateModule(2);
    else if (key.vk == TCODK_ESCAPE) getEngine()->deactivateAll();
}

