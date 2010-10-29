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

enum UmbraLogResult {
	UMBRA_LOG_FAILURE,
	UMBRA_LOG_SUCCESS,
	UMBRA_LOG_NONE
};

class UmbraLog {
	friend class UmbraEngine;
	friend class UmbraModule;
private:
	static FILE * out;
	static time_t rawTime;
	static struct tm * timeInfo;
	static int indent;
	static void save();
	static void initialise();
	static void output(int logLevel, const char * str);
	static void output(int logLevel, std::string str);
public:
	static void openBlock(const char * str, ...);
	static void openBlock(std::string str);
	static void info(const char * str, ...);
	static void info(std::string str);
	static void notice(const char * str, ...);
	static void notice(std::string str);
	static void warning(const char * str, ...);
	static void warning(std::string str);
	static void error(const char * str, ...);
	static void error(std::string str);
	static void fatalError(const char * str, ...);
	static void fatalError(std::string str);
	static void closeBlock(UmbraLogResult result = UMBRA_LOG_NONE);
};
