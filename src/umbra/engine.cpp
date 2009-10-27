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
