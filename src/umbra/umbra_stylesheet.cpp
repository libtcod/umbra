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

#include <umbra.hpp>
#include <umbra_stylesheet.hpp>
#include <string.h>

UmbraStyleSheet::UmbraStyleSheet () {
	//placeholder --- hardcoded values
	colour(TCODColor::white, "normal");
	colour(TCODColor::lighterGrey, "hover");
	colour(TCODColor::yellow, "active");
	backgroundColour(TCODColor::darkerRed, "normal");
	backgroundColour(TCODColor::darkRed, "hover");
	backgroundColour(TCODColor::red, "active");
	borderColour(TCODColor::blue, "normal");
	borderColour(TCODColor::lightBlue, "hover");
	borderColour(TCODColor::lighterBlue, "active");
}

void UmbraStyleSheet::colour (TCODColor val, const char* pseudoClass) {
	if (pseudoClass == NULL)
		normal.colour = hover.colour = active.colour = val;
	else if (strcmp(pseudoClass,"normal") == 0)
		normal.colour = val;
	else if (strcmp(pseudoClass,"hover") == 0)
		hover.colour = val;
	else if (strcmp(pseudoClass,"active") == 0)
		active.colour = val;
	else
		UmbraLog::error("UmbraStyleSheet::colour | unknown pseudoclass \"%s\".", pseudoClass);
}

void UmbraStyleSheet::backgroundColour (TCODColor val, const char* pseudoClass) {
	if (pseudoClass == NULL)
		normal.backgroundColour = hover.backgroundColour = active.backgroundColour = val;
	else if (strcmp(pseudoClass,"normal") == 0)
		normal.backgroundColour = val;
	else if (strcmp(pseudoClass,"hover") == 0)
		hover.backgroundColour = val;
	else if (strcmp(pseudoClass,"active") == 0)
		active.backgroundColour = val;
	else
		UmbraLog::error("UmbraStyleSheet::backgroundColour | unknown pseudoclass \"%s\".", pseudoClass);
}

void UmbraStyleSheet::borderColour (TCODColor val, const char* pseudoClass) {
	if (pseudoClass == NULL)
		normal.borderColour = hover.borderColour = active.borderColour = val;
	else if (strcmp(pseudoClass,"normal") == 0)
		normal.borderColour = val;
	else if (strcmp(pseudoClass,"hover") == 0)
		hover.borderColour = val;
	else if (strcmp(pseudoClass,"active") == 0)
		active.borderColour = val;
	else
		UmbraLog::error("UmbraStyleSheet::backgroundColour | unknown pseudoclass \"%s\".", pseudoClass);
}
