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
#include <stdarg.h>

//constructor
UmbraEngine::UmbraEngine (void) : keyboardMode( UMBRA_KEYBOARD_RELEASED ) {
    UmbraConfig::load();
    paused = false;
    setWindowTitle("%s ver. %s (%s)", UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS);
    //default keybindings
    setKeybinding(UMBRA_KEYBINDING_QUIT,TCODK_F4,0,true,false,false);
    setKeybinding(UMBRA_KEYBINDING_FULLSCREEN,TCODK_ENTER,'\r',true,false,false);
    setKeybinding(UMBRA_KEYBINDING_FONT_UP,TCODK_PAGEUP,0,false,false,false);
    setKeybinding(UMBRA_KEYBINDING_FONT_DOWN,TCODK_PAGEDOWN,0,false,false,false);
    setKeybinding(UMBRA_KEYBINDING_SCREENSHOT,TCODK_PRINTSCREEN,0,false,false,false);
    setKeybinding(UMBRA_KEYBINDING_PAUSE,TCODK_PAUSE,0,false,false,false);
}

void UmbraEngine::setWindowTitle (const char * title, ...) {
    char f[512];
    va_list ap;
    va_start(ap,title);
    vsprintf(f,title,ap);
    va_end(ap);
    windowTitle = (const char *)f;
}

//add a module to the modules list
int UmbraEngine::registerModule (UmbraModule * module, int fallback) {
    module->setFallback(fallback);
    modules.push(module);
    return modules.size()-1;
}

//register a font
void UmbraEngine::registerFont (int rows, int columns, const char * filename, int flags) {
    if (!UmbraError::fileExists(filename)) {
        UmbraError::add("Tried to register a font file that does not exist: %s.",filename);
        return;
    }
    UmbraFont * file = new UmbraFont; //don't delete this later
    file->initialise(rows,columns,filename,flags);
    UmbraConfig::registerFont(file);
}

void UmbraEngine::setKeybinding (UmbraKeybinding kb, TCOD_keycode_t vk, char c, bool alt, bool ctrl, bool shift) {
    keybindings[kb].vk = vk;
    keybindings[kb].c = c;
    keybindings[kb].alt = alt;
    keybindings[kb].ctrl = ctrl;
    keybindings[kb].shift = shift;
}

void UmbraEngine::activateModule( int moduleId ) {
    if ( moduleId < 0 || moduleId >= modules.size() ) {
        UmbraError::add("Try to activate invalid module id %d.",moduleId);
        return;
    }
    UmbraModule *module = modules.get(moduleId);
    if (module != NULL && ! module->isActive()) {
        toActivate.push(module);
    }
}

void UmbraEngine::deactivateModule( int moduleId ) {
    if ( moduleId < 0 || moduleId >= modules.size() ) {
        UmbraError::add("Try to deactivate invalid module id %d.",moduleId);
        return;
    }
    UmbraModule *module = modules.get(moduleId);
    if (module != NULL && module->isActive()) {
        toDeactivate.push(module);
        module->setActive(false);
    }
}

bool UmbraEngine::initialise (void) {
    //activate the base font
    UmbraConfig::activateFont();
    //initialise console
    TCODConsole::setCustomFont(UmbraConfig::font->filename(),UmbraConfig::font->flags(),UmbraConfig::font->rows(),UmbraConfig::font->columns());
    TCODConsole::initRoot(UmbraConfig::rootWidth,UmbraConfig::rootHeight,windowTitle.c_str(), UmbraConfig::fullScreen);
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

    while(!TCODConsole::isWindowClosed()) {
        //execute only when paused
        if (paused) {
            key = TCODConsole::checkForKeypress(true);
            keyboard(key);
            TCODConsole::root->flush();
            continue; //don't update or render anything anew
        }

        // deactivate modules
        for (UmbraModule ** mod = toDeactivate.begin(); mod != toDeactivate.end(); mod++) {
            (*mod)->setActive(false);
            activeModules.remove(*mod);
        }
        toDeactivate.clear();
        // activate new modules
        for (UmbraModule ** mod = toActivate.begin(); mod != toActivate.end(); mod++) {
            if (! (*mod)->isActive() ) {
                (*mod)->setActive(true);
                activeModules.push(*mod);
            }
        }
        toActivate.clear();
        if (activeModules.size() == 0) break; // exit game
        // update all active modules
        switch ( keyboardMode ) {
            case UMBRA_KEYBOARD_WAIT :
                key = TCODConsole::waitForKeypress( true ) ;
                break;
            case UMBRA_KEYBOARD_WAIT_NOFLUSH :
                key = TCODConsole::waitForKeypress( false ) ;
                break;
            case UMBRA_KEYBOARD_PRESSED :
                key = TCODConsole::checkForKeypress( TCOD_KEY_PRESSED ) ;
                break;
            case UMBRA_KEYBOARD_PRESSED_RELEASED :
                key = TCODConsole::checkForKeypress( TCOD_KEY_PRESSED | TCOD_KEY_RELEASED ) ;
                break;
            case UMBRA_KEYBOARD_RELEASED :
            default :
                key = TCODConsole::checkForKeypress( TCOD_KEY_RELEASED ) ;
                break;
        }
        mouse = TCODMouse::getStatus();
        keyboard(key);
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
                    if (fallback != -1) {
                        // register fallback for activation
                        UmbraModule *fallbackModule = modules.get(fallback);
                        if (fallbackModule != NULL && !fallbackModule->isActive()) toActivate.push(fallbackModule);
                    }
                }
            }
        }
        // render active modules
        for (UmbraModule ** mod = activeModules.begin(); mod != activeModules.end(); mod++) {
            (*mod)->render();
        }
        TCODConsole::root->flush();
    }

    UmbraConfig::save();
    return 0;
}

void UmbraEngine::keyboard (TCOD_key_t &key) {
    if (key.vk == TCODK_NONE) return;

    UmbraKey k = { key.vk, key.c, key.ralt|key.lalt, key.rctrl|key.lctrl, key.shift };

    bool val = true;

    if (keybindings[UMBRA_KEYBINDING_QUIT] == k) { UmbraConfig::save(); exit(0); }
    else if (keybindings[UMBRA_KEYBINDING_PAUSE] == k) { paused = !paused; }
    else if (keybindings[UMBRA_KEYBINDING_FONT_UP] == k) { if (UmbraConfig::activateFont(1)) reinitialise(); }
    else if (keybindings[UMBRA_KEYBINDING_FONT_DOWN] == k) { if (UmbraConfig::activateFont(-1)) reinitialise(); }
    else if (keybindings[UMBRA_KEYBINDING_SCREENSHOT] == k) { TCODSystem::saveScreenshot(NULL); }
    else if (keybindings[UMBRA_KEYBINDING_FULLSCREEN] == k) { TCODConsole::setFullscreen(!TCODConsole::isFullscreen()); }
    else val = false;

    if (val) {
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
