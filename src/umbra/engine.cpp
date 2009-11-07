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

UmbraEngine * UmbraEngine::engineInstance = NULL;

//constructor
UmbraEngine::UmbraEngine (const char *fileName, bool registerDefaultCallbacks, bool registerAdditionalCallbacks) : keyboardMode( UMBRA_KEYBOARD_RELEASED ) {
    UmbraConfig::load(fileName);
    paused = false;
    setWindowTitle("%s ver. %s (%s)", UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS);
    engineInstance = this;
    //register internal modules
    registerInternalModule(UMBRA_INTERNAL_SPEEDOMETER,new UmbraModSpeed());
    registerInternalModule(UMBRA_INTERNAL_MESSAGE,new UmbraModMessage());
    //register default callbacks
    if (registerDefaultCallbacks) {
        registerCallback(new UmbraCallbackQuit());
        registerCallback(new UmbraCallbackFullscreen());
        registerCallback(new UmbraCallbackScreenshot());
        registerCallback(new UmbraCallbackFontUp());
        registerCallback(new UmbraCallbackFontDown());
        registerCallback(new UmbraCallbackPause());
    }
    if (registerAdditionalCallbacks) {
        registerCallback(new UmbraCallbackSpeedometer());
    }
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

// temporary internal font storage structure
struct TmpFontData {
    int rows;
    int columns;
    char name[512];
    int flags;
    int size;
};
#define MAX_FONTS 16
void UmbraEngine::registerFonts( void ) {
    // if fonts registered by the user, do nothing
    if ( UmbraConfig::getNbFonts() > 0 ) return;
    TmpFontData dat[MAX_FONTS];
    TCODList<TmpFontData *> fontDataList;
    // look for font*png in font directory
    TCODList<const char *> dir=TCODSystem::getDirectoryContent(UmbraConfig::getFontDir(),"font*.png");
    if ( dir.size() > 0 ) {
        int fontNum=0;
        for (const char **fontName = dir.begin(); fontName != dir.end() && fontNum < MAX_FONTS; fontName++) {
            int charWidth;
            int charHeight;
            char layout[32]="";
            if ( sscanf(*fontName,"font%dx%d%s",&charWidth,&charHeight,layout) >= 2 ) {
                if ( charWidth > 0 && charHeight > 0 ) {
                    int fontFlag = TCOD_FONT_TYPE_GREYSCALE;
                    if ( layout[0] == '_' ) {
                        // parse font layout
                        if ( strncasecmp(layout,"_TCOD.",6) == 0 ) fontFlag|=TCOD_FONT_LAYOUT_TCOD;
                        else if ( strncasecmp(layout,"_INCOL.",7) == 0 ) fontFlag|=TCOD_FONT_LAYOUT_ASCII_INCOL;
                        else if ( strncasecmp(layout,"_INROW.",7) == 0 ) fontFlag|=TCOD_FONT_LAYOUT_ASCII_INROW;
                    } else {
                        // default is TCOD |GREYSCALE
                        fontFlag|=TCOD_FONT_LAYOUT_TCOD;
                    }
                    // compute font grid size from image size & char size
                    int w,h;
                    sprintf(dat[fontNum].name,"%s/%s",UmbraConfig::getFontDir(),*fontName);
                    TCODImage tmp(dat[fontNum].name);
                    tmp.getSize(&w,&h);
                    dat[fontNum].size = charWidth*charHeight;
                    dat[fontNum].rows=h/charHeight;
                    dat[fontNum].columns=w/charWidth;
                    dat[fontNum].flags=fontFlag;
                    // sort this font by size
                    int idx=0;
                    while ( idx < fontDataList.size() && fontDataList.get(idx)->size < dat[fontNum].size ) idx ++;
                    fontDataList.insertBefore(&dat[fontNum],idx);
                    fontNum++;
                }
            }
        }
        for (TmpFontData **dat=fontDataList.begin(); dat != fontDataList.end(); dat ++) {
            // register the fonts from smallest to biggest
            registerFont((*dat)->rows,(*dat)->columns,(*dat)->name,(*dat)->flags);
        }
    }
}

// public function registering the module for activation next frame, by id
void UmbraEngine::activateModule (int moduleId) {
    if ( moduleId < 0 || moduleId >= modules.size() ) {
        UmbraError::add("Tried to activate an invalid module: ID %d.",moduleId);
        toActivate.push(internalModules[UMBRA_INTERNAL_MESSAGE]);
        return;
    }
    UmbraModule *module = modules.get(moduleId);
    activateModule(module);
}

// public function registering the module for activation next frame, by reference
void UmbraEngine::activateModule(UmbraModule *module) {
    if (module != NULL && ! module->isActive()) {
        toActivate.push(module);
    }
}

// the internal function actually putting a module in active list
void UmbraEngine::doActivateModule( UmbraModule *mod ) {
    if (! mod->isActive() ) {
        mod->setActive(true);
		// insert the module at the right pos, sorted by priority
		int idx = 0;
		while ( idx < activeModules.size() && activeModules.get(idx)->getPriority() < mod->getPriority() ) idx ++;
        activeModules.insertBefore(mod,idx);
    }
}

// register the module for deactivation by id
void UmbraEngine::deactivateModule (int moduleId) {
    if ( moduleId < 0 || moduleId >= modules.size() ) {
        UmbraError::add("Try to deactivate invalid module id %d.",moduleId);
        return;
    }
    UmbraModule *module = modules.get(moduleId);
    deactivateModule(module);
}

// register the module for deactivation by reference
void UmbraEngine::deactivateModule(UmbraModule *module) {
    if (module != NULL && module->isActive()) {
        toDeactivate.push(module);
        module->setActive(false);
    }
}

void UmbraEngine::deactivateAll (void) {
    for (UmbraModule ** mod = activeModules.begin(); mod != activeModules.end(); mod++) {
        deactivateModule((*mod));
    }
}

bool UmbraEngine::initialise (void) {
    // autodetect fonts if needed
    registerFonts();
    //activate the base font
    UmbraConfig::activateFont();
    //initialise console
    TCODConsole::setCustomFont(UmbraConfig::font->filename(),UmbraConfig::font->flags(),UmbraConfig::font->columns(),UmbraConfig::font->rows());
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
        TCODConsole::root->setBackgroundColor(TCODColor::black);
        TCODConsole::root->clear();
        //execute only when paused
        if (paused) {
            key = TCODConsole::checkForKeypress(TCOD_KEY_RELEASED);
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
			doActivateModule(*mod);
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
		// update all active modules by priority order
	    for (UmbraModule ** mod = activeModules.begin(); mod != activeModules.end(); mod++) {
	        if (!(*mod)->isPaused()) {
	            // handle input
	            (*mod)->keyboard(key);
	            (*mod)->mouse(mouse);
	            if (!(*mod)->update() || !(*mod)->isActive()) {
	                UmbraModule *module=*mod;
	                int fallback=module->getFallback();
	                // deactivate module
	                module->setActive(false);
	                mod = activeModules.remove(mod);
	                if (fallback != -1) {
	                    // register fallback for activation
	                    UmbraModule *fallbackModule = modules.get(fallback);
	                    if (fallbackModule != NULL && !fallbackModule->isActive()) toActivate.push(fallbackModule);
	                }
	            }
	        }
	    }
        // render active modules by inverted priority order
	    for (UmbraModule ** mod = activeModules.end(); mod != activeModules.begin(); ) {
			mod --;
	        (*mod)->render();
	    }
        //flush the screen
        TCODConsole::root->flush();
    }

    UmbraConfig::save();
    return 0;
}

void UmbraEngine::keyboard (TCOD_key_t &key) {
    if (key.vk == TCODK_NONE) return;

    UmbraKey k(key.vk, key.c, key.ralt|key.lalt, key.rctrl|key.lctrl, key.shift);

    bool val = false;

    for (UmbraCallback ** cbk = callbacks.begin(); cbk != callbacks.end(); cbk++) {
        if ((*cbk)->evaluate(k)) {
            val = true;
            break;
        }
    }

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

void UmbraEngine::registerInternalModule (UmbraInternalModuleID id, UmbraModule * module) {
    internalModules[id] = module;
}
