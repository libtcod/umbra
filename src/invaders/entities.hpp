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

#ifndef _ENTITIES_HPP_
#define _ENTITIES_HPP_

#include "utilities.hpp"

class Entity {
	protected:
		uint32 speed;
		uint32 lastMovementTime;
	public:
		Entity_t type;
		Point coords;
		Rect area;
		bool removed;
		virtual bool move(int sx, int sy, uint32 curTime);
		virtual void render();
		Entity();
		virtual ~Entity() {}
};

class Ship: public Entity {
	private:
		uint32 lastShotTime;
		uint32 shootingSpeed;
	public:
		Ship();
		bool move(int sx, int sy, uint32 curTime);
		void render();
		void shoot(TCODList <Entity*> *entities, uint32 curTime);
};

class Bullet: public Entity {
	public:
		bool move(int sx, int sy, uint32 curTime);
		void render();
		Bullet(Point p);
		Bullet(Rect r);
};

class Alien: public Entity {
	private:
		int delta;
	public:
		bool move(int sx, int sy, uint32 curTime);
		void render();
		Alien(Point p);
};

#endif
