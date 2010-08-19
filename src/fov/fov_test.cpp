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

// map rendering colors
static TCODColor darkWall(0,0,100);
static TCODColor lightWall(130,110,50);
static TCODColor darkGround(50,50,150);
static TCODColor lightGround(200,180,50);

TCODRandom FovTest::rng;

FovTest* FovTest::getTest(int algoNum,int testNum) {
	// test factory
	FovTest *ret=NULL;
	switch(testNum) {
		case FOV_TEST_PILLAR1 : ret=new FovPillar1(); break;
		case FOV_TEST_PILLAR2 : ret=new FovPillar2(); break;
		case FOV_TEST_PILLAR3 : ret=new FovPillar3(); break;
		case FOV_TEST_CORNER1 : ret=new FovCorner1(); break;
		case FOV_TEST_CORNER2 : ret=new FovCorner2(); break;
		case FOV_TEST_DIAGONAL : ret=new FovDiagonal(); break;
		case FOV_TEST_SYMMETRY : ret=new FovSymmetry(); break;
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

void FovTest::getRenderSize(int *w, int *h) {
	*w=map->getWidth();		
	*h=map->getHeight();		
}

void FovTest::render(TCODConsole *con,int x, int y) {
	// standard fov renderer (same as in libtcod's samples)
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

void FovTest::buildOutdoorMap() {
	// empty map with 10% random 1x1 pillars
	int nbCells = map->getWidth()*map->getHeight();
	map->clear(true,true);
	for (int i=0; i < nbCells/10; i++) {
		int x=rng.getInt(0,map->getWidth()-1);
		int y=rng.getInt(0,map->getHeight()-1);
		map->setProperties(x,y,false,false);
	}
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

void FovPillar3::initialise() {
	FovPillar1::initialise();
	// same as pillar 1. only the player pos changes
	playerx=4;
	playery=4;
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

void FovCorner2::initialise() {
    FovCorner1::initialise();
    result = new bool[15];
}

void FovCorner2::render(TCODConsole *con,int x, int y) {
	// render cells that can see the player at the T junction
	for (int mx=0; mx < map->getWidth(); mx++ ) {
		for (int my=0; my < map->getHeight(); my++ ) {
            TCODColor col;
            if ( my != 5 ) col=map->isTransparent(mx,my) ? darkGround : darkWall;
            else col = result[mx] ? lightGround:darkGround;
            con->putCharEx(x+mx,y+my,mx == playerx && my ==playery ? '@' : ' ', TCODColor::white,col);
		}
	}
}

void FovCorner2::execute() {
    // compute fov from each cell in the corridor and see if player is visible
    for (int x=0; x < 15; x++) {
        map->computeFov(x,5,0,true,(TCOD_fov_algorithm_t)algoNum);
        result[x] = map->isInFov(playerx,playery);
    }
}

void FovDiagonal::initialise() {
	// build a diagonal wall
	map = new TCODMap(11,11);
	map->clear(true,true);
	for (int x=0; x < 11; x++) map->setProperties(x,x,false,false);
	// player against the wall
	playerx=6;
	playery=5;
}

void FovSymmetry::initialise() {
	// build a 60x60 outdoor map
	map = new TCODMap(60,60);
	playerx=playery=30;
}

void FovSymmetry::execute() {
	// test on 20 different maps
	#define NB_SYMMETRY_TESTS 20
	nbFovCells=map->getWidth()*map->getHeight();
	nbErrFromPlayer=0;
	nbErrToPlayer=0;
	for (int i=0; i < NB_SYMMETRY_TESTS; i++) {
		buildOutdoorMap();
		map->setProperties(playerx,playery,true,true); // in case there's a pillar at player's position
		
		// create a copy of the map for reverse fov
		TCODMap map2(60,60);
		map2.copy(map);
		// compute the fov from the player point of view
		map->computeFov(playerx,playery,0,true,(TCOD_fov_algorithm_t)algoNum);
		// compute the reverse fov
		for (int x=0; x < map->getWidth(); x++) {
			for ( int y=0; y < map->getHeight(); y++) {
				if (x == playerx && y == playery) continue;
				// compute the fov from x,y and see if the player is in fov
				map2.computeFov(x,y,0,true,(TCOD_fov_algorithm_t)algoNum);
				if ( map->isInFov(x,y) ) {
					if ( ! map2.isInFov(playerx,playery) ) {
						// player can see x,y but x,y cannot see player
						nbErrFromPlayer++;
					}
				} else if ( map2.isInFov(playerx,playery) ) {
					// player cannot see x,y but x,y sees the player
					nbErrToPlayer++;
				}
			}
		}
	}
	nbErrFromPlayer/=NB_SYMMETRY_TESTS;
	nbErrToPlayer/=NB_SYMMETRY_TESTS;
}

void FovSymmetry::getRenderSize(int *w, int *h) {
	*w=40;		
	*h=1;		
}

void FovSymmetry::render(TCODConsole *con,int x, int y) {
	float errorRate=(float)(nbErrFromPlayer+nbErrToPlayer)/nbFovCells;
	con->print(x,y,"%.2g%% (%d+%d/%d)",errorRate*100,nbErrFromPlayer,nbErrToPlayer,nbFovCells);
}
