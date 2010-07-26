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

#include "notification.hpp"
#include "gameview.hpp"

void QuitButton::onMouseDown () {
    UmbraEngine::getInstance()->deactivateAll();
}

Notification::Notification () {
    notification = new TCODConsole(24,12);
    rect.set(UmbraEngine::getInstance()->getRootWidth()/2-12,UmbraEngine::getInstance()->getRootHeight()/2-6,24,12);
    //setDragZone(0,0,24,1);
    button.set(this,10,7,4,3,"OK");
}

void Notification::mouse (TCOD_mouse_t &ms) {
    UmbraWidget::mouse(ms);
    button.mouse(ms);
}

void Notification::render () {
    notification->setForegroundColor(TCODColor::white);
    notification->setBackgroundColor(TCODColor::darkerAzure);
    notification->printFrame(0,0,24,12,true,TCOD_BKGND_SET,NULL);
    notification->printRectEx(12,2,24,6,TCOD_BKGND_NONE,TCOD_CENTER,text.c_str());
    if (dragZone.mouseHover || isDragging) {
        notification->setBackgroundColor(TCODColor::lightRed);
        notification->rect(5,0,14,1,false,TCOD_BKGND_SET);
    }
    if (button.area.mouseHover) notification->setForegroundColor(TCODColor::lightGreen);
    else notification->setForegroundColor(TCODColor::white);
    button.render(notification);
    TCODConsole::blit(notification,0,0,rect.w,rect.h,TCODConsole::root,rect.x,rect.y,1.0f,0.5f);
}

void Notification::activate() {
	if (((GameView*)(UmbraEngine::getInstance()->getModule(MOD_GAME_VIEW)))->alienCount == 0)
		text = "Congratulations!\nYou won!";
	else
		text = "Oops, you lose!\nTry again!";
}
