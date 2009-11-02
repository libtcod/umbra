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

enum { MOD_CREDITS, MOD_DEMO, MOD_SPEED };

int main()
{
    //create the engine
    UmbraEngine engine;
    //set window title
    engine.setWindowTitle("Umbra demo");
    //register fonts
    engine.registerFont(32,8,"data/img/font8x8.png",TCOD_FONT_LAYOUT_TCOD|TCOD_FONT_TYPE_GRAYSCALE);
    engine.registerFont(32,8,"data/img/font10x10.png",TCOD_FONT_LAYOUT_TCOD|TCOD_FONT_TYPE_GRAYSCALE);
    engine.registerFont(32,8,"data/img/font12x12.png",TCOD_FONT_LAYOUT_TCOD|TCOD_FONT_TYPE_GRAYSCALE);
    //declare modules
    engine.registerModule(new Credits(),MOD_DEMO);
    engine.registerModule(new Demo());
    //activate modules
    engine.activateModule(MOD_CREDITS);
    //set a custom keybinding
    engine.setKeybinding(UMBRA_KEYBINDING_QUIT,TCODK_CHAR,'q',false,true,false);
    //initialise and run the engine
    if (engine.initialise()) return engine.run();
    else return 1;
}
