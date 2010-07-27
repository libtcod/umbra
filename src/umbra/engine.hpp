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

class UmbraModule;
class UmbraCallback;

class UmbraKey {
	friend class UmbraEngine;
	friend class UmbraCallback;
	public:
		UmbraKey (): vk(TCODK_NONE),c(0),alt(false),ctrl(false),shift(false) {}
		UmbraKey (TCOD_keycode_t vk, char c, bool alt, bool ctrl, bool shift): vk(vk),c(c),alt(alt),ctrl(ctrl),shift(shift) {}
		inline void assign (TCOD_keycode_t vk, char c, bool alt, bool ctrl, bool shift) { this->vk=vk; this->c=c; this->alt=alt; this->ctrl=ctrl; this->shift=shift; }
		inline void assign (UmbraKey k1) { vk=k1.vk; c=k1.c; alt=k1.alt; ctrl=k1.ctrl; shift=k1.shift; }
		inline bool operator == (const UmbraKey &k1) { return memcmp (this, &k1, sizeof(UmbraKey)) == 0; }
	private:
		TCOD_keycode_t vk;
		char c;
		bool alt;
		bool ctrl;
		bool shift;
};

enum UmbraKeyboardMode {
	UMBRA_KEYBOARD_WAIT,
	UMBRA_KEYBOARD_WAIT_NOFLUSH,
	UMBRA_KEYBOARD_RELEASED,
	UMBRA_KEYBOARD_PRESSED,
	UMBRA_KEYBOARD_PRESSED_RELEASED
};

enum UmbraKeybinding {
	UMBRA_KEYBINDING_QUIT,
	UMBRA_KEYBINDING_FULLSCREEN,
	UMBRA_KEYBINDING_SCREENSHOT,
	UMBRA_KEYBINDING_FONT_UP,
	UMBRA_KEYBINDING_FONT_DOWN,
	UMBRA_KEYBINDING_PAUSE,
	UMBRA_KEYBINDING_SPEEDOMETER,
	UMBRA_KEYBINDING_MAX
};

enum UmbraInternalModuleID {
	UMBRA_INTERNAL_SPEEDOMETER,
	UMBRA_INTERNAL_BSOD,
	UMBRA_INTERNAL_MAX
};

//the main engine
class UmbraEngine {
	public:
		UmbraEngine (const char *fileName = "data/cfg/umbra.txt",
		            bool registerDefaultCallbacks = true,
		            bool registerAdditionalCallbacks = false); //constructor

		int registerModule (UmbraModule * module, int fallback = (-1)); //add a module to the modules list. returns id
		void registerFont (int columns, int rows, const char * filename, int flags = TCOD_FONT_LAYOUT_TCOD);
		bool initialise (TCOD_renderer_t renderer = TCOD_RENDERER_SDL); //initialises the engine
		void reinitialise (TCOD_renderer_t renderer = TCOD_RENDERER_SDL);
		int run (); //runs the engine

		void setWindowTitle (const char * title, ...);
		void setWindowTitle (std::string title);
		inline void setKeyboardMode (UmbraKeyboardMode mode) { keyboardMode = mode; }
		inline void setPaused (bool pause) { paused = pause; }
		inline void registerCallback (UmbraCallback * cbk) {callbacks.push(cbk); }

		// register a module for activation next frame, either by id or reference
		void activateModule (int moduleId);
		void activateModule (UmbraModule *mod);
		void activateModule (UmbraInternalModuleID id);
		// register a module for deactivation next frame either by id or reference
		void deactivateModule (int moduleId);
		void deactivateModule (UmbraModule * mod);
		void deactivateModule (UmbraInternalModuleID id);
		//deactivate all modules (the program will end normally)
		void deactivateAll ();

		inline bool getPaused () { return paused; }
		inline UmbraKeyboardMode getKeyboardMode () { return keyboardMode; }
		inline UmbraModule * getModule (int moduleId) { return (moduleId < 0 || moduleId >= modules.size() ? NULL : modules.get(moduleId)); }
		inline UmbraModule * getModule (UmbraInternalModuleID id) { return (id < 0 || id >= UMBRA_INTERNAL_MAX ? NULL : internalModules[id]); }
		inline static UmbraEngine * getInstance () { if (engineInstance == NULL) engineInstance = new UmbraEngine(); return engineInstance; }

		void displayError ();

		//Config-related stuff
		inline bool activateFont (int shift = 0) { return UmbraConfig::activateFont(shift); }

		inline int getRootWidth () { return UmbraConfig::rootWidth; }
		inline int getRootHeight () { return UmbraConfig::rootHeight; }

		inline int getFontID() { return UmbraConfig::fontID; }
		inline int getNbFonts() { return UmbraConfig::fonts.size(); }
		inline const char * getFontDir() { return UmbraConfig::fontDir; }

		static void setRootDimensions (int w, int h) { UmbraConfig::rootWidth = w; UmbraConfig::rootHeight = h; getInstance()->reinitialise(renderer); }

	private:
		static UmbraEngine * engineInstance;
		std::string windowTitle;
		void keyboard (TCOD_key_t &key);
		bool paused;
		static TCOD_renderer_t renderer;

		TCODList <UmbraModule*> modules; // list of all registered modules
		TCODList <UmbraModule*> activeModules; // currently active modules
		TCODList <UmbraModule*> toActivate; // modules to activate next frame
		TCODList <UmbraModule*> toDeactivate; // modules to deactivate next frame
		UmbraKeyboardMode keyboardMode;

		//the keybinding callbacks
		TCODList <UmbraCallback *> callbacks;

		// actually put the module in active list
		void doActivateModule( UmbraModule *mod );
		// font autodetection if no font is registered
		bool registerFonts ();

		//the internal modules stuff
		UmbraModule * internalModules[UMBRA_INTERNAL_MAX];
		void registerInternalModule (UmbraInternalModuleID id, UmbraModule * module);
};
