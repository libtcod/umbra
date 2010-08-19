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

#ifndef PANEL_HPP
#define PANEL_HPP

//class ButtonMatrix: public UmbraButton { public: ButtonMatrix (); void onMouseOver (); void onMouseDown (); std::string text; };
//class ButtonNoise: public UmbraButton { public: ButtonNoise (); void onMouseOver (); void onMouseDown (); std::string text; };
//class ButtonError: public UmbraButton { public: ButtonError (); void onMouseOver (); void onMouseDown (); std::string text; };
class ButtonQuit: public UmbraButton { public: ButtonQuit (); void onMouseOver (); void onMouseDown (); std::string text; };

class Panel: public UmbraWidget {
    public:
        Panel ();
        //ButtonMatrix bMatrix;
        //ButtonNoise bNoise;
        //ButtonError bError;
        ButtonQuit bQuit;
        bool update ();
        void mouse (TCOD_mouse_t &ms);
        void render ();
        TCODConsole * panel;
    private:
        int posx, posy, width, height;
        uint32 delay;
        uint32 lastHover; //the time the mouse last hovered over the panel
};

#endif
