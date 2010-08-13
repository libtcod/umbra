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

#ifndef _UTILITIES_HPP_
#define _UTILITIES_HPP_

#include "main.hpp"

class Point {
	public:
		int x, y;
		inline void set(int x, int y) { this->x = x; this->y = y; }
		inline void offset(int sx, int sy) { if((unsigned)(x+sx)<MAXX && (unsigned)(y+sy)<MAXY) {x += sx; y += sy;} }
		//overload operators
		bool operator == (const Point &p) const { return this->x == p.x && this->y == p.y; }
		bool operator != (const Point &p) const { return this->x != p.x || this->y != p.y; }
		//ctors
		Point(int x, int y) { set(x,y); }
		Point(): x(0), y(0);
};

class Rect {
	public:
		int x, y, w, h;
		inline void set(int x, int y, int w, int h) { this->x = x; this->y = y; this->w = w; this->h = h; }
		bool offset(int sx, int sy);
		bool checkIntersection(const Rect &r) const;
		bool contains(const Point &p) const;
		Rect(int x, int y, int w, int h) { set(x,y,w,h); }
		Rect(): x(0), y(0), w(0), h(0);
};

#endif
