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

enum UmbraModuleStatus { UMBRA_UNINITIALIZED, UMBRA_INACTIVE, UMBRA_FADING_IN, UMBRA_ACTIVE, UMBRA_PAUSED, UMBRA_FADING_OUT };

//all screens or views, such as credits, main menu, map view, etc. have to inherit this
class UmbraModule {
    public:
        UmbraModule (void); //constructor
        virtual ~UmbraModule (void) {} //destructor

        virtual void initialise (void); // allocate resources. called only once

        virtual void render (void) { } //render the module on the root console
        virtual bool update (void) { return true; } //update the module's logic
        virtual void keyboard (TCOD_key_t &key) { } //module-specific keyboard
        virtual void mouse (TCOD_mouse_t &ms) { } //module-specific mouse

        //setters
        inline void setFallback (int fback) { fallback = fback; } //set default fallback module's index
        void setFadeIn (int lengthInMilli, TCODColor col = TCODColor::black); //set fade lengths in milliseconds
        void setFadeOut (int lengthInMilli, TCODColor col = TCODColor::black); //set fade lengths in milliseconds
        void setActive (bool active);
        void setPause (bool paused);

        //getters
        inline int getFallback (void) { return fallback; }
        inline int getFadeInLength (void) { return fadeInLength; }
        inline int getFadeOutLength (void) { return fadeOutLength; }
        inline TCODColor getFadeInColor (void) { return fadeInColor; }
        inline TCODColor getFadeOutColor (void) { return fadeOutColor; }
        inline bool isPaused (void) { return status == UMBRA_PAUSED; }
        inline bool isActive (void) { return status > UMBRA_INACTIVE; }
        inline UmbraEngine * getEngine (void) { return UmbraEngine::getInstance(); }
		inline int getPriority() { return priority; }
		inline UmbraModuleStatus getStatus (void) { return status; }

    protected:
        // for activation/deactivation custom code
        virtual void activate() {}
        virtual void deactivate() {}
        // for pause/resume custom code
        virtual void pause() {}
        virtual void resume() {}
		int priority; // update order (inverse of render order)
    private:
        UmbraModuleStatus status;
        int fallback; //fallback module's index
        int fadeInLength;
        TCODColor fadeInColor;
        int fadeOutLength;
        TCODColor fadeOutColor;
};
