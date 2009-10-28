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

#include "main.hpp"
#include <stdio.h>

TCODParser UmbraConfig::parser;
int UmbraConfig::xSize;
int UmbraConfig::ySize;
int UmbraConfig::fontSize;
bool UmbraConfig::fullScreen;
std::string * UmbraConfig::fontFile = new std::string;

void UmbraConfig::load (void) {
    static bool loaded = false;
    if (loaded) return;

    //register configuration variables
    TCODParserStruct * config = parser.newStructure("config");
        config->addProperty("xSize",TCOD_TYPE_INT,true);
        config->addProperty("ySize",TCOD_TYPE_INT,true);
        config->addProperty("fontSize",TCOD_TYPE_INT,true);
        config->addProperty("fullScreen",TCOD_TYPE_BOOL,true);

    //check if the config file exists
    if (!UmbraError::fileExists("data/cfg/config.txt")) {
        UmbraError::add("Configuration file data/cfg/config.txt is bad or missing.");
        exit(1); //replace by loading defaults or automatic default config file generator
    }

    //run the parser
    parser.run("data/cfg/config.txt",NULL);

    //assign parsed values to class variables
    xSize = parser.getIntProperty("config.xSize");
    ySize = parser.getIntProperty("config.ySize");
    fontSize = parser.getIntProperty("config.fontSize");
    fullScreen = parser.getBoolProperty("config.fullScreen");

    //create terminal font file name
    char fName[128];
    sprintf(fName,"data/img/font%dx%d.png",fontSize,fontSize);
    fontFile->assign(fName);

    loaded = true;
}

void UmbraConfig::save (void) {
    FILE * out;
    out = fopen("data/cfg/config.txt","w");

    fprintf(out,"/*\n"
                " * UMBRA CONFIGURATION FILE\n"
                " */\n"
                "\n"
                "config {\n"
                "  xSize = %d\n"
                "  ySize = %d\n"
                "  fontSize = %d\n"
                "  fullScreen = %s\n"
                "}\n",
                xSize, ySize, fontSize, (fullScreen?"true":"false"));

    fclose(out);
}
