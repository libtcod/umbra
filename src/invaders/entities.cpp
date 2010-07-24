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

#include "entities.hpp"

/* Entity */

Entity::Entity() {}

void Entity::render() {
	TCODConsole::root->putChar(coords.x,coords.y,'*',TCOD_BKGND_NONE);
}

bool Entity::move(int sx, int sy, uint32 curTime) {
	if (lastMovementTime + speed <= curTime) {
		coords.offset(sx,sy);
		lastMovementTime = curTime;
	}
	return true;
}

/* Ship */

Ship::Ship() {
	speed = 200;
	shootingSpeed = 500;
	lastMovementTime = lastShotTime = 0;
	coords = Point(MAXX/2, MAXY-3);
}

bool Ship::move(int sx, int sy, uint32 curTime) {
	if (lastMovementTime + speed <= curTime) {
		coords.offset(sx,sy);
		lastMovementTime = curTime;
	}
	return true;
}

void Ship::shoot(TCODList <Entity*> *entities, uint32 curTime) {
	if (lastShotTime + shootingSpeed <= curTime) {
		lastShotTime = curTime;
		entities->push(new Bullet(coords));
	}
}

void Ship::render() {
	TCODConsole::root->printEx(coords.x,coords.y,TCOD_BKGND_NONE,TCOD_CENTER,"A\nbMd");
}

/* Bullet */

Bullet::Bullet(Point p) {
	speed = 50;
	lastMovementTime = 0;
	coords = p;
}

bool Bullet::move(int sx, int sy, uint32 curTime) {
	if (lastMovementTime + speed <= curTime) {
		if (coords.y == 0) return false;
		coords.offset(sx,sy);
		lastMovementTime = curTime;
	}
	return true;
}

void Bullet::render() {
	TCODConsole::root->putChar(coords.x,coords.y,'|',TCOD_BKGND_NONE);
}
