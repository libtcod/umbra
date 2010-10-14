/*
* Umbra
* Copyright (c) 2009, 2010 Mingos, Jice
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

#include "main.hpp"
#include <stdio.h>

UmbraEngine engine = UmbraEngine("data/cfg/umbra.txt",UMBRA_REGISTER_ALL);

int main()
{
    //create the engine
    //UmbraEngine engine("data/cfg/umbra.txt",true,true);
    //set window title
    engine.setWindowTitle("Umbra demo");
    //register fonts
    /*
    engine.registerFont(32,8,"data/img/font8x8.png",TCOD_FONT_LAYOUT_TCOD|TCOD_FONT_TYPE_GRAYSCALE);
    engine.registerFont(32,8,"data/img/font10x10.png",TCOD_FONT_LAYOUT_TCOD|TCOD_FONT_TYPE_GRAYSCALE);
    engine.registerFont(32,8,"data/img/font12x12.png",TCOD_FONT_LAYOUT_TCOD|TCOD_FONT_TYPE_GRAYSCALE);
    */
    //declare modules
    engine.registerModule(new Matrix(),"matrix");
    engine.registerModule(new Demo(),"demo");
    engine.registerModule(new RabbitWidget(),"rabbit");
    engine.registerModule(new Panel(),"panel");
    engine.registerModule(new Credits(),"credits");
    //initialise and run the engine
    if (engine.loadModuleConfiguration("data/cfg/module.txt") && engine.initialise()) return engine.run();
    else return 1;
}
