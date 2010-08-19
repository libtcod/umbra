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

enum UmbraModuleStatus { UMBRA_UNINITIALISED, UMBRA_INACTIVE, UMBRA_ACTIVE, UMBRA_PAUSED };

//all screens or views, such as credits, main menu, map view, etc. have to inherit this
class UmbraModule {
    public:
        UmbraModule (); //constructor
        virtual ~UmbraModule () {} //destructor

        virtual void initialise (); // allocate resources. called only once

        virtual void render () { } //render the module on the root console
        virtual bool update () { return getActive(); } //update the module's logic
        virtual void keyboard (TCOD_key_t &key) { } //module-specific keyboard
        virtual void mouse (TCOD_mouse_t &ms) { } //module-specific mouse

        //setters
        inline void setFallback (int fback) { fallback = fback; } //set default fallback module's index
        void setActive (bool active);
        void setPause (bool paused);

        //getters
        inline int getFallback () { return fallback; }
        inline bool getPause () { return status == UMBRA_PAUSED; }
        inline bool getActive () { return status > UMBRA_INACTIVE; }
        inline UmbraEngine * getEngine () { return UmbraEngine::getInstance(); }
		inline int getPriority() { return priority; }
		inline UmbraModuleStatus getStatus () { return status; }

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
};
