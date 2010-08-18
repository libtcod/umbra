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

enum {
	FOV_TEST_PILLAR1,
	FOV_TEST_PILLAR2,
	FOV_TEST_PILLAR3,
	FOV_TEST_CORNER1,
	FOV_TEST_CORNER2,
	FOV_TEST_DIAGONAL,
	FOV_TEST_SYMMETRY,
	FOV_TEST_SPEED_EMPTY,
	FOV_TEST_SPEED_FULL,
	FOV_TEST_SPEED_OUTDOOR,
	// todo add speed indoor
	FOV_NB_TESTS
};

extern const char *fovnames[NB_FOV_ALGORITHMS];
extern const char *testnames[FOV_NB_TESTS];

class FovSetup: public UmbraWidget {
    public:
        FovSetup();
        bool update ();
        void render ();
        void mouse (TCOD_mouse_t &ms);
        void initialise();
    private:
    	UmbraCheckbox algoCkb[NB_FOV_ALGORITHMS];
    	UmbraCheckbox testCkb[FOV_NB_TESTS];
    	UmbraButton go;
    	bool running; // we are currently running tests
    	TCODList<FovTest *>testsToRun;
    	TCODList<FovTest *>finishedTests;
    	TCODList<UmbraButton *>tabs;
    	int curTestResult;
};


