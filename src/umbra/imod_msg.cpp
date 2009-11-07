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

#include "umbra.hpp"

UmbraModMessage::UmbraModMessage (void) {
    msg = new TCODConsole(30,6);
    closeButton.set(28,0);
    duration = 5000;
    msgString = "";
    rect.set(UmbraConfig::rootWidth-32,UmbraConfig::rootHeight-8,30,6);
}

void UmbraModMessage::activate (void) {
    startTime = TCODSystem::getElapsedMilli();
    msgString = UmbraError::getLastMessage();
    msg->setBackgroundColor(TCODColor::blue);
    msg->clear();
}

bool UmbraModMessage::update (void) {
    if (TCODSystem::getElapsedMilli() - startTime >= duration) return false;
    else return true;
}

void UmbraModMessage::render (void) {
    msg->setForegroundColor(TCODColor::white);
    msg->printCenterRect(15,2,28,3,TCOD_BKGND_NONE,UmbraError::getLastMessage());
    if (closeButton.mouseHover)
        msg->setForegroundColor(TCODColor::red);
    msg->putChar(closeButton.x,closeButton.y,'X',TCOD_BKGND_NONE);
    TCODConsole::blit(msg,0,0,rect.w,rect.h,TCODConsole::root,rect.x,rect.y,1.0f,0.5f);
}