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

class FovTest {
public :
	int algoNum;
	int testNum;
	static FovTest* getTest(int algoNum,int testNum);
	virtual void initialise() = 0;
	void run();
	TCODMap *map;
	virtual void render(TCODConsole *con,int x, int y); 	
	float time; // length of the execution of run function in seconds
protected :
	float t0;
	int playerx,playery;
	inline void startCounter() {t0=TCODSystem::getElapsedSeconds();}	
	inline void stopCounter() {time=TCODSystem::getElapsedSeconds()-t0;}
	virtual void execute();	
};

class FovPillar1 : public FovTest {
public :
	void initialise();
};

class FovPillar2 : public FovPillar1 {
	void initialise();
};

class FovCorner1 : public FovTest {
public :
	void initialise();
};

class FovCorner2 : public FovCorner1 {
public :
//	void initialise();
};

