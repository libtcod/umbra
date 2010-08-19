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

#include "entities.hpp"
#include "gameview.hpp"

/* Entity */

Entity::Entity() {
	removed = false;
}

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
	coords = Point(MAXX/2, MAXY-4);
	area = Rect(MAXX/2-1,MAXY-4,3,3);
	type = ENTITY_SHIP;
}

bool Ship::move(int sx, int sy, uint32 curTime) {
	if (lastMovementTime + speed <= curTime) {
		if (area.offset(sx,sy)) {
			coords.offset(sx,sy);
			lastMovementTime = curTime;
		}
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
	TCODConsole::root->printEx(coords.x,coords.y,TCOD_BKGND_NONE,TCOD_CENTER,"A\nbMd\n^ ^");
}

/* Bullet */

Bullet::Bullet(Point p) {
	speed = 50;
	lastMovementTime = 0;
	coords = p;
	area = Rect(p.x,p.y,1,1);
	type = ENTITY_BULLET;
}

Bullet::Bullet(Rect r) {
	speed = 50;
	lastMovementTime = 0;
	coords = Point(r.x,r.y);
	area = r;
	type = ENTITY_BULLET;
}

bool Bullet::move(int sx, int sy, uint32 curTime) {
	if (lastMovementTime + speed <= curTime) {
		if (coords.y == 0) return false;
		else {
			coords.y--;
			area.y--;
			lastMovementTime = curTime;
		}
	}
	return true;
}

void Bullet::render() {
	TCODConsole::root->putChar(coords.x,coords.y,'|',TCOD_BKGND_NONE);
}

/* Alien */

Alien::Alien(Point p) {
	health = 1;
	speed = 500;
	lastMovementTime = 0;
	coords = p;
	area = Rect(p.x-1,p.y,3,1);
	delta = 1;
	type = ENTITY_ALIEN;
}

void Alien::render() {
	TCODConsole::root->printEx(coords.x,coords.y,TCOD_BKGND_NONE,TCOD_CENTER,"/M\\");
}

bool Alien::move(int sx, int sy, uint32 curTime) {
	if (lastMovementTime + speed <= curTime) {
		speed--;
		if (!area.offset(delta,0)) {
			delta = -delta;
			coords.offset(0,1);
			area.y++;
		}
		else
			coords.offset(delta,0);
		lastMovementTime = curTime;
	}
	return true;
}

void Alien::hit() {
	GameView * game = (GameView*)(UmbraEngine::getInstance()->getModule(MOD_GAME_VIEW));
	health--;
	if (health == 0) {
		game->alienCount--;
		if (!removed) {
			removed = true;
			game->removeList.push(this);
		}
	}
}
