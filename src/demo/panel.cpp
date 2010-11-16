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

void Panel::onQuit(UmbraWidget *w,UmbraEvent ev) {
	engine.deactivateAll();
}

Panel::Panel () {
	width = 24;
	height = 48;
	posx = 0;
	posy = (getEngine()->getRootHeight() - height) / 2;
	rect.set(posx,posy,width,height);
	panel = new TCODConsole(width,height);
	lastHover = 0;
	delay = 3000;
	bQuit.set(this,2,2,20,3,"Quit");
	bQuit.onMouseClick.Connect(this,&Panel::onQuit);
}

void Panel::render () {
	panel->setDefaultBackground(TCODColor::darkerGrey);
	panel->setDefaultForeground(TCODColor::silver);
	panel->printFrame(0,0,rect.w,rect.h,true,TCOD_BKGND_SET,NULL);
	if (bQuit.rect.mouseHover) panel->setDefaultForeground(TCODColor::white);
	bQuit.render(panel);
	TCODConsole::blit(panel,0,0,rect.w,rect.h,TCODConsole::root,posx,posy,1.0f,0.5f);
}

bool Panel::update () {
	uint32 time = TCODSystem::getElapsedMilli();
	if (rect.mouseHover) {
		lastHover = time;
		posx += 3;
		posx = MIN(posx,0);
		rect.set(posx,posy,width,height);
	}
	else if (time >= lastHover + delay) {
		posx -= 2;
		posx = MAX(posx,(-width)+1);
		rect.set(posx,posy,width,height);
	}
	return getActive();
}

void Panel::mouse (TCOD_mouse_t &ms) {
	UmbraWidget::mouse(ms);
	bQuit.mouse(ms);
	return;
}
