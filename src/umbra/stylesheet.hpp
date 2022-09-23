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
#define UMBRA_STYLESHEET_HPP
#include <libtcod/libtcod.hpp>

/**
 * Specificity levels. Used to determine whether an encountered value can override the one that has been already set.
 */
enum UmbraStyleSheetSpecificity {
  /**
   * Default specificity. Used for default values. Can be overridden by anything.
   */
  UMBRA_SPECIFICITY_DEFAULT,
  /**
   * Tag level. This specificity is used when setting a property value for all widgets of a given type, e.g. for all
   * pushbuttons.
   */
  UMBRA_SPECIFICITY_TAG,
  /**
   * Class level. Overrides tag level. Used for setting a common property value for an arbitrary class of widgets (for
   * instance, main menu buttons can belong to a class so that their styling is different from all other pushbuttons).
   */
  UMBRA_SPECIFICITY_CLASS,
  /**
   * ID level. Used for styling individual widgets. Targets only the widget with a specifin name and overrides both tag
   * and class specificity levels.
   */
  UMBRA_SPECIFICITY_ID,
  /**
   * Used when setting a property's value manually within the code (for instance, for dynamic changes). The external
   * style sheet cannot use this specificity. It overrides everything.
   */
  UMBRA_SPECIFICITY_MANUAL
};

class UmbraStyleSheetSet;  // forward declaration

/**
 * A template of a stylesheet property, including the property's value and the level at which it has been set.
 */
template <class T>
class UmbraStyleSheetProperty {
  friend class UmbraStyleSheetSet;

 private:
  /**
   * The property's value.
   */
  T val;
  /**
   * The level at which the property has been set (tag, class, ID or manual). Used to determine the precedence.
   */
  UmbraStyleSheetSpecificity specificity;

 public:
  /**
   * Fetches the property's value. Equivalent to the overloaded <code>()</code> operator.
   * @return the property's value
   */
  inline T value() { return val; }
  /**
   * Overloaded assignment operator. Assigns a value to the property.
   * @param x the value to be assigned to the property
   * @return the property object reference
   */
  inline UmbraStyleSheetProperty& operator=(const T& x) {
    val = x;
    specificity = UMBRA_SPECIFICITY_MANUAL;
    return *this;
  }
  /**
   * Overloaded function call operator. Assigns a value to the property.
   * @param x the value to be assigned to the property
   * @return the property object reference
   */
  inline UmbraStyleSheetProperty& operator()(const T& x) {
    val = x;
    specificity = UMBRA_SPECIFICITY_MANUAL;
    return *this;
  }
  /**
   * Overloaded function call operator. Fetches the property's value. Equivalent to the <code>value()</code> method.
   * @return the property's value
   */
  inline T& operator()() { return val; }

 private:
  /**
   * Sets the property's value and specificity. If
   * @param x the property's value
   * @param l the property's specificity
   * @return the property object reference
   */
  inline UmbraStyleSheetProperty& set(const T& x, UmbraStyleSheetSpecificity s = UMBRA_SPECIFICITY_DEFAULT) {
    if (s >= specificity || s == UMBRA_SPECIFICITY_DEFAULT) {
      val = x;
      specificity = s;
    }
    return *this;
  }
};

/**
 * The class that holds the information about a styles set. Used internally by the <code>UmbraStyleSheet</code> class.
 */
class UmbraStyleSheetSet {
 public:
  /**
   * The style sheet set constructor. Assigns default values to all properties.
   */
  UmbraStyleSheetSet();
  /**
   * Text foreground colour.
   */
  UmbraStyleSheetProperty<TCODColor> colour;
  /**
   * Widget's background colour.
   */
  UmbraStyleSheetProperty<TCODColor> backgroundColour;
  /**
   * Widget's border colour.
   */
  UmbraStyleSheetProperty<TCODColor> borderColour;
};

/**
 * The style sheet class. It stores the information about a widget's appearance.
 */
class UmbraStyleSheet {
 private:
  static TCODParser parser;

 public:  // style sheets
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

 public:  // setters
  /**
   * Sets the style sheet's <code>colour</code> property.
   * @param val the property's value
   * @return reference to the style sheet the method is called on. It can be used for chaining.
   */
  UmbraStyleSheet& colour(TCODColor val);
  /**
   * Sets the style sheet's <code>backgroundColour</code> property.
   * @param val the property's value
   * @return reference to the style sheet the method is called on. It can be used for chaining.
   */
  UmbraStyleSheet& backgroundColour(TCODColor val);
  /**
   * Sets the style sheet's <code>borderColour</code> property.
   * @param val the property's value
   * @return reference to the style sheet the method is called on. It can be used for chaining.
   */
  UmbraStyleSheet& borderColour(TCODColor val);

 public:  // ctor
  /**
   * The constructor for the style sheet class. Fills all styles with default values.
   */
  UmbraStyleSheet();
};

#endif /* UMBRA_STYLESHEET_HPP */
