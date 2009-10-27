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
