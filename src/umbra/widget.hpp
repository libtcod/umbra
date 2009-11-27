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

class UmbraRect {
	public:
        int x,y,w,h;
        bool mouseHover;
        bool mouseDown;
        UmbraRect (void): x(0),y(0),w(0),h(0),mouseHover(false) {}
        UmbraRect (int x, int y, int w, int h): x(x),y(y),w(w),h(h),mouseHover(false) {}
        inline void setPos (int x, int y) { this->x=x; this->y=y; }
        inline void setSize (int w, int h) { this->w=w;this->h=h; }
        inline void set (int x, int y, int w, int h) { setPos(x,y); setSize(w,h); }
        inline bool isInside (int px, int py) { return px >= x && px < x+w && py >= y && py < y+h; }
};

class UmbraPoint {
    public:
        int x, y;
        bool mouseHover;
        bool mouseDown;
        UmbraPoint (void): x(0),y(0),mouseHover(false) {}
        UmbraPoint (int x, int y): x(x),y(y),mouseHover(false) {}
        inline void set (int x, int y) { this->x=x; this->y=y; }
        inline bool is (int px, int py) { return px == x && py == y; }
};


class UmbraWidget : public UmbraModule {
    friend class UmbraCheckbox;
    friend class UmbraButton;
    public :
        UmbraWidget (void);
        void mouse (TCOD_mouse_t &ms);
    protected :
        void setDragZone (int x, int y, int w, int h);
        UmbraRect rect; // part of the screen where the widget is
        UmbraRect dragZone; // part of the widget we can click to drag it
        UmbraPoint minimiseButton; //minimise button coordinates
        UmbraPoint closeButton; //close button coordinates
        int mousex,mousey;
        int dragx,dragy;
        bool canDrag, isDragging;
};

