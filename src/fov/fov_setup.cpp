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

const char *fovShortNames[NB_FOV_ALGORITHMS] = {
	"BASIC",
	"DIAMOND",
	"SHADOW",
	"PERM-0",
	"PERM-1",
	"PERM-2",
	"PERM-3",
	"PERM-4",
	"PERM-5",
	"PERM-6",
	"PERM-7",
	"PERM-8",
	"MRPAS",
};

const char *testnames[FOV_NB_TESTS] = {
	"Pillar, orthogonal",
	"Pillar, away",
	"Pillar, diagonal",
	"Corner peeking: T-junction",
	"Corner peeking: corridor",
	"Diagonal walls",
	"Symmetry, outdoor map",
	"Symmetry, indoor map",
	"Speed, empty map",
	"Speed, full map",
	"Speed, outdoor map",
	"Speed, indoor map",
};

const char *testShortNames[FOV_NB_TESTS] = {
	"PILLAR-ORTH",
	"PILLAR-AWAY",
	"PILLAR-DIAG",
	"CORNER-T-J",
	"CORNER-CORR",
	"DIAGONAL-WL",
	"SYMM-OUT",
	"SYMM-IN",
	"SPEED-EMPTY",
	"SPEED-FULL",
	"SPEED-OUT",
	"SPEED-IN",
};

// background thread executing the tests
int testThread(void *data) {
	FovSetup *setup=(FovSetup *)data;
    // run the tests
    while ( !setup->testsToRun.isEmpty() ) {
		setup->currentTest = setup->testsToRun.pop();
		// restore the rng so that all tests are done in the same conditions
		FovTest::rng.restore(setup->rngBackup);
		setup->currentTest->initialise();
		setup->currentTest->run();
		setup->finishedTests.push(setup->currentTest);
	}
    // all tests are finished
    setup->createResultTabs();
    return 0;
}

FovSetup::FovSetup () {
}

void FovSetup::createResultTabs() {
	// create the result tabs
	int x=0,y=17;
	for (int j=0; j <FOV_NB_TESTS; j++) {
		if ( testCkb[j].checked ) {
			int len=strlen(testShortNames[j])+2;
			if ( x+len >= engine.getRootWidth() ) {
				x=0;y+=3;
			}
			tabs.push(new UmbraButton(this,x,y,len,3,testShortNames[j]));
			x += len;
		}
	}
	running=false;
}

bool FovSetup::update () {
    return true;
}

void FovSetup::initialise() {
    int y=2;
	for (int i=0; i < NB_FOV_ALGORITHMS; i++) {
		algoCkb[i].set(this,2,y,strlen(fovnames[i])+2,1,fovnames[i]);
		y++;
	}
	y=2;
	for (int i=0; i < FOV_NB_TESTS; i++) {
		if ( i == FOV_TEST_SPEED_EMPTY ) y++;
		testCkb[i].set(this,40,y,strlen(testnames[i])+2,1,testnames[i]);
		y++;
	}
	go.set(this,70,0,10,3,"GO");
	running=false;
	// save the test rng to be able to restore it
	rngBackup = FovTest::rng.save();
	bgThread=NULL;
	currentTest=NULL;
}

void FovSetup::render () {
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
    // render the tabs (if any)
    for ( UmbraButton **it=tabs.begin(); it != tabs.end(); it++) {
        (*it)->render(TCODConsole::root);
    }
	if (! running ) {
		if ( finishedTests.size() > 0 ) {
			// render the results for the last executed tests for the current tab
			int tx=0,ty=24, th=0,w,h;
			for (FovTest **it=finishedTests.begin(); it != finishedTests.end(); it++) {
				// skip tests not belonging to current tab
			    if ( (*it)->testNum != curTestResult ) continue;
			    // find a suitable position to render the test result
                (*it)->getRenderSize(&w,&h);
                if ( tx + w >= TCODConsole::root->getWidth() ) {
                    tx=0;
                    ty+=th+1;
                    th=0;
                }
                if (h>th) th=h; // th is the max height of the current line of results
                if ( h > 1 ) {
	                // display the algo short name on top of the test result
	                TCODConsole::root->printEx(tx+w/2,ty-1,TCOD_BKGND_NONE,TCOD_CENTER,
	                                           "%s",fovShortNames[(*it)->algoNum]);
	            } else {
	            	// single line result : display at the right of the algo name
	                TCODConsole::root->print(tx,ty,"%s:",fovShortNames[(*it)->algoNum]);
	                tx+=strlen(fovShortNames[(*it)->algoNum])+2;
				}
                // display the result
                (*it)->render(TCODConsole::root,tx,ty);
                tx+=w+1;
			}
		}
	} else {
		// render remaining tests counter
		TCODConsole::root->print(30,35,"Running test %d / %d...", finishedTests.size()+1, testsToRun.size()+finishedTests.size()+1);
		TCODConsole::root->setDefaultBackground(TCODColor::darkerGrey);
		TCODConsole::root->rect(20,37,40,1,false,TCOD_BKGND_SET);
		TCODConsole::root->setDefaultBackground(TCODColor::darkRed);
		int progressLength=(int)(40*currentTest->progress);
		if ( progressLength > 0 ) TCODConsole::root->rect(20,37,progressLength,1,false,TCOD_BKGND_SET);
	}
}

void FovSetup::mouse (TCOD_mouse_t &ms) {
	if (! running) {
	    // update the UI
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
		// update the tabs
		int tabnum=0;
		for ( UmbraButton **it=tabs.begin(); it != tabs.end(); it++, tabnum++) {
            (*it)->mouse(ms);
            if ( (*it)->area.mouseDown ) {
                // tab <tabnum> pressed. retrieve the corresponding test
                int testTab=0;
                for (int i=0; i < FOV_NB_TESTS; i++) {
                    if ( testCkb[i].checked ) {
                        if ( testTab == tabnum) {
                            // tabnum correspond to test i
                            curTestResult=i;
                            break;
                        } else testTab++;
                    }
                }
            }
        }
		nbTests = nbTests * nbAlgos;
		if (nbTests > 0 ) {
			// if at least 1 algo and 1 test selected, click go to launch
			running = go.area.mouseDown;
			if (running) {
				// initialise the test lists...
				testsToRun.clear();
				finishedTests.clear();
				tabs.clearAndDelete();
				if ( bgThread != NULL ) TCODSystem::deleteThread(bgThread);
				// create the list of tests to run
                for (int j=FOV_NB_TESTS-1; j >= 0; j--) {
                    if ( testCkb[j].checked ) {
                    	curTestResult=j;
                        for (int i=NB_FOV_ALGORITHMS-1; i >= 0; i--) {
                            if ( algoCkb[i].checked ) {
								FovTest *test=FovTest::getTest(i,j);
								if ( test != NULL ) {
									currentTest=test;
									testsToRun.push(test);
								}
							}
						}
					}
				}
				// launch the thread
				bgThread = TCODSystem::newThread(testThread,this);
			}
		}
	}
}


