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
int UmbraConfig::fontID;
bool UmbraConfig::fullScreen;
TCODList <UmbraFont *> UmbraConfig::fonts;
UmbraFont * UmbraConfig::font = NULL;
char * UmbraConfig::fileName = NULL;

void UmbraConfig::load (const char *fileName) {
    static bool loaded = false;
    if (loaded && strcmp(UmbraConfig::fileName, fileName) == 0 ) return;
    TCODParser parser;

    UmbraConfig::fileName = strdup(fileName);
    //register configuration variables
    TCODParserStruct * config = parser.newStructure("config");
        config->addProperty("rootWidth",TCOD_TYPE_INT,true);
        config->addProperty("rootHeight",TCOD_TYPE_INT,true);
        config->addProperty("fontID",TCOD_TYPE_INT,true);
        config->addProperty("fullScreen",TCOD_TYPE_BOOL,true);

    //check if the config file exists
    if (!UmbraError::fileExists(fileName)) {
        UmbraError::add("Configuration file %s is bad or missing.", fileName );
        exit(1); //replace by loading defaults or automatic default config file generator
    }

    //run the parser
    parser.run(fileName,NULL);

    //assign parsed values to class variables
    rootWidth = parser.getIntProperty("config.rootWidth");
    rootHeight = parser.getIntProperty("config.rootHeight");
    fontID = parser.getIntProperty("config.fontID");
    fullScreen = parser.getBoolProperty("config.fullScreen");

    loaded = true;
}

void UmbraConfig::save (void) {
    FILE * out;
    out = fopen(fileName,"w");

    fprintf(out,"/*\n"
                " * UMBRA CONFIGURATION FILE\n"
                " */\n"
                "\n"
                "config {\n"
                "  rootWidth = %d\n"
                "  rootHeight = %d\n"
                "  fontID = %d\n"
                "  fullScreen = %s\n"
                "}\n",
                rootWidth, rootHeight, fontID, (fullScreen?"true":"false"));

    fclose(out);
}

void UmbraConfig::registerFont (UmbraFont * _font) {
    fonts.push(_font);
}

bool UmbraConfig::activateFont (int shift) {
    int s = CLAMP(-1,1,shift);
    //check if there are any registered fonts
    if (fonts.size() == 0) {
        UmbraError::add("Tried to activate a font without having registered any.");
        return false;
    }
    //check if the requested ID isn't out of range
    if (fontID+s < 0 || fontID+s >= fonts.size()) return false;
    //check if the font needs changing at all
    if (font != NULL && s == 0) return false;
    //register the font
    font = fonts.get(fontID+s);
    fontID += s;
    return true;
}

