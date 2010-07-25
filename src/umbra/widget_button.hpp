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

#include <iostream>

class UmbraWidget;
class UmbraRect;

class UmbraButton {
    public:
        UmbraButton ();
        virtual ~UmbraButton() {}
        UmbraButton (UmbraWidget * parent, int x, int y, int w, int h, const char * tag = "");
        void set (UmbraWidget * parent, int x, int y, int w, int h, const char * tag = "");
        UmbraRect area; //the rectangle where the object is contained
        UmbraWidget * parent; //reference to the widget that contains the object
        bool visible; //visibility (can be toggled)
        std::string tag;
        virtual void render (TCODConsole * con);
        void mouse (TCOD_mouse_t &ms); //checks the status
        virtual void onMouseDown () {} //custom code executed after a button press
        virtual void onMouseOver () {} //custom code executed when the mouse is hovering
};
