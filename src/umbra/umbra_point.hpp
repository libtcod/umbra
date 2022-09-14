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
#include <libtcod/mouse_types.h>

struct UmbraPoint {
	constexpr UmbraPoint() noexcept = default;
	constexpr UmbraPoint(int new_x, int new_y) noexcept: x{new_x}, y{new_y} {}
	/**
	 * Sets the point's coordinates.
	 * @param x the point's <i>x</i> coordinate
	 * @param y the point's <i>y</i> coordinate
	 */
	constexpr void set(int new_x, int new_y) noexcept {
		x=new_x;
		y=new_y;
	}
	/**
	 * Checks whether the point's coordinates match the provided pair.
	 * @param px the <i>x</i> coordinate to be compared
	 * @param py the <i>y</i> coordinate to be compared
	 * @return <code>true</code> if the coordinates match, <code>false</code> if they don't
	 */
	[[nodiscard]] constexpr bool is(int px, int py) const noexcept { return px == x && py == y; }
	/**
	 * Checks whether the point's coordinates match the provided pair.
	 * @param p the point to be checked against
	 * @return <code>true</code> if the coordinates match, <code>false</code> if they don't
	 */
	[[nodiscard]] constexpr bool is(const UmbraPoint &p) const noexcept { return *this == p; }
	/**
	 * Sets the <code>mouseHover</code> and <code>mouseDown</code> statuses for the rectangle.
	 * @param px the <i>x</i> coordinate to be compared
	 * @param py the <i>y</i> coordinate to be compared
	 * @param ms a reference to the mouse event object
	 */
	void mouse(int px, int py, TCOD_mouse_t &ms) noexcept {
		mouseHover = is(px, py);
		mouseDown = mouseHover & ms.lbutton;
	}
	/**
	 * Sets the <code>mouseHover</code> and <code>mouseDown</code> statuses for the rectangle.
	 * @param p the point to be checked against
	 * @param ms a reference to the mouse event object
	 */
	void mouse(UmbraPoint &p, TCOD_mouse_t &ms) noexcept {
		mouseHover = is(p);
		mouseDown = mouseHover & ms.lbutton;
	}
	friend [[nodiscard]] constexpr bool operator==(const UmbraPoint& lhs, const UmbraPoint &rhs) noexcept {
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
	friend [[nodiscard]] constexpr bool operator!=(const UmbraPoint& lhs, const UmbraPoint &rhs) noexcept {
		return !(lhs == rhs);
	}
	int x = 0;
	int y = 0;
	bool mouseHover = false;
	bool mouseDown = false;
};
