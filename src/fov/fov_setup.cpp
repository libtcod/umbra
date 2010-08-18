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

const char *fovnames[NB_FOV_ALGORITHMS] = {
	"Basic raycasting",
	"Diamond raycasting",
	"Recursive shadowcasting",
	"Permissive-0",
	"Permissive-1",
	"Permissive-2",
	"Permissive-3",
	"Permissive-4",
	"Permissive-5",
	"Permissive-6",
	"Permissive-7",
	"Permissive-8",
	"MRPAS",
};
const char *testnames[FOV_NB_TESTS] = {
	"Pillar 1",
	"Pillar 2",
	"Corner peeking 1",
	"Corner peeking 2",
	"Diagonal walls",
	"Symmetry",
	"Speed on empty map",
	"Speed on full map",
	"Speed on outdoor map",
};

FovSetup::FovSetup () {
}

bool FovSetup::update () {
	if (running) {
		FovTest *nextTest=testsToRun.pop();
		nextTest->initialise();
		nextTest->run();		
		finishedTests.push(nextTest);	
		if ( testsToRun.isEmpty() ) running=false;	
	}
    return true;
}

void FovSetup::initialise() {

	for (int i=0; i < NB_FOV_ALGORITHMS; i++) {
		algoCkb[i].set(this,2,2+i*2,strlen(fovnames[i])+2,1,fovnames[i]);
	}
	for (int i=0; i < FOV_NB_TESTS; i++) {
		testCkb[i].set(this,40,2+i*2,strlen(testnames[i])+2,1,testnames[i]);
	}
	go.set(this,39,23,10,3,"GO");
	running=false;
}

void FovSetup::render () {
	if (! running ) {
		// render the menu
		TCODConsole::root->print(2,0,"Algorithms to test");
		for (int i=0; i < NB_FOV_ALGORITHMS; i++) {
			algoCkb[i].render(TCODConsole::root);
		}
		TCODConsole::root->print(40,0,"Tests to run");
		for (int i=0; i < FOV_NB_TESTS; i++) {
			testCkb[i].render(TCODConsole::root);
		}
		go.render(TCODConsole::root);
		if ( finishedTests.size() == 1 ) {
			// render the last executed test if there was only 1
			finishedTests.peek()->render(TCODConsole::root,0,30);
		}
	} else {
		// render remaining tests counter
		TCODConsole::root->print(30,35,"Remaining tests : %d / %d", testsToRun.size(), testsToRun.size()+finishedTests.size());
	}
}

void FovSetup::mouse (TCOD_mouse_t &ms) {
	if (! running) {
		// count the number of algos and tests selected
		int nbTests=0;
		int nbAlgos = 0;
		for (int i=0; i < NB_FOV_ALGORITHMS; i++) {
			algoCkb[i].mouse(ms);
			if ( algoCkb[i].checked ) nbAlgos++;
		} 
		for (int i=0; i < FOV_NB_TESTS; i++) {
			testCkb[i].mouse(ms);
			if ( testCkb[i].checked ) nbTests++;
		}
		go.mouse(ms);
		nbTests = nbTests * nbAlgos;
		if (nbTests > 0 ) {
			// if at least 1 algo and 1 test selected, click go to launch
			running = go.area.mouseDown;
			if (running) {
				// launching...
				testsToRun.clear();
				finishedTests.clear();
				// create the list of tests to run
				for (int i=0; i < NB_FOV_ALGORITHMS; i++) {
					if ( algoCkb[i].checked ) {
						for (int j=0; j < FOV_NB_TESTS; j++) {
							if ( testCkb[j].checked ) {
								FovTest *test=FovTest::getTest(i,j);
								if ( test != NULL ) testsToRun.push(test);
							}
						}
					}
				}
			}
		}
	}
}


