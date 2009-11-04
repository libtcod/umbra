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

UmbraWidget::UmbraWidget( void ) : mousex(-1),mousey(-1),
	canDrag(false),isDragging(false) {
}

void UmbraWidget::mouse(TCOD_mouse_t &ms) {
	if ( !isDragging && !rect.isInside(ms.cx,ms.cy) ) return;

	mousex=ms.cx-rect.x;
	mousey=ms.cy-rect.y;
	if ( ms.lbutton && canDrag && ! isDragging && dragZone.isInside(mousex,mousey) ) {
		isDragging = true;
		dragx = mousex;
		dragy = mousey; // position where the widget is drag
		ms.lbutton=false; // erase event
	} else if ( isDragging && ! ms.lbutton ) {
		isDragging = false;
		ms.lbutton_pressed=false; // erase event
	} else if ( isDragging ) {
		ms.lbutton=false; // erase event
		rect.x = CLAMP(0,UmbraConfig::rootWidth-rect.w, ms.cx-dragx);
		rect.y = CLAMP(0,UmbraConfig::rootHeight-rect.h,ms.cy-dragy);
		mousex=dragx;mousey=dragy;
		ms.cx=ms.cy=ms.x=ms.y=ms.dx=ms.dy=ms.dcx=ms.dcy=0; // erase mouse move event
	}
}

