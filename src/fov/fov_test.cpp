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

#include "main.hpp"

FovTest* FovTest::getTest(int algoNum,int testNum) {
	// test factory
	FovTest *ret=NULL;
	switch(testNum) {
		case FOV_TEST_PILLAR1 : ret=new FovPillar1(); break;
		case FOV_TEST_PILLAR2 : ret=new FovPillar2(); break;
		case FOV_TEST_CORNER1 : ret=new FovCorner1(); break;
		case FOV_TEST_CORNER2 : ret=new FovCorner2(); break;
		default:break; 
	}
	if ( ret == NULL ) return ret; // not implemented
	ret->algoNum=algoNum;
	ret->testNum=testNum;
	return ret;
}

void FovTest::run() {
	startCounter();
	execute();
	stopCounter();
}

void FovTest::render(TCODConsole *con,int x, int y) {
	static TCODColor darkWall(0,0,100);
	static TCODColor lightWall(130,110,50);
	static TCODColor darkGround(50,50,150);
	static TCODColor lightGround(200,180,50);
	for (int mx=0; mx < map->getWidth(); mx++ ) {
		for (int my=0; my < map->getHeight(); my++ ) {
			 if ( playerx==mx && playery==my) {
			 	con->putCharEx(x+mx,y+my,'@',TCODColor::white,lightGround);
			 } else {
			 	bool transp=map->isTransparent(mx,my);
			 	bool infov=map->isInFov(mx,my);
			 	TCODColor col;
			 	if ( transp ) {
					col = infov ? lightGround:darkGround;
				} else {
					col = infov ? lightWall:darkWall;
				}  
			 	con->putCharEx(x+mx,y+my,' ', TCODColor::white,col);
			 }
		}
	}
}

void FovTest::execute() {
	map->computeFov(playerx,playery,0,true,(TCOD_fov_algorithm_t)algoNum);
}

void FovPillar1::initialise() {
	// build an empty map with a single pillar at the center
	map = new TCODMap(11,11);
	map->clear(true,true);
	map->setProperties(5,5,false,false);
	// player against the pillar
	playerx=4;
	playery=5;
}


void FovPillar2::initialise() {
	FovPillar1::initialise();
	// same as pillar 1. only the player pos changes
	playerx=1;
	playery=3;
}

void FovCorner1::initialise() {
	// build a T junction corridor
	map = new TCODMap(15,11);
	map->clear(false,false);
	for (int x=0; x < 15; x++) map->setProperties(x,5,true,true);
	for (int y=6;y<11;y++) map->setProperties(7,y,true,true);
	// player at the T junction
	playerx=7;
	playery=6;
}

