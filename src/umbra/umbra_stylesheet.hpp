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

#ifndef UMBRA_STYLESHEET_HPP
#define	UMBRA_STYLESHEET_HPP

enum UmbraStyleSheetSpecificity {
	UMBRA_SPECIFICITY_DEFAULT,
	UMBRA_SPECIFICITY_TAG,
	UMBRA_SPECIFICITY_CLASS,
	UMBRA_SPECIFICITY_ID,
	UMBRA_SPECIFICITY_MANUAL
};

/**
 * A template of a stylesheet property, including the property's value and the level at which it has been set.
 */
template <class T1> class UmbraStyleSheetProperty {
private:
	/**
	 * The property's value.
	 */
	T1 val;
	/**
	 * The level at which the property has been set (tag, class, ID or manual). Used to determine the precedence.
	 */
	UmbraStyleSheetSpecificity specificity;
public:
	/**
	 * Fetches the property's value.
	 * @return the property's value
	 */
	inline T1 value() { return val; }
	inline UmbraStyleSheetProperty& operator = (const T1& x) { val = x; specificity = UMBRA_SPECIFICITY_MANUAL; return *this; }
	inline T1& operator () () { return val; }
private:
	/**
	 * Sets the property's value and level.
	 * @param x the property's value
	 * @param l the property's level
	 */
	inline void set (const T1& x, UmbraStyleSheetSpecificity s) { val = x; specificity = s; }
};

/**
 * The class that holds the information about a styles set. Used internally by the <code>UmbraStyleSheet</code> class.
 */
class UmbraStyleSheetSet {
public:
	/**
	 * Text foreground colour.
	 */
	UmbraStyleSheetProperty <TCODColor> colour;
	UmbraStyleSheetProperty <TCODColor> backgroundColour;
	UmbraStyleSheetProperty <TCODColor> borderColour;
};

/**
 * The style sheet class. It stores the information about a widget's appearance.
 */
class UmbraStyleSheet {
private:

	static TCODParser parser;
public: // style sheets
	/**
	 * Default style sheet for the widget.
	 */
	UmbraStyleSheetSet normal;
	/**
	 * Style sheet that overrides the default appearance when the mouse cursor is hovering over the widget.
	 */
	UmbraStyleSheetSet hover;
	/**
	 * Style sheet that overrides the default appearance when the mouse cursor is pressed while hovering over the widget.
	 */
	UmbraStyleSheetSet active;
public: // setters
	/**
	 * Sets the style sheet's <code>colour</code> property.
     * @param val the property's value
     * @param pseudoClass can be either <code>"normal"</code>, <code>"hover"</code>, <code>"active"</code> or <code>NULL</code>.<br />Used to specify which pseudo class property is to be changed. If the parametre is ommitted, all pseudo classes will receive the colour.
     */
	void colour (TCODColor val, const char * pseudoClass = NULL);
	/**
	 * Sets the style sheet's <code>backgroundColour</code> property.
     * @param val the property's value
     * @param pseudoClass can be either <code>"normal"</code>, <code>"hover"</code>, <code>"active"</code> or <code>NULL</code>.<br />Used to specify which pseudo class property is to be changed. If the parametre is ommitted, all pseudo classes will receive the colour. 
     */
	void backgroundColour (TCODColor val, const char * pseudoClass = NULL);
	/**
	 * Sets the style sheet's <code>borderColour</code> property.
     * @param val the property's value
     * @param pseudoClass can be either <code>"normal"</code>, <code>"hover"</code>, <code>"active"</code> or <code>NULL</code>.<br />Used to specify which pseudo class property is to be changed. If the parametre is ommitted, all pseudo classes will receive the colour. 
     */
	void borderColour (TCODColor val, const char * pseudoClass = NULL);
public: // ctor
	/**
	 * The constructor for the style sheet class. Fills all styles with default values.
     */
	UmbraStyleSheet();
};

#endif	/* UMBRA_STYLESHEET_HPP */

