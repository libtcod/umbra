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

class UmbraModule;

//the main engine
class UmbraEngine {
    public:
        UmbraEngine (void); //constructor
        ~UmbraEngine (void);
        bool initialise (void); //initialises the engine
        int run (void); //runs the engine
        int registerModule (UmbraModule * module, int fallback = (-1)); //add a module to the modules list. returns id
        void registerFont (int rows, int columns, const char * filename, int flags = TCOD_FONT_LAYOUT_TCOD);
        void registerFonts (void);
        void activateModule (int moduleId);
        void deactivateModule (int moduleId);
    private:
        void keyboard (TCOD_key_t &key);
        void reinitialise (void);
        bool paused;

        TCODList <UmbraModule*> modules; // list of all registered modules
        TCODList <UmbraModule*> activeModules; // currently active modules
        TCODList <UmbraModule*> toActivate; // modules to activate next frame
        TCODList <UmbraModule*> toDeactivate; // modules to deactivate next frame
};
