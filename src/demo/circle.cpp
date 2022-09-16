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
#include "circle.hpp"

Circle::Circle() {
	isGreen = false;
	red = new TCODImage("data/img/red.png");
	green = new TCODImage("data/img/green.png");
}

void Circle::onInitialise() {
	circle.set(getEngine()->getRootWidth()/2,getEngine()->getRootHeight()/2,7);
}

void Circle::mouse (TCOD_mouse_t &ms) {
	isGreen = circle.contains(ms.cx,ms.cy);
	if (isGreen && ms.lbutton) setActive(false);
}

void Circle::render() {
	if (isGreen) green->blit2x(TCODConsole::root,circle.x-circle.r,circle.y-circle.r);
	else red->blit2x(TCODConsole::root,circle.x-circle.r,circle.y-circle.r);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->printEx(circle.x,circle.y+8,TCOD_BKGND_NONE,TCOD_CENTER,"Do you take the green or the red pill?\nClick the big button to carry on...");
}
