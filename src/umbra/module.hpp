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
        /**
         * Activates or deactivates the module.
         * @param active <i>true</i> if the module is to be activated, <i>false</i> otherwise         
         */ 
        void setActive (bool active);
        /**
         * Pauses or unpauses the module.
         * @param paused <i>true</i> if the module is to be paused, <i>false</i> otherwise         
         */
        void setPause (bool paused);

        //getters
        
        /**
         * Gets the ID number of the fallback module.
         * @return ID number of the fallback module        
         */                 
        inline int getFallback () { return fallback; }
        /**
         * Checks whether the module is paused or not.
         * @return <i>true</i> if the module is paused, <i>false</i> otherwise         
         */                 
        inline bool getPause () { return status == UMBRA_PAUSED; }
        /**
         * Checks whether the module has been activated.
         * @return <i>true</i> if the module has been activated, <i>false</i> otherwise         
         */                 
        inline bool getActive () { return status > UMBRA_INACTIVE; }
        /**
         * Provides a pointer to the engine object.
         * @return a pointer to the engine object         
         */ 
        inline UmbraEngine * getEngine () { return UmbraEngine::getInstance(); }
		    /**
         * Checks the module's priority.
         * @return the module's priority         
         */ 
        inline int getPriority() { return priority; }
        /**
         * Checks the modul's status.
         * @return module's status (one of the values from the UmbraModuleStatus enum)        
         */ 
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
