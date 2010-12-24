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

#include "umbra_stylesheet.hpp"

class UmbraPoint;
class UmbraRect;

class UmbraWidget: public UmbraModule {
	friend class UmbraCheckbox;
	friend class UmbraButton;
public:
	UmbraWidget ();
	/**
	 * Custom, widget-specific code interpreting the mouse input.
	 * @param ms reference to the mouse object
	 */
	void mouse (TCOD_mouse_t &ms);

	/**
	 * Signal launched when the mouse cursor enters the widget.
	 */
	Signal2 <UmbraWidget*,UmbraEvent> onMouseEnter;
	/**
	 * Signal launched when the mouse cursor leaves the widget.
	 */
	Signal2 <UmbraWidget*,UmbraEvent> onMouseLeave;
	/**
	 * Signal lauched when the mouse cursor moves inside the widget.
	 */
	Signal2 <UmbraWidget*,UmbraEvent> onMouseMove;
	/**
	 * Signal launched when the mouse button is pressed when hovering over the widget. Corresponds to JavaScript's <code>onmousedown</code> event.
	 */
	Signal2 <UmbraWidget*,UmbraEvent> onMousePress;
	/**
	 * Signal launched when the mouse button is released when hovering over the widget. Corresponds to JavaScript's <code>onmouseup</code> event.
	 */
	Signal2 <UmbraWidget*,UmbraEvent> onMouseRelease;
	/**
	 * Signal launched when the mouse button is clicked when hovering over the widget. Corresponds to JavaScript's <code>onclick</code> event.
	 * <strong>TODO:</strong> With the current implementation, this signal behaves identically to <code>onMouseRelease</code>.
	 */
	Signal2 <UmbraWidget*,UmbraEvent> onMouseClick;

	/**
	 * Part of the screen where the widget is
	 */
	UmbraRect rect;
	/**
	 * The style sheet containing information about the widget's appearance
	 */
	UmbraStyleSheet style;
protected:
	/**
	 * Pointer to the containing (parent) widget
	 */
	UmbraWidget * parent; //reference to the widget that contains the object
	/**
	 * The drag zone: the are within the widget that can be clicked in order to drag it
	 */
	UmbraRect dragZone; // part of the widget we can click to drag it
	/**
	 * Coordinates of the minimise button
	 */
	UmbraPoint minimiseButton; //minimise button coordinates
	/**
	 * Coordinates of the close button
	 */
	UmbraPoint closeButton; //close button coordinates
	int mousex;
	int mousey;
	int dragx;
	int dragy;
	bool canDrag;
	bool isDragging;
	/**
	 * Sets the widget's active zone reacting to dragging.
	 * @param x the drag zone's top left corner's <i>x</i> coordinate
	 * @param y the drag zone's top left corner's <i>y</i> coordinate
	 * @param w the drag zone's width
	 * @param h the drag zone's height
	 */
	void setDragZone (int x, int y, int w, int h);
	/**
	 * Custom code that is executed when the user release the mouse button
	 * after dragging the widget		  
	 */		 		
	virtual void onDragEnd() {}	
};
