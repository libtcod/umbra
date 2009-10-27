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

//constructor
UmbraEngine::UmbraEngine (void) {
    currentModule = 0;
}

//add a module to the modules list
void UmbraEngine::registerModule (UmbraModule * module) {
    //static int count = 0;
    //modules.insert(std::pair <int, UmbraModule*> (count++, module));
    modules.push(module);
}

bool UmbraEngine::initialise (void) {
    //load configuration variables
    UmbraConfig::load();
    //check files existence
    if (!UmbraError::fileExists(UmbraConfig::fontFile->c_str())) {
        UmbraError::add("Terminal font image file %s is bad or missing.",UmbraConfig::fontFile->c_str());
        return false;
    }
    //initialise console
    TCODConsole::setCustomFont(UmbraConfig::fontFile->c_str(),TCOD_FONT_LAYOUT_TCOD|TCOD_FONT_TYPE_GRAYSCALE,32,16);
    TCODConsole::initRoot(UmbraConfig::xSize,UmbraConfig::ySize,UMBRA_TITLE" "UMBRA_VERSION" ("UMBRA_STATUS")", UmbraConfig::fullScreen);
    TCODSystem::setFps(25);
    TCODMouse::showCursor(true);
    return true;
}

int UmbraEngine::run (void) {
    TCOD_key_t key;
    if (modules.size() == 0) {
        UmbraError::add("No modules registered!");
        exit(1);
    }
    module = modules.get(0);
    while(!TCODConsole::isWindowClosed()) {
        //if (modules[currentModule]->update()) modules[currentModule]->render();
        if (module->update()) module->render();
        key = TCODConsole::checkForKeypress(true);
        globalKeybindings(key);
        TCODConsole::root->flush();
    }
    return 0;
}

bool UmbraEngine::globalKeybindings (TCOD_key_t key) {
    bool returnValue = true;

    switch (key.vk) {
        case TCODK_ENTER:
            if (key.lalt || key.ralt) TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
            break;
        case TCODK_PRINTSCREEN:
            TCODSystem::saveScreenshot(NULL);
            break;
        case TCODK_F4:
            if (key.ralt || key.lalt) exit(0);
            break;
        default:
            returnValue = false;
            break;
    }

    return returnValue;
}