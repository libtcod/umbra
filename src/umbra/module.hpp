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

//all screens or views, such as credits, main menu, map view, etc. have to inherit this
class UmbraModule {
    public:
        UmbraModule (void); //constructor
        virtual ~UmbraModule (void) {} //destructor

        virtual void initialize(); // allocate resources. called only once
        virtual void render (void) { } //render the module on the root console
        virtual bool update (void) { return true; } //update the module's logic
        virtual void keyboard (TCOD_key_t &key) { return; } //module-specific keyboard
        virtual void mouse (TCOD_mouse_t ms) { return; } //module-specific mouse
        //setters
        void setFallback (int fback); //set default fallback module's index
        void setFade (int in, int out); //set fade lengths in milliseconds
        //getters
        int getFallback (void);
        int getFadeIn (void);
        int getFadeOut (void);
        inline bool isPaused (void) { return paused; }
        virtual void setActive (bool active);
        inline bool isActive (void) { return active; }
        virtual void setPause (bool paused);
        void deinitialize (void);


    private:
        bool initialized;
        bool active;
        bool paused;
        int fallback; //fallback module's index
        int fadeIn;
        int fadeOut;
};
