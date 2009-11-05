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

class UmbraCallback {
    public:
        UmbraCallback (void) {}
        virtual ~UmbraCallback (void) {}
        void setKeybinding (TCOD_keycode_t vk, char c, bool alt, bool ctrl, bool shift) { key.vk=vk; key.c=c; key.alt=alt; key.ctrl=ctrl; key.shift=shift; }
        virtual inline bool evaluate (UmbraKey k) { if (k == key) {action(); return true;} else return false; }
        UmbraKey key;
    protected:
        virtual void action (void) = 0;
        inline UmbraEngine * getEngine (void) { return UmbraEngine::getInstance(); }
};

//Internal callbacks:

//quit game
class UmbraCallbackQuit : public UmbraCallback {
    public:
        UmbraCallbackQuit (void);
        ~UmbraCallbackQuit (void) {}
        inline bool evaluate (UmbraKey k) {if (k == key || k == key2) {action(); return true;} else return false; }
        UmbraKey key2;
        void action (void);
};

//switch fullscreen
class UmbraCallbackFullscreen : public UmbraCallback {
    public:
        UmbraCallbackFullscreen (void);
        ~UmbraCallbackFullscreen (void) {}
        void action (void);
};

//save screenshot
class UmbraCallbackScreenshot : public UmbraCallback {
    public:
        UmbraCallbackScreenshot (void);
        ~UmbraCallbackScreenshot (void) {}
        void action (void);
};

//font up
class UmbraCallbackFontUp : public UmbraCallback {
    public:
        UmbraCallbackFontUp (void);
        ~UmbraCallbackFontUp (void) {}
        void action (void);
};

//switch font down
class UmbraCallbackFontDown : public UmbraCallback {
    public:
        UmbraCallbackFontDown (void);
        ~UmbraCallbackFontDown (void) {}
        void action (void);
};

//pause the program
class UmbraCallbackPause : public UmbraCallback {
    public:
        UmbraCallbackPause (void);
        ~UmbraCallbackPause (void) {}
        void action (void);
};

//pause the program
class UmbraCallbackSpeedometer : public UmbraCallback {
    public:
        UmbraCallbackSpeedometer (void);
        ~UmbraCallbackSpeedometer (void) {}
        void action (void);
};
