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
#include "demo.hpp"

#include <stdio.h>

Demo::Demo () {
    random = TCODRandom::getInstance();
    noise = new TCODNoise(2,random);
    offset = 0.0f;
}

void Demo::onInitialise () {
    img = new TCODImage(getEngine()->getRootWidth(),getEngine()->getRootHeight());
}

bool Demo::update () {
    if (getActive()) {
        int i, j;
        for (i = 0; i < getEngine()->getRootWidth(); i++) for (j = 0; j < getEngine()->getRootHeight(); j++) {
            float f[2];
            f[0] = 8.0f * i / getEngine()->getRootWidth();
            f[1] = (8.0f * j / getEngine()->getRootHeight()) + offset;
            int val = (uint8_t)((noise->get(f)+1.0f)*24.0f);
            img->putPixel(i,j,TCODColor(0,val/2,val));
        }
        offset += 0.01f;
        return true;
    }
    else return false;
}

void Demo::render () {
    img->blit(TCODConsole::root,getEngine()->getRootWidth()/2,getEngine()->getRootHeight()/2);
    TCODConsole::root->print(1,3,"Read custom parameters from module.txt:");
    TCODConsole::root->print(1,5,"chainParam1: %s",getStringParam("chainParam1"));
    TCODConsole::root->print(1,6,"chainParam2: %s",getStringParam("chainParam2"));
    TCODConsole::root->print(1,7,"chainParam3: %s",getStringParam("chainParam3"));
    TCODConsole::root->print(1,8,"moduleParam: %s",getStringParam("moduleParam"));
}

void Demo::keyboard (TCOD_key_t &key) {
    if (key.vk == TCODK_SPACE) getEngine()->activateModule(666);
    else if (key.vk == TCODK_ENTER) {
        std::string e = "This is a test error";
        UmbraLog::error(e);
        getEngine()->displayError();
    }
    else if (key.vk == TCODK_ESCAPE) getEngine()->deactivateAll();
}
