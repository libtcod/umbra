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

#include <iostream>

class UmbraModule;
class UmbraCallback;

class UmbraKey {
	friend class UmbraEngine;
	friend class UmbraCallback;
	public:
		UmbraKey (): vk(TCODK_NONE),c(0),alt(false),ctrl(false),shift(false) {}
		UmbraKey (TCOD_keycode_t vk, char c, bool alt, bool ctrl, bool shift): vk(vk),c(c),alt(alt),ctrl(ctrl),shift(shift) {}
		/**
		 * Assigns a keystroke or key combination. In case of alt, ctrl and shift keys, left and right keys are not distinguished (due to incomplete support in SDL).
		 * @param vk the non-printable key code, using TCOD_keycode_t constants (see libtcod documentation). Set to TCODK_NONE if none is expected
		 * @param c a printable character key. Set to 0 if none is expected
		 * @param alt boolean indicating whether the alt key is expected to be pressed
		 * @param ctrl boolean indicating whether the ctrl key is expected to be pressed
		 * @param shift boolean indicating whether the shift key is expected to be pressed                   		 
		 */     		
		inline void assign (TCOD_keycode_t vk, char c, bool alt, bool ctrl, bool shift) { this->vk=vk; this->c=c; this->alt=alt; this->ctrl=ctrl; this->shift=shift; }
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

enum UmbraInternalModuleID {
	UMBRA_INTERNAL_SPEEDOMETER,
	UMBRA_INTERNAL_BSOD,
	UMBRA_INTERNAL_MAX
};

enum UmbraRegisterCallbackFlag {
	UMBRA_REGISTER_NONE       = 0x00000000,
	UMBRA_REGISTER_DEFAULT    = 0x00000001,
	UMBRA_REGISTER_ADDITIONAL = 0x00000002,
	UMBRA_REGISTER_ALL        = 0xFFFFFFFF
};

//the main engine
class UmbraEngine {
	public:
		UmbraEngine (const char *fileName = "data/cfg/umbra.txt",
		             UmbraRegisterCallbackFlag flag = UMBRA_REGISTER_DEFAULT); //constructor

		/**
		 * Registers a module for usage in the application. Unregistered modules cannot be activated. Registering is done only once per application run.<br><i>Note: this method only registers the module, but doesn't activate it. Activation is performed using the UmbraEngine::activateModule(*) methods!</i>
		 * @param module a pointer to the module to be registered. Creating the module using the <code>new</code> keyword is strongly encouraged, eg. <code>registerModule(new myModule());</code>
		 * @param fallback (optional) the fallback module's ID
		 * @return the module's unique ID number (0 for the first registered module, 1 for the second, etc.)
		 */
		int registerModule (UmbraModule * module, int fallback = (-1)); //add a module to the modules list. returns id
		/**
		 * Registers a font for usage in the application.<br><i>Note: you are encouraged to let the engine register fonts automatically. Please refer to the documentation regarding font autodetection.</i>
		 * @param columns number of character columns in the font image file
		 * @param rows number of character rows in the font image file
		 * @param filename the filename of the font image file
		 * @param flags font layout flags. Please refer to <b>libtcod</b> documentation for more information on font layout flags.
		 */     		
		void registerFont (int columns, int rows, const char * filename, int flags = TCOD_FONT_LAYOUT_TCOD);
		bool initialise (TCOD_renderer_t renderer = TCOD_RENDERER_SDL); //initialises the engine
		void reinitialise (TCOD_renderer_t renderer = TCOD_RENDERER_SDL);
		/**
		 * Runs the engine.
         * @return the result of running the application: <i>0</i> if no errors have occurred, different value otherwise.
         */
		int run (); //runs the engine

		/**
		 * Sets the window title.<br><i>Note: this method is usually called before initialising the engine. Should it be called after the engine has been initialised, the title won't be changed util the engine is reinitialised.</i>
         * @param title the main program window's new title
         * @param ... optional printf-like formatting of the title
         */
		void setWindowTitle (const char * title, ...);
		/**
		 * Sets the window title.<br><i>Note: this method is usually called before initialising the engine. Should it be called after the engine has been initialised, the title won't be changed util the engine is reinitialised.</i>
         * @param title the main program window's new title
         */
		void setWindowTitle (std::string title);
		/**
		 * Sets the keyboard mode.
         * @param mode keyboard mode, as defined in the <code>UmbraKeyboardMode</code> enum.
         */
		inline void setKeyboardMode (UmbraKeyboardMode mode) { keyboardMode = mode; }
		/**
		 * Pauses or unpauses the engine.
         * @param pause <code>true</code> if the engine is to be paused, <code>false</code> otherwise
         */
		inline void setPause (bool pause) { paused = pause; }
		/**
		 * Registers a new keyboard callback.
         * @param cbk a pointer to the keyboard callback. You're encouraged to create the callback using the <code>new</code> keyword here: <code>registerCallback(new MyCallback());</code>
         */
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

		inline bool getPause () { return paused; }
		inline UmbraKeyboardMode getKeyboardMode () { return keyboardMode; }
		inline UmbraModule * getModule (int moduleId) { return (moduleId < 0 || moduleId >= modules.size() ? NULL: modules.get(moduleId)); }
		inline UmbraModule * getModule (UmbraInternalModuleID id) { return (id < 0 || id >= UMBRA_INTERNAL_MAX ? NULL: internalModules[id]); }
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
