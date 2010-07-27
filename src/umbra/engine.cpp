/*
* Umbra
* Copyright (c) 2009 Mingos, Jice
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

#include "umbra.hpp"
#include <stdio.h>
#include <stdarg.h>

TCOD_renderer_t UmbraEngine::renderer = TCOD_RENDERER_SDL;
UmbraEngine * UmbraEngine::engineInstance = NULL;

//constructor
UmbraEngine::UmbraEngine (const char *fileName, bool registerDefaultCallbacks, bool registerAdditionalCallbacks): keyboardMode(UMBRA_KEYBOARD_RELEASED) {
    //load configuration variables
    UmbraConfig::load(fileName);

    paused = false;
    setWindowTitle("%s ver. %s (%s)", UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS);
    engineInstance = this;
    //register internal modules
    registerInternalModule(UMBRA_INTERNAL_SPEEDOMETER,new UmbraModSpeed());
    registerInternalModule(UMBRA_INTERNAL_BSOD,new UmbraModBSOD());
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

void UmbraEngine::setWindowTitle (std::string title) {
	windowTitle = title.c_str();
}

//add a module to the modules list
int UmbraEngine::registerModule (UmbraModule * module, int fallback) {
    module->setFallback(fallback);
    modules.push(module);
    return modules.size()-1;
}

//register a font
void UmbraEngine::registerFont (int columns, int rows, const char * filename, int flags) {
    if (!UmbraError::fileExists(filename)) {
        UmbraError::add("Tried to register a font file that does not exist: %s.",filename);
        displayError();
        return;
    }
    UmbraFont * file = new UmbraFont; //don't delete this later
    file->initialise(columns,rows,filename,flags);
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
bool UmbraEngine::registerFonts( void ) {
    // if fonts registered by the user, do nothing
    if ( getNbFonts() > 0 ) return true;
    TmpFontData dat[MAX_FONTS];
    TCODList<TmpFontData *> fontDataList;
    // look for font*png in font directory
    TCODList<const char *> dir=TCODSystem::getDirectoryContent(getFontDir(),"font*.png");
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
                    sprintf(dat[fontNum].name,"%s/%s",getFontDir(),*fontName);
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
            registerFont((*dat)->columns,(*dat)->rows,(*dat)->name,(*dat)->flags);
        }
    }
    else {
        UmbraError::add("No fonts registered. The font directory %s is empty.",getFontDir());
        return false;
    }

    if (getNbFonts() == 0) {
        UmbraError::add("No fonts registered. Autodetection found no fonts matching the naming pattern font<WIDTH>x<HEIGHT>[_<LAYOUT>].png in the specified directory %s.",getFontDir());
        return false;
    }
    else return true;
}

// public function registering the module for activation next frame, by id
void UmbraEngine::activateModule (int moduleId) {
    if ( moduleId < 0 || moduleId >= modules.size() ) {
        UmbraError::add("Tried to activate an invalid module: ID %d.",moduleId);
        displayError();
        return;
    }
    UmbraModule *module = modules.get(moduleId);
    activateModule(module);
}

//public function registering an internal module for activation next frame, by id
void UmbraEngine::activateModule (UmbraInternalModuleID id) {
    if (id < 0 || id >= UMBRA_INTERNAL_MAX) {
        UmbraError::add("Tried to activate an invalid internal module: ID %d.",(int)id);
        displayError();
        return;
    }
    activateModule(internalModules[id]);
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
        UmbraError::add("Tried to deactivate an invalid module: ID %d.",moduleId);
        displayError();
        return;
    }
    UmbraModule *module = modules.get(moduleId);
    deactivateModule(module);
}

void UmbraEngine::deactivateModule (UmbraInternalModuleID id) {
    if (id < 0 || id >= UMBRA_INTERNAL_MAX) {
        UmbraError::add("Tried to deactivate an invalid internal module: ID %d.",(int)id);
        displayError();
        return;
    }
    else deactivateModule(internalModules[id]);
}

// register the module for deactivation by reference
void UmbraEngine::deactivateModule(UmbraModule *module) {
    if (module != NULL && module->isActive()) {
        toDeactivate.push(module);
        module->setActive(false);
    }
}

void UmbraEngine::deactivateAll () {
    for (UmbraModule ** mod = activeModules.begin(); mod != activeModules.end(); mod++) {
        deactivateModule((*mod));
    }
}

bool UmbraEngine::initialise (TCOD_renderer_t renderer) {
    // autodetect fonts if needed
    bool retVal = registerFonts();
    //activate the base font
    if (retVal) {
		UmbraEngine::renderer=renderer;
        UmbraConfig::activateFont();
        //initialise console
        TCODConsole::setCustomFont(UmbraConfig::font->filename(),UmbraConfig::font->flags(),UmbraConfig::font->columns(),UmbraConfig::font->rows());
        TCODConsole::initRoot(getRootWidth(),getRootHeight(),windowTitle.c_str(), UmbraConfig::fullScreen, renderer);
        TCODSystem::setFps(25);
        TCODMouse::showCursor(true);
    }
    else {
        UmbraError::add("Could not initialise the root console.");
    }
    return retVal;
}

int UmbraEngine::run () {
    TCOD_key_t key;
    TCOD_mouse_t mouse;

    if (modules.size() == 0) {
        UmbraError::add("No modules registered!");
        displayError();
        exit(1);
    }

    while(!TCODConsole::isWindowClosed()) {
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
        long startTime=TCODSystem::getElapsedMilli();
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
	    TCODConsole::root->setBackgroundColor(TCODColor::black);
        TCODConsole::root->clear();
        long updateTime=TCODSystem::getElapsedMilli() - startTime;
        // render active modules by inverted priority order
	    for (UmbraModule ** mod = activeModules.end(); mod != activeModules.begin(); ) {
			mod --;
	        (*mod)->render();
	    }
        long renderTime=TCODSystem::getElapsedMilli() - startTime - updateTime;
        if ( internalModules[UMBRA_INTERNAL_SPEEDOMETER]->isActive() ) {
            ((UmbraModSpeed *)internalModules[UMBRA_INTERNAL_SPEEDOMETER])->setTimes(updateTime,renderTime);
        }
        //flush the screen
        TCODConsole::root->flush();
    }

    UmbraConfig::save();
    return 0;
}

void UmbraEngine::keyboard (TCOD_key_t &key) {
    if (key.vk == TCODK_NONE || key.pressed) return;

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

void UmbraEngine::reinitialise (TCOD_renderer_t renderer) {
    delete TCODConsole::root;
    TCODConsole::root = NULL;
    TCODConsole::setCustomFont(UmbraConfig::font->filename(),UmbraConfig::font->flags(),UmbraConfig::font->columns(),UmbraConfig::font->rows());
	UmbraEngine::renderer=renderer;
    TCODConsole::initRoot(getRootWidth(),getRootHeight(),windowTitle.c_str(), UmbraConfig::fullScreen, this->renderer);
}

void UmbraEngine::registerInternalModule (UmbraInternalModuleID id, UmbraModule * module) {
    internalModules[id] = module;
}

void UmbraEngine::displayError () {
    if (UmbraConfig::debug && TCODConsole::root != NULL) {
        if (internalModules[UMBRA_INTERNAL_BSOD]->isActive())
            toDeactivate.push(internalModules[UMBRA_INTERNAL_BSOD]);
        toActivate.push(internalModules[UMBRA_INTERNAL_BSOD]);
    }
}
