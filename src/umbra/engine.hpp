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
#ifndef UMBRA_ENGINE_HPP
#define UMBRA_ENGINE_HPP

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <fmt/printf.h>
#include <libtcod/console_types.h>

#include <iostream>
#include <libtcod/list.hpp>
#include <string>

#include "callback_fwd.hpp"
#include "config.hpp"
#include "key.hpp"
#include "module.hpp"
#include "module_factory.hpp"

/**
 * The keyboard modes available in Umbra. They correspond to the ones used in libtcod.
 */
enum UmbraKeyboardMode {
  UMBRA_KEYBOARD_WAIT,
  UMBRA_KEYBOARD_WAIT_NOFLUSH,
  UMBRA_KEYBOARD_RELEASED,
  UMBRA_KEYBOARD_PRESSED,
  UMBRA_KEYBOARD_PRESSED_RELEASED,
  UMBRA_KEYBOARD_SDL,  // Use SDL for events.  Libtcod events are processed immediately and there will be no input lag.
};

/**
 * IDs used to reference internal modules.
 */
enum UmbraInternalModuleID {
  UMBRA_INTERNAL_SPEEDOMETER,
  UMBRA_INTERNAL_BSOD,
  UMBRA_INTERNAL_CREDITS,
  UMBRA_INTERNAL_MAX
};

/**
 * Flags used to register callbacks. They can be combined using bitwise <code>OR</code>.
 */
enum UmbraRegisterCallbackFlag {
  UMBRA_REGISTER_NONE = 0x00000000,
  UMBRA_REGISTER_DEFAULT = 0x00000001,
  UMBRA_REGISTER_ADDITIONAL = 0x00000002,
  UMBRA_REGISTER_ALL = 0xFFFFFFFF
};

struct UmbraCustomCharMap {
  int x;
  int y;
  int code;
};

// the main engine
class UmbraEngine {
 public:
  /**
   * The constructor.
   * @param fileName the filename from which to read Umbra's configuration.
   * @param flag the callback registering flags, used to choose which callbacks are to be registered in the application.
   */
  UmbraEngine(const char* fileName = "data/cfg/umbra.txt", UmbraRegisterCallbackFlag flag = UMBRA_REGISTER_DEFAULT);
  /**
   * The constructor.
   * @param flag the callback registering flags, used to choose which callbacks are to be registered in the application.
   */
  UmbraEngine(UmbraRegisterCallbackFlag flag) : UmbraEngine{"data/cfg/umbra.txt", flag} {}

  ~UmbraEngine();

  /**
   * Add custom character mapping. Mappings are put on queue for UmbraEngine::initialise()/reinitialise() to call them.
   * @param x position of character in font file
   * @param y position of character in font file
   * @param ascii code associated with the character
   */
  void addCustomCharacter(int x, int y, int code);

