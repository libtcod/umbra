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

		/**
		 * Custom code that is executed once and only once, when the module is activated for the first time.<br>It is used mainly to allocate resources that might be unavailable at the moment of the module's instantiation.
		 */
		virtual void initialise (); // allocate resources. called only once
		/**
		 * Custom code controlling what and how is displayed on the console. Called automatically after <code>update()</code>.
		 */
		virtual void render () { } //render the module on the root console
		/**
		 * Custom code used for updating the module's internal logic. Called automatically before <code>render()</code>.
		 * @return <code>true</code> if the module should remain active, <code>false</code> if it should be deactivated.
		 */
		virtual bool update () { return getActive(); } //update the module's logic
		/**
		 * Implementation of any module-specific keyboard event interpretation. Called automatically.
		 * @param key a reference to the key event object
		 */
		virtual void keyboard (TCOD_key_t &key) { } //module-specific keyboard
		/**
		 * Implementation of any module-specific mouse event interpretation. Called automatically
		 * @param ms a reference to the mouse event object
		 */
		virtual void mouse (TCOD_mouse_t &ms) { } //module-specific mouse

		//setters
		/**
		 * Sets the fallback module. Please refer to Umbra documentation for detailed information about fallbacks.
		 * @param fback the ID of the fallback module.
		 */
		inline void setFallback (int fback) { fallback = fback; } //set default fallback module's index
		/**
		 * Sets the module's timeout.
		 * @param val the number of milliseconds that the module will be allowed to run before timing out. Set to 0 if the timeout is to be removed.		 
		 */
		inline void setTimeout (uint32 val) { timeout = val; }
		/**
		 * Activates or deactivates the module.
		 * @param active <code>true</code> if the module is to be activated, <code>false</code> otherwise
		 */
		void setActive (bool active);
		/**
		 * Pauses or unpauses the module.
		 * @param paused <code>true</code> if the module is to be paused, <code>false</code> otherwise
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
		 * @return <code>true</code> if the module is paused, <code>false</code> otherwise
		 */
		inline bool getPause () { return status == UMBRA_PAUSED; }
		/**
		 * Checks whether the module has been activated.
		 * @return <code>true</code> if the module has been activated, <code>false</code> otherwise
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
		 * Checks the module's status.
		 * @return module's status (one of the values from the UmbraModuleStatus enum)
		 */
		inline UmbraModuleStatus getStatus () { return status; }

	protected:
		/**
		 * Custom code that is executed each time the module is activated
		 */
		virtual void activate() {}
		/**
		 * Custom code that is executed each time the module is deactivated
		 */
		virtual void deactivate() {}
		/**
		 * Custom code that is executed each time the module is paused
		 */
		virtual void pause() {}
		/**
		 * Custom code that is executed each time the module is resumed
		 */
		virtual void resume() {}
		int priority; // update order (inverse of render order)
	private:
		friend class UmbraEngine;
		UmbraModuleStatus status;
		int fallback; //fallback module's index
		uint32 timeout;
		uint32 timeoutEnd;
		void initialiseTimeout();
		inline bool isTimedOut(uint32 currentTime) { return (timeoutEnd > currentTime) ? false : true; }
};
