/*
* Umbra
* Copyright (c) 2009 Dominik Marczuk
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The name of Dominik Marczuk may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "umbra.hpp"

UmbraModSpeed::UmbraModSpeed (void) : isMinimised(false) {
    speed = new TCODConsole(30,6);
    rect.set((UmbraConfig::rootWidth/2)-15,(UmbraConfig::rootHeight/2)-3,30,6);
	canDrag = true;
	// the title bar is drag-sensible
	dragZone.set(0,0,27,1);
    //the buttons:
    minimiseButton.set(27,0);
    closeButton.set(28,0);
	priority=0; // higher prio for internal modules
}

void UmbraModSpeed::mouse (TCOD_mouse_t &ms) {
	UmbraWidget::mouse(ms);
	if (ms.lbutton_pressed) {
		ms.lbutton_pressed=false; // erase event
		//minimise button is pressed
		if (minimiseButton.is(mousex,mousey)) {
            isMinimised = !isMinimised;
            if (isMinimised) {
                rect.setSize(9,1);
                minimiseButton.set(7,0);
                closeButton.set(8,0);
                dragZone.w = 7;
            } else {
                rect.setSize(30,6);
                minimiseButton.set(27,0);
                closeButton.set(28,0);
                dragZone.w = 27;
                // when the widget maximizes, it might cross the screen borders
                rect.x=MIN(UmbraConfig::rootWidth-rect.w,rect.x);
                rect.y=MIN(UmbraConfig::rootHeight-rect.h,rect.y);
            }
		}
		//close button is pressed
		else if (closeButton.is(mousex,mousey)) {
		    setActive(false);
		}
	}
}

bool UmbraModSpeed::update (void) {
    return true;
}

void UmbraModSpeed::render (void) {
    speed->setBackgroundColor(TCODColor::black);
    speed->setForegroundColor(TCODColor::white);
	if ( isMinimised ) {
		speed->printLeft(0,0,TCOD_BKGND_SET,"%4dfps ",TCODSystem::getFps());
		TCODConsole::blit(speed,0,0,8,1,TCODConsole::root,rect.x,rect.y,1.0f,0.5f);
	} else {
		speed->printFrame(0,0,30,6,true,"Speed-o-meter");
		speed->printCenter(15,2,TCOD_BKGND_NONE,"last frame: %3d ms",(int)(TCODSystem::getLastFrameLength()*1000));
		speed->printCenter(15,3,TCOD_BKGND_NONE,"frames per second: %3d",TCODSystem::getFps());
	}
	speed->setBackgroundColor(TCODColor::black);
	// draw minimize button
	if (minimiseButton.mouseHover) speed->setForegroundColor(TCODColor::white); //button is active
	else speed->setForegroundColor(TCODColor::lightGrey); //button is not active
	speed->putChar(minimiseButton.x,minimiseButton.y, isMinimised ? '+' : '-', TCOD_BKGND_SET);
	//draw close button
	if (closeButton.mouseHover) speed->setForegroundColor(TCODColor::red); //button is active
	else speed->setForegroundColor(TCODColor::lightGrey); //button is not active
	speed->putChar(closeButton.x,closeButton.y, 'X', TCOD_BKGND_SET);
	//blit the console
	TCODConsole::blit(speed,0,0,rect.w,rect.h,TCODConsole::root,rect.x,rect.y,1.0f,0.5f);
}

void UmbraModSpeed::activate (void) {
    fps = TCODSystem::getFps();
    TCODSystem::setFps(0);
}

void UmbraModSpeed::deactivate (void) {
    TCODSystem::setFps(fps);
}