  /**
   * Checks whether a module name has already been used in order to prevent registering modules with the same name.
   * @param name the module name to be checked
   * @return <code>true</code> if the name is free and available for use, <code>false</code> otherwise
   */
  bool isNameFree(const char* name);
  /**
   * Registers a module for usage in the application. Unregistered modules cannot be activated. Registering is done only
   * once per application run.<br><i>Note: this method only registers the module, but doesn't activate it. Activation is
   * performed using the UmbraEngine::activateModule(*) methods!</i>
   * @param module a pointer to the module to be registered. Creating the module using the <code>new</code> keyword is
   * strongly encouraged, eg. <code>registerModule(new myModule());</code>
   * @param name the module's name
   * @return the module's unique ID number (0 for the first registered module, 1 for the second, etc.)
   */
  int registerModule(UmbraModule* module, const char* name = NULL);  // add a module to the modules list. returns id
  /**
   * Registers a font for usage in the application.<br><i>Note: you are encouraged to let the engine register fonts
   * automatically. Please refer to the documentation regarding font autodetection.</i>
   * @param columns number of character columns in the font image file
   * @param rows number of character rows in the font image file
   * @param filename the filename of the font image file
   * @param flags font layout flags. Please refer to <b>libtcod</b> documentation for more information on font layout
   * flags.
   */
  void registerFont(int columns, int rows, const char* filename, int flags = TCOD_FONT_LAYOUT_TCOD);
  /**
   * Read module configuration from the given filename, or the filename defined as moduleConfig in umbra.txt.<br>If
   * there's no filename or the file cannot be read, return false.
   * @param filename name of the module configuration file
   * @param factory a module factory
   * @param chainName (optional) the name of the module chain to load. Leave at default to load the chain specified in
   * <code>umbra.txt</code> or, in case it's not specified, the first module chain that's encountered in the module
   * configuration file.
   * @return <code>true</code> if module configuration has been loaded successfully, <code>false</code> otherwise
   */
  bool loadModuleConfiguration(const char* filename, UmbraModuleFactory* factory, const char* chainName = NULL);
  /**
   * Read module configuration from the given filename, or the filename defined as moduleConfig in umbra.txt.<br>If
   * there's no filename or the file cannot be read, return false.
   * @param filename name of the module configuration file
   * @param chainName (optional) the name of the module chain to load. Leave at default to load the chain specified in
   * <code>umbra.txt</code> or, in case it's not specified, the first module chain that's encountered in the module
   * configuration file.
   * @return <code>true</code> if module configuration has been loaded successfully, <code>false</code> otherwise
   */
  bool loadModuleConfiguration(const char* filename, const char* chainName = NULL);
  /**
   * Initialises the engine.
   * @param renderer the renderer to be used (defaults to SDL)
   * @return <code>true</code> if initialisation is successful, <code>false</code> if errors were encountered
   */
  bool initialise(TCOD_renderer_t renderer = TCOD_RENDERER_SDL2);
  /**
   * Reinitialises an already initialised engine. Used mainly when the console font or the window title change.
   * @param renderer the renderer to be used (defaults to SDL)
   */
  void reinitialise(TCOD_renderer_t renderer = TCOD_RENDERER_SDL2);
  /**
   * Runs the engine.
   * @return the result of running the application: <i>0</i> if no errors have occurred, different value otherwise.
   */
  [[deprecated("Should call onFrame, OnEvent, and onQuit instead")]] int run();
  /**
   * @brief Handle an iteration of game logic.
   * @return The SDL_AppResult for an SDL main callback
   */
  SDL_AppResult onFrame();
  /**
   * @brief Handle an SDL_Event.
   *
   * @param event The SDL_Event to process.
   * @return The SDL_AppResult for an SDL main callback
   */
  SDL_AppResult onEvent(SDL_Event& event);
  /**
   * @brief Handle the shutdown on the engine.
   */
  void onQuit();
  /**
   * Sets the window title.<br><i>Note: this method is usually called before initialising the engine. Should it be
   * called after the engine has been initialised, the title won't be changed util the engine is reinitialised.</i>
   * @param title the main program window's new title
   * @param ... optional printf-like formatting of the title
   */
  template <typename S, typename... T>
  void setWindowTitle(const S& title, const T&... args) {
    setWindowTitle(fmt::sprintf(title, args...));
  }
  /**
   * Sets the window title.<br><i>Note: this method is usually called before initialising the engine. Should it be
   * called after the engine has been initialised, the title won't be changed util the engine is reinitialised.</i>
   * @param title the main program window's new title
   */
  void setWindowTitle(std::string title);
  /**
   * Sets the keyboard mode.
   * @param mode keyboard mode, as defined in the <code>UmbraKeyboardMode</code> enum.
   */
  inline void setKeyboardMode(UmbraKeyboardMode mode) { keyboardMode = mode; }
  /**
   * Pauses or unpauses the engine.
   * @param pause <code>true</code> if the engine is to be paused, <code>false</code> otherwise
   */
  inline void setPause(bool pause) { paused = pause; }
  /**
   * Registers a new keyboard callback.
   * @param cbk a pointer to the keyboard callback. You're encouraged to create the callback using the <code>new</code>
   * keyword here: <code>registerCallback(new MyCallback());</code>
   */
  inline void registerCallback(UmbraCallback* cbk) { callbacks.push_back(cbk); }
  /**
   * Activates a module.
   * @param moduleId the identification number of the module to be activated
   */
  void activateModule(int moduleId);
  /**
   * Activates a module.
   * @param mod a pointer to the module object to be activated
   */
  void activateModule(UmbraModule* mod);
  /**
   * Activates an internal module.
   * @param id the identification number of the internal module to be activated
   */
  void activateModule(UmbraInternalModuleID id);
  /**
   * Activates a module.
   * @param moduleName the name of the module to be activated
   */
  void activateModule(const char* name);
  /**
   * Deactivates a module.
   * @param moduleId the identification number of the module to be deactivated
   */
  void deactivateModule(int moduleId);
  /**
   * Deactivates a module.
   * @param mod a pointer to the module object to be deactivated
   */
  void deactivateModule(UmbraModule* mod);
  /**
   * Deactivates an internal module.
   * @param id the identification number of the internal module to be deactivated
   */
  void deactivateModule(UmbraInternalModuleID id);
  /**
   * Deactivates a module.
   * @param moduleName the name of the module be deactivated
   */
  void deactivateModule(const char* name);
  /**
   * Deactivates all active modules, either letting their respective fallbacks to get activated, or ignoring fallbacks
   * completely.
   * @param ignoreFallbacks <code>true</code> if the fallbacks should be ignored, <code>false</code> or default value if
   * the fallbacks should be allowed to get activated.
   */
  void deactivateAll(bool ignoreFallbacks = false);
  /**
   * Gets the message log level. All messages with a lower severity level will be discarded when creating the message
   * log.
   * @return the log level, as defined in the configuration file
   */
  inline UmbraLogLevel getLogLevel() { return UmbraConfig::logLevel; }
  /**
   * Retrieves the paused state of the engine.
   * @return <code>true</code> if the engine is currently paused, <code>false</code> otherwise
   */
  inline bool getPause() { return paused; }
  /**
   * Retrieves the keyboard mode used by the engine.
   * @return the currently used keyboard mode
   */
  inline UmbraKeyboardMode getKeyboardMode() { return keyboardMode; }
  /**
   * Fetches a pointer to a module.
   * @param moduleId the identification number of the module to which a pointer is to be fetched
   * @return a pointer to the requested module
   */
  inline UmbraModule* getModule(int moduleId) {
    return (moduleId < 0 || moduleId >= modules.size() ? NULL : modules.at(moduleId));
  }
  /**
   * Fetches a pointer to a module.
   * @param moduleName the name of the module to which a pointer is to be fetched
   * @return a pointer to the requested module
   */
  UmbraModule* getModule(const char* name);
  /**
   * Retrieve the module id from its name
   * @param mod pointer to the module
   * @return the module's id
   */
  int getModuleId(const char* name);
  /**
   * Retrieve the module id from its reference
   * @param mod pointer to the module
   * @return the module's id
   */
  int getModuleId(UmbraModule* mod);
  /**
   * Fetches a pointer to an internal module.
   * @param id the identification number of the internal module to which a pointer is to be fetched
   * @return a pointer to the requested internal module
   */
  inline UmbraModule* getModule(UmbraInternalModuleID id) {
    return (id < 0 || id >= UMBRA_INTERNAL_MAX ? NULL : internalModules[id]);
  }
  /**
   * Fetches a pointer to the engine instance.
   * @return a pointer to the engine
   */
  inline static UmbraEngine* getInstance() {
    if (engineInstance == NULL) engineInstance = new UmbraEngine();
    return engineInstance;
  }
  /**
   * Displays the last logged error using the inbuilt BSOD module.
   */
  void displayError();
  /**
   * Activates a different font.
   * @param shift a number indicating whether to activate the next or the previous font in the registered fonts
   * list.<br>This can be -1 (switch down) or 1 (switch up). All other numbers will be clamped to these values.<br>A
   * value of 0 results in doing nothing.
   * @return <code>true</code> if the font has been successfully changed, <code>false</code> otherwise
   */
  inline bool activateFont(int shift = 0) { return UmbraConfig::activateFont(shift); }
  /**
   * Retrieves the width of the console in cells.
   * @return the console's width
   */
  inline int getRootWidth() { return UmbraConfig::rootWidth; }
  /**
   * Retrieves the height of the console in cells.
   * @return the console's height
   */
  inline int getRootHeight() { return UmbraConfig::rootHeight; }
  /**
   * Retrieves the ID number of the currently used font.
   * @return current font's ID
   */
  inline int getFontID() { return UmbraConfig::fontID; }
  /**
   * Retrieves the total number of registered fonts.
   * @return number of registered fonts
   */
  int getNbFonts() { return static_cast<int>(UmbraConfig::fonts.size()); }
  /**
   * Retrieves the font directory.
   * @return the font direcory
   */
  std::filesystem::path getFontDir() { return UmbraConfig::fontDir; }
  /**
   * Sets the root console's dimensions in cells.
   * @param w the root console's width
   * @param h the root console's height
   */
  static void setRootDimensions(int w, int h) {
    UmbraConfig::rootWidth = w;
    UmbraConfig::rootHeight = h;
    getInstance()->reinitialise(renderer);
  }
  /**
   * Displays a credits line.
   * @param x the <code>x</code> coordinate of the credits line placement on the root console
   * @param y the <code>y</code> coordinate of the credits line placement on the root console
   * @param duration the total duration of the display (half of which is the fade out)
   */
  void printCredits(int x, int y, uint32_t duration = 10000);

 private:
  /**
   * Register custom characters
   */
  void registerCustomCharacters();

  static UmbraEngine* engineInstance;
  static TCOD_renderer_t renderer;
  std::string windowTitle{""};
  bool paused{false};
  std::vector<UmbraCustomCharMap> customChars{};  // List of custom chars to add
  std::vector<UmbraModule*> modules{};  // list of all registered modules
  std::vector<UmbraModule*> activeModules{};  // currently active modules
  std::vector<UmbraModule*> toActivate{};  // modules to activate next frame
  std::vector<UmbraModule*> toDeactivate{};  // modules to deactivate next frame
  UmbraModule* internalModules[UMBRA_INTERNAL_MAX]{};
  UmbraKeyboardMode keyboardMode{UMBRA_KEYBOARD_RELEASED};
  std::vector<UmbraCallback*> callbacks{};  // the keybinding callbacks
  TCOD_key_t key_{};  // TCOD key dirty state
  TCOD_mouse_t mouse_{};  // TCOD mouse dirty state
  /**
   * Parses the keyboard input and passes it to the registered callbacks.
   * @param key a reference to the keyboard event object
   */
  void keyboard(TCOD_key_t& key);
  /**
   * Puts the newly activated module in the active modules list.
   * @param mod a pointer to the module that's being activated
   */
  void doActivateModule(UmbraModule* mod);
  /**
   * Performs font autodetection and registered any found fonts.
   * @return <code>true</code> if at least one font has been registered, <code>false</code> otherwise
   */
  bool registerFonts();
  /**
   * Registers an internal module for usage in the application.
   * @param id the ID number of an internal module
   * @param module a pointer to the internal module to be registered.
   */
  void registerInternalModule(UmbraInternalModuleID id, UmbraModule* module);
  /// @brief SDL event watcher.
  static bool onSDLEvent(void* userdata, SDL_Event* event);
};

#endif
