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
#include "umbra_point.hpp"
#include <libtcod/mouse_types.h>

struct UmbraRect {
	constexpr UmbraRect() noexcept = default;
	constexpr UmbraRect(int new_x, int new_y) noexcept: x{new_x}, y{new_y} {}
	explicit constexpr UmbraRect(const UmbraPoint &p) noexcept: x{p.x}, y{p.y} {}
	constexpr UmbraRect(int new_x, int new_y, int width, int height) noexcept
	: x{new_x}, y{new_y}, w{width}, h{height} {}
	constexpr UmbraRect(const UmbraPoint &p, int width, int height) noexcept: x{p.x}, y{p.y}, w{width}, h{height} {}
	/**
	 * Sets the rectangle's position.
	 * @param x the rectangle's top left corner's <i>x</i> coordinate
	 * @param y the rectangle's top left corner's <i>y</i> coordinate
	 */
	constexpr void setPos(int new_x, int new_y) noexcept {
		x = new_x;
		y = new_y;
	}
	/**
	 * Sets the rectangle's position.
	 * @param p the point whose coordinates are to become the rectangle's top letf corner's coordinates
	 */
	constexpr void setPos(const UmbraPoint &p) noexcept { x = p.x; y = p.y; }
	/**
	 * Sets the rectangle's size, keeping the top left corner's coordinates unchanged.
	 * @param w the rectangle's width
	 * @param h the rectangle's height
	 */
	constexpr void setSize(int width, int height) noexcept {
		w = width;
		h = height;
	}
	/**
	 * Sets the rectangle's position and size.
	 * @param x the rectangle's top left corner's <i>x</i> coordinate
	 * @param y the rectangle's top left corner's <i>y</i> coordinate
	 * @param w the rectangle's width
	 * @param h the rectangle's height
	 */
	constexpr void set(int new_x, int new_y, int new_w, int new_h) noexcept {
		setPos(new_x, new_y);
		setSize(new_w, new_h);
	}
	/**
	 * Sets the rectangle's position and size.
	 * @param p the point whose coordinates are to become the rectangle's top letf corner's coordinates
	 * @param w the rectangle's width
	 * @param h the rectangle's height
	 */
	constexpr void set(const UmbraPoint &p, int new_w, int new_h) noexcept {
		setPos(p.x, p.y);
		setSize(new_w, new_h);
	}
	/**
	 * Checks whether a set of coordinates is contained within the rectangle. Sets the <code>mouseHover</code> status, so subsequent calls are not necessary within the same frame.
	 * @param px the <i>x</i> coordinate to be checked
	 * @param py the <i>y</i> coordinate to be checked
	 * @return <code>true</code> if the coordinates are within the rectangle, <code>false</code> otherwise
	 */
	[[nodiscard]] constexpr bool contains(int px, int py) const noexcept {
		return px >= x && px < x+w && py >= y && py < y+h;
	}
	/**
	 * Checks whether a point is contained within the rectangle. Sets the <code>mouseHover</code> status, so subsequent calls are not necessary within the same frame.
	 * @param p the point to be checked
	 * @return <code>true</code> if the point is within the rectangle, <code>false</code> otherwise
	 */
	[[nodiscard]] constexpr bool contains(const UmbraPoint &p) const noexcept { return contains(p.x, p.y); }
	/**
	 * Sets the <code>mouseHover</code> and <code>mouseDown</code> statuses for the rectangle.
	 * @param px the <i>x</i> coordinate to be checked
	 * @param py the <i>y</i> coordinate to be checked
	 * @param m a reference to the mouse event object
	 */
	inline void mouse (int px, int py, TCOD_mouse_t &m) noexcept {
		mouseHover = contains(px, py);
		mouseDown = mouseHover & m.lbutton;
	}
	/**
	 * Sets the <code>mouseHover</code> and <code>mouseDown</code> statuses for the rectangle.
	 * @param p the point to be checked
	 * @param m a reference to the mouse event object
	 */
	inline void mouse (const UmbraPoint &p, TCOD_mouse_t &m) noexcept { mouse(p.x, p.y, m); }
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	bool mouseHover = false;
	bool mouseDown = false;
};
