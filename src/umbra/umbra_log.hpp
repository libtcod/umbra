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

/**
 * The results of closing a log block.
 */
enum UmbraLogResult {
	UMBRA_LOGRESULT_FAILURE,
	UMBRA_LOGRESULT_SUCCESS,
	UMBRA_LOGRESULT_NONE
};

/**
 * The message log, used for debugging. It logs messages in a nested hierarchy, showing not only the place and time of saving the message, but also the caller-callee dependency (if used in both the caller and callee methods).
 */
class UmbraLog {
	friend class UmbraEngine;
private:
	enum UmbraLogType {
		UMBRA_LOGTYPE_INFO,
		UMBRA_LOGTYPE_NOTICE,
		UMBRA_LOGTYPE_WARNING,
		UMBRA_LOGTYPE_ERROR,
		UMBRA_LOGTYPE_FATAL
	};
	class UmbraLogMessage {
		friend class UmbraLog;
		std::string msg;
		uint32 time;
		UmbraLogResult result;
		UmbraLogType logType;
		int indent;
	};
	static FILE * out;
	static int indent;
	static TCODList <UmbraLogMessage*> messages;
	static void save ();
	static void initialise ();
	static void output (UmbraLogType type, UmbraLogResult result, int indent, const char * str);
	static void output (UmbraLogType type, UmbraLogResult result, int indent, std::string str);
public:
	/**
	 * Opens a block in the log (increases the indent). The log level of this message is <code>INFO</code>.
     * @param str the log message string, <code>printf</code>-like formatted
     * @param ... optional parametres for the message formatting
     */
	static void openBlock (const char * str, ...);
	/**
	 * Opens a block in the log (increases the indent). The log level of this message is <code>INFO</code>.
     * @param str the log message string, as a C++ string
     */
	static void openBlock (std::string str);
	/**
	 * Puts a message with the log level <code>INFO</code> in the log.
     * @param str the log message string, <code>printf</code>-like formatted
     * @param ... optional parametres for the message formatting
     */
	static void info (const char * str, ...);
	/**
	 * Puts a message with the log level <code>INFO</code> in the log.
     * @param str the log message string, as a C++ string
     */
	static void info (std::string str);
	/**
	 * Puts a message with the log level <code>NOTICE</code> in the log.
     * @param str the log message string, <code>printf</code>-like formatted
     * @param ... optional parametres for the message formatting
     */
	static void notice (const char * str, ...);
	/**
	 * Puts a message with the log level <code>NOTICE</code> in the log.
     * @param str the log message string, as a C++ string
     */
	static void notice (std::string str);
	/**
	 * Puts a message with the log level <code>WARNING</code> in the log.
     * @param str the log message string, <code>printf</code>-like formatted
     * @param ... optional parametres for the message formatting
     */
	static void warning (const char * str, ...);
	/**
	 * Puts a message with the log level <code>NOTICE</code> in the log.
     * @param str the log message string, as a C++ string
     */
	static void warning (std::string str);
	/**
	 * Puts a message with the log level <code>ERROR</code> in the log.
     * @param str the log message string, <code>printf</code>-like formatted
     * @param ... optional parametres for the message formatting
     */
	static void error (const char * str, ...);
	/**
	 * Puts a message with the log level <code>ERROR</code> in the log.
     * @param str the log message string, as a C++ string
     */
	static void error (std::string str);
	/**
	 * Puts a message with the log level <code>FATAL ERROR</code> in the log.
     * @param str the log message string, <code>printf</code>-like formatted
     * @param ... optional parametres for the message formatting
     */
	static void fatalError (const char * str, ...);
	/**
	 * Puts a message with the log level <code>FATAL ERROR</code> in the log.
     * @param str the log message string, as a C++ string
     */
	static void fatalError (std::string str);
	/**
	 * Closes a block in the log (decreases the indent). The log level is <code>INFO</code>.
     * @param result (optional) the result of the block (success or failure). A failure will typically be preceded with a logged message describing the reason for the block to end with a failure.
     */
	static void closeBlock (UmbraLogResult result = UMBRA_LOGRESULT_NONE);
};
