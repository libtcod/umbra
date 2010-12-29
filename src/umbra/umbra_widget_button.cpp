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

#include "umbra.hpp"

UmbraButton::UmbraButton () {
	parent = NULL;
	rect.set(0,0,0,0);
	tag = "";
	visible = true;
}

UmbraButton::UmbraButton (UmbraWidget * parent, int x, int y, int w, int h, const char * tag) {
	this->parent = parent;
	rect.set(x, y, w, h);
	this->tag = tag;
	visible = true;
}

UmbraButton::UmbraButton (UmbraWidget * parent, int x, int y, int w, int h, std::string tag) {
	this->parent = parent;
	rect.set(x, y, w, h);
	this->tag = tag;
	visible = true;
}

void UmbraButton::set (UmbraWidget * parent, int x, int y, int w, int h, const char * tag) {
	this->parent = parent;
	rect.set(x, y, w, h);
	this->tag = tag;
	visible = true;
}

void UmbraButton::render (TCODConsole * con) {
	if (!visible) return;
	TCODColor col = con->getDefaultForeground();
	UmbraStyleSheetSet* s;
	if (rect.mouseHover) {
		if (rect.mouseDown) s = &style.active;
		else s = &style.hover;
	} else s = &style.normal;
	
	con->setDefaultForeground(s->borderColour());
	con->setDefaultBackground(s->backgroundColour());
	con->printFrame(rect.x,rect.y,rect.w,rect.h,true,TCOD_BKGND_SET,NULL);
	con->setDefaultForeground(s->colour());
	if (!tag.empty())
		con->printRectEx(rect.x+(rect.w/2),rect.y+(rect.h/2),rect.w-2,rect.h-2,TCOD_BKGND_NONE,TCOD_CENTER,tag.c_str());
	con->setDefaultForeground(col);
}
