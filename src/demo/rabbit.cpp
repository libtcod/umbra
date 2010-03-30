/*
* Umbra
* Copyright (c) 2009 Dominik Marczuk, Jice
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The names of Dominik Marczuk or Jice may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK & JICE ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK OR JICE BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "main.hpp"

void RabbitButton::onMouseDown () {
    parent->setActive(false);
    engine.getModule(MOD_MATRIX)->setActive(false);
}

RabbitWidget::RabbitWidget () {
    rabbit = new TCODConsole(24,12);
    rect.set(engine.getRootWidth()/2-12,engine.getRootHeight()/2-6,24,12);
    setDragZone(0,0,24,1);
    button.set(this,10,7,4,3,"OK");
}

void RabbitWidget::mouse (TCOD_mouse_t &ms) {
    UmbraWidget::mouse(ms);
    button.mouse(ms);
}

void RabbitWidget::render () {
    rabbit->setForegroundColor(TCODColor::white);
    rabbit->setBackgroundColor(TCODColor::black);
    rabbit->printFrame(0,0,24,12,true,TCOD_BKGND_SET,"Wake up, Neo");
    rabbit->printCenterRect(12,2,24,6,TCOD_BKGND_NONE,"The Matrix has you. Press OK to follow the white rabbit.");
    if (dragZone.mouseHover || isDragging) {
        rabbit->setBackgroundColor(TCODColor::lightRed);
        rabbit->rect(5,0,14,1,false,TCOD_BKGND_SET);
    }
    if (button.area.mouseHover) rabbit->setForegroundColor(TCODColor::lightGreen);
    else rabbit->setForegroundColor(TCODColor::white);
    button.render(rabbit);
    TCODConsole::blit(rabbit,0,0,rect.w,rect.h,TCODConsole::root,rect.x,rect.y,1.0f,0.5f);
}
