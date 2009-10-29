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

#include "umbra.hpp"
#include <stdio.h>

//constructor
UmbraEngine::UmbraEngine (void) {
    UmbraConfig::load();
    currentModule = 0;
}

//add a module to the modules list
void UmbraEngine::registerModule (UmbraModule * module) {
    modules.push(module);
}

bool UmbraEngine::initialise (void) {
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
    TCOD_mouse_t mouse;
    if (modules.size() == 0) {
        UmbraError::add("No modules registered!");
        exit(1);
    }

    module = modules.get(0);
    while(!TCODConsole::isWindowClosed()) {
        if (module->isPaused() || module->update()) module->render();
        else {
            int fallback = module->getFallback();
            if (fallback == -1) break;
            else if (fallback >= modules.size()) {
                UmbraError::add("Fallback indicated a nonexistent module index number (%d)!",fallback);
                exit(1);
            }
            else module = modules.get(fallback);
        }
        key = TCODConsole::checkForKeypress(true);
        mouse = TCODMouse::getStatus();
        if (!globalKeybindings(key)) module->keyboard(key);
        module->mouse(mouse);
        TCODConsole::root->flush();
    }

    UmbraConfig::save();
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
