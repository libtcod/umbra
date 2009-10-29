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
int UmbraEngine::registerModule (UmbraModule * module, int fallback) {
    module->setFallback(fallback);
    modules.push(module);
    return modules.size()-1;
}

void UmbraEngine::activateModule( int moduleId ) {
    if ( moduleId < 0 || moduleId >= modules.size() ) {
        UmbraError::add("Try to activate invalid module id %d.",moduleId);
        return;
    }
    UmbraModule *module = modules.get(moduleId);
    if (module != NULL && ! module->isActive()) {
        module->setActive(true);
        activeModules.push(module);
    }
}

void UmbraEngine::deactivateModule( int moduleId ) {
    if ( moduleId < 0 || moduleId >= modules.size() ) {
        UmbraError::add("Try to deactivate invalid module id %d.",moduleId);
        return;
    }
    UmbraModule *module = modules.get(moduleId);
    if (module != NULL && module->isActive()) {
        activeModules.remove(module);
        module->setActive(false);
    }
}

bool UmbraEngine::initialise (void) {
    //check files existence
    if (!UmbraError::fileExists(UmbraConfig::fontFile->c_str())) {
        UmbraError::add("Terminal font image file %s is bad or missing.",UmbraConfig::fontFile->c_str());
        return false;
    }
    //initialise console
    TCODConsole::setCustomFont(UmbraConfig::fontFile->c_str(),TCOD_FONT_LAYOUT_TCOD|TCOD_FONT_TYPE_GRAYSCALE,32,8);
    TCODConsole::initRoot(UmbraConfig::xSize,UmbraConfig::ySize,UMBRA_TITLE" "UMBRA_VERSION" ("UMBRA_STATUS")", UmbraConfig::fullScreen);
    TCODSystem::setFps(25);
    TCODMouse::showCursor(true);
    return true;
}

int UmbraEngine::run (void) {
    TCOD_key_t key;
    TCOD_mouse_t mouse;
    static TCODList<UmbraModule *> toActivate;

    if (modules.size() == 0) {
        UmbraError::add("No modules registered!");
        exit(1);
    }

    module = modules.get(0);
    while(!TCODConsole::isWindowClosed()) {
        // update all active modules
        key = TCODConsole::checkForKeypress(true);
        mouse = TCODMouse::getStatus();
        globalKeybindings(key);
        for (UmbraModule ** mod = activeModules.begin(); mod != activeModules.end(); mod++) {
            if (!(*mod)->isPaused()) {
                // handle input
                (*mod)->keyboard(key);
                (*mod)->mouse(mouse);
                if (!(*mod)->update()) {
                    UmbraModule *module=*mod;
                    int fallback=module->getFallback();
                    // deactivate module
                    mod = activeModules.remove(mod);
                    module->setActive(false);
                    if ( fallback != -1 ) {
                        // register fallback for activation
                        UmbraModule *fallbackModule = modules.get(fallback);
                        if ( fallbackModule != NULL && !fallbackModule->isActive() ) toActivate.push(fallbackModule);
                    }
                }
            }
        }
        // render active modules
        for (UmbraModule ** mod = activeModules.begin(); mod != activeModules.end(); mod++) {
            (*mod)->render();
        }
        // activate new modules
        for (UmbraModule ** mod = toActivate.begin(); mod != toActivate.end(); mod++) {
            (*mod)->setActive(true);
            activeModules.push(*mod);
        }
        toActivate.clear();
        if ( activeModules.size() == 0 ) break; // exit game
        TCODConsole::root->flush();
    }

    UmbraConfig::save();
    return 0;
}

void UmbraEngine::globalKeybindings (TCOD_key_t &key) {
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
        case TCODK_PAGEUP:
            if (UmbraConfig::adjustFontSize(1)) reinitialise();
            break;
        case TCODK_PAGEDOWN:
            if (UmbraConfig::adjustFontSize(-1)) reinitialise();
            break;
        default:
            returnValue = false;
            break;
    }

    if (returnValue) {
        // "erase" key event
        memset(&key,0,sizeof(TCOD_key_t));
    }
}

void UmbraEngine::reinitialise (void) {
    delete TCODConsole::root;
    TCODConsole::root = NULL;
    if (!initialise()) {
        UmbraError::add("Could not reinitialise the root console.");
        exit(1);
    }
}
