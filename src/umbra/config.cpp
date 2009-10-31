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

int UmbraConfig::rootWidth;
int UmbraConfig::rootHeight;
int UmbraConfig::fontSize;
bool UmbraConfig::fullScreen;
std::string * UmbraConfig::fontFile = new std::string;
TCODList <UmbraFont *> UmbraConfig::fonts;

void UmbraConfig::load (void) {
    static bool loaded = false;
    if (loaded) return;
    TCODParser parser;

    //register configuration variables
    TCODParserStruct * config = parser.newStructure("config");
        config->addProperty("rootWidth",TCOD_TYPE_INT,true);
        config->addProperty("rootHeight",TCOD_TYPE_INT,true);
        config->addProperty("fontSize",TCOD_TYPE_INT,true);
        config->addProperty("fullScreen",TCOD_TYPE_BOOL,true);

    //check if the config file exists
    if (!UmbraError::fileExists("data/cfg/umbra.txt")) {
        UmbraError::add("Configuration file data/cfg/umbra.txt is bad or missing.");
        exit(1); //replace by loading defaults or automatic default config file generator
    }

    //run the parser
    parser.run("data/cfg/umbra.txt",NULL);

    //assign parsed values to class variables
    rootWidth = parser.getIntProperty("config.rootWidth");
    rootHeight = parser.getIntProperty("config.rootHeight");
    fontSize = parser.getIntProperty("config.fontSize");
    fullScreen = parser.getBoolProperty("config.fullScreen");

    generateTerminalName();

    loaded = true;
}

void UmbraConfig::save (void) {
    FILE * out;
    out = fopen("data/cfg/umbra.txt","w");

    fprintf(out,"/*\n"
                " * UMBRA CONFIGURATION FILE\n"
                " */\n"
                "\n"
                "config {\n"
                "  rootWidth = %d\n"
                "  rootHeight = %d\n"
                "  fontSize = %d\n"
                "  fullScreen = %s\n"
                "}\n",
                rootWidth, rootHeight, fontSize, (fullScreen?"true":"false"));

    fclose(out);
}

void UmbraConfig::generateTerminalName (void) {
    char fName[128];
    sprintf(fName,"data/img/font%dx%d.png",fontSize,fontSize);
    fontFile->assign(fName);
}

bool UmbraConfig::adjustFontSize (int adjust) {
    int a = (adjust == 0 ? 0 : (adjust < 0 ? (-1) : 1)); //probably for going forth or back through a filenames list or something... TODO...

    //the following primitive code is only a test - change later, when it's clear how we want the font switcher to work!
    static int sizeID;
    if (fontSize == 8) sizeID = 0;
    if (fontSize == 10) sizeID = 1;
    if (fontSize == 12) sizeID = 2;
    static int sizes[3] = { 8, 10, 12 };
    bool change = false;
    if ((a == 1 && sizeID < 2) || (a == -1 && sizeID > 0)) { fontSize = sizes[sizeID+a]; sizeID += a; change = true; }
    if (change) generateTerminalName();
    return change;
}

void UmbraConfig::registerFont (UmbraFont * _font) {
    fonts.push(_font);
}
