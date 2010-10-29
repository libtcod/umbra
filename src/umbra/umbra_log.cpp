#include "umbra.hpp"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

FILE * UmbraLog::out = NULL;
time_t UmbraLog::rawTime;
struct tm * UmbraLog::timeInfo;
int UmbraLog::indent = 0;

const char * levelString[] = {
	"INF.",
	"NOT.",
	"WAR.",
	"ERR.",
	"FAT."
};
const char * resultString[] = {
	"[END BLOCK: FAILURE]",
	"[END BLOCK: SUCCESS]",
	"[END BLOCK]"
};

enum {
	UMBRA_LOG_INFO,
	UMBRA_LOG_NOTICE,
	UMBRA_LOG_WARN,
	UMBRA_LOG_ERROR,
	UMBRA_LOG_FATAL
};

void UmbraLog::initialise() {
	out = fopen("log.txt","w");
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	fprintf(out,"%s ver. %s (%s) Log file, created on %04d-%02d-%02d, %02d:%02d:%02d.\n"
	            "---===---\n"
	            "INF. = INFORMATION. Informative message.\n"
	            "NOT. = NOTICE. Something unexpected that does not affect the program execution.\n"
	            "WAR. = WARNING. An error that may potentially provoke some misbehaviour.\n"
	            "ERR. = ERROR. An error that is guaranteed to provoke some misbehaviour.\n"
	            "FAT. = FATAL ERROR. An error that prevents the program from continuing.\n"
	            "---===---",
	            UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS,
	            timeInfo->tm_year, timeInfo->tm_mon, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
	fflush(out);
}

void UmbraLog::save() {
	indent = 0;
	UmbraLog::info("Log file saved.");
	if (out != NULL) fclose(out);
}

void UmbraLog::output(int logLevel, const char * str) {
	if (!UmbraConfig::debug) return;
	if (out == NULL) initialise();
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	std::string arrows;
	for (int i = 0; i < indent; i++)
		if (i < indent - 1) arrows += " |  ";
		else arrows += " |> ";
	fprintf(out,"\n%s %02d:%02d:%02d.%03d %s%s", levelString[logLevel], timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, 0, arrows.c_str(), str);
	fflush(out);
	fprintf(stderr,"%s\n",str);
}

void UmbraLog::output(int logLevel, std::string str) {
	if (!UmbraConfig::debug) return;
	if (out == NULL) initialise();
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	std::string arrows;
	for (int i = 0; i < indent; i++)
		if (i < indent - 1) arrows += " |  ";
		else arrows += " |> ";
	fprintf(out,"\n%s %02d:%02d:%02d.%03d %s%s", levelString[logLevel], timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, 0, str.c_str());
	fflush(out);
	fprintf(stderr,"%s\n",str.c_str());
}

void UmbraLog::openBlock(const char* str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOG_INFO,s);
	++indent;
}

void UmbraLog::openBlock(std::string str) {
	output(UMBRA_LOG_INFO,str);
	++indent;
}

void UmbraLog::info(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOG_INFO,s);
}

void UmbraLog::info(std::string str) {
	output(UMBRA_LOG_INFO,str);
}

void UmbraLog::warning(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOG_WARN,s);
}

void UmbraLog::warning(std::string str) {
	output(UMBRA_LOG_WARN,str);
}

void UmbraLog::error(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOG_ERROR,s);
}

void UmbraLog::error(std::string str) {
	output(UMBRA_LOG_ERROR,str);
}

void UmbraLog::fatalError(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOG_FATAL,s);
}

void UmbraLog::fatalError(std::string str) {
	output(UMBRA_LOG_FATAL,str);
}

void UmbraLog::closeBlock(UmbraLogResult result) {
	if (!UmbraConfig::debug) return;
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	std::string arrows;
	for (int i = 0; i < indent; i++)
		if (i < indent - 1) arrows += " |  ";
		else arrows += " \\> ";
	fprintf(out,"\n%s %02d:%02d:%02d.%03d %s%s", levelString[UMBRA_LOG_INFO], timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, 0, arrows.c_str(), resultString[result]);
	--indent;
}
