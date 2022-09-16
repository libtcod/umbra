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
#pragma once
#include <libtcod/console_types.h>

class UmbraKey {
	friend class UmbraEngine;
	friend class UmbraCallback;
	public:
		UmbraKey() = default;
		UmbraKey(TCOD_keycode_t vk, char c, bool alt, bool ctrl, bool shift)
			: vk_{vk}, c_{c}, alt_{alt}, ctrl_{ctrl}, shift_{shift} {}
		/**
		 * Assigns a keystroke or key combination. In case of alt, ctrl and shift keys, left and right keys are not distinguished (due to incomplete support in SDL).
		 * @param vk the non-printable key code, using TCOD_keycode_t constants (see libtcod documentation). Set to TCODK_NONE if none is expected
		 * @param c a printable character key. Set to 0 if none is expected
		 * @param alt boolean indicating whether the alt key is expected to be pressed
		 * @param ctrl boolean indicating whether the ctrl key is expected to be pressed
		 * @param shift boolean indicating whether the shift key is expected to be pressed
		 */
		[[deprecated("Use normal assignment instead of this method.")]]
		void assign (TCOD_keycode_t vk, char c, bool alt, bool ctrl, bool shift) {
			(*this) = UmbraKey{vk, c, alt, ctrl, shift};
		}
		[[nodiscard]] bool operator==(const UmbraKey &rhs) {
			return vk_ == rhs.vk_ && c_ == rhs.c_ && alt_ == rhs.alt_ && ctrl_ == rhs.ctrl_ && shift_ == rhs.shift_;
		}
		[[nodiscard]] bool operator!=(const UmbraKey &rhs) { return !((*this) == rhs); }
	private:
		TCOD_keycode_t vk_{TCODK_NONE};
		char c_{0};
		bool alt_{false};
		bool ctrl_{false};
		bool shift_{false};
};
