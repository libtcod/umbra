#include "umbra.hpp"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

FILE * UmbraLog::logOut = NULL;
FILE * UmbraLog::errOut = NULL;
struct timeval UmbraLog::rawTime;
struct tm * UmbraLog::timeInfo;
int UmbraLog::indent = 0;

const char * logTypeString[] = {
	"INF.",
	"NOT.",
	"WAR.",
	"ERR.",
	"FAT."
};

const char * logTypeStringLong[] = {
	"INFO",
	"NOTIFICATION",
	"WARNING",
	"ERROR",
	"FATAL ERROR"
};

const char * resultString[] = {
	"[END BLOCK: FAILURE]",
	"[END BLOCK: SUCCESS]",
	"[END BLOCK]"
};

void UmbraLog::logInitialise() {
	logOut = fopen("log.txt","w");
	gettimeofday(&rawTime,NULL);
	timeInfo = localtime(&(rawTime.tv_sec));
	fprintf(logOut,"%s ver. %s (%s) Log file, created on %04d-%02d-%02d, %02d:%02d:%02d.%03d.\n"
	            "---===---\n"
	            "INF. = INFORMATION. Informative message.\n"
	            "NOT. = NOTICE. Something unexpected that does not affect the program execution.\n"
	            "WAR. = WARNING. An error that may potentially provoke some misbehaviour.\n"
	            "ERR. = ERROR. An error that is guaranteed to provoke some misbehaviour.\n"
	            "FAT. = FATAL ERROR. An error that prevents the program from continuing.\n"
	            "---===---",
	            UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS,
	            timeInfo->tm_year, timeInfo->tm_mon, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, rawTime.tv_usec/1000);
	fflush(logOut);
}

void UmbraLog::errInitialise() {
	errOut = fopen("errorlog.txt","w");
	gettimeofday(&rawTime,NULL);
	timeInfo = localtime(&(rawTime.tv_sec));
	fprintf(errOut,"%s ver. %s (%s) Error log file, created on %04d-%02d-%02d, %02d:%02d:%02d.%03d.\n"
	            "---===---",
	            UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS,
	            timeInfo->tm_year, timeInfo->tm_mon, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, rawTime.tv_usec/1000);
	fflush(errOut);
}

void UmbraLog::save() {
	indent = 0;
	UmbraLog::info("Log file saved.");
	if (logOut != NULL) fclose(logOut);
	if (errOut != NULL) fclose(errOut);
}

void UmbraLog::output(UmbraLogType type, UmbraLogResult res, const char * str) {
	if (UmbraConfig::logLevel > (UmbraLogLevel)type) return;
	if (logOut == NULL) {
		logInitialise();
		if (res >= UMBRA_LOGRESULT_FAILURE || indent == 0) {
			error("UmbraLog::closeBlock | Tried to close a block, but it hasn't been opened in the first place.");
			return;
		}
	}
	gettimeofday(&rawTime,NULL);
	timeInfo = localtime(&(rawTime.tv_sec));
	UmbraLogMessage * msg = new UmbraLogMessage();
	msg->msg = str;
	msg->logType = type;
	msg->indent = indent;
	msg->result = res;
	msg->time.h = timeInfo->tm_hour;
	msg->time.m = timeInfo->tm_min;
	msg->time.s = timeInfo->tm_sec;
	msg->time.ms = rawTime.tv_usec/1000;
	if (type >= UMBRA_LOGTYPE_WARNING) {
		if (errOut == NULL) errInitialise();
		fprintf(logOut,"\n%s %02d:%02d:%02d.%03d %s", logTypeStringLong[type], msg->time.h, msg->time.m, msg->time.s, msg->time.ms, str);
	}
	std::string arrows;
	for (int i = 0; i < indent; i++)
		if (i < indent - 1) arrows += " |  ";
		else arrows += " |> ";
	if (res < UMBRA_LOGRESULT_FAILURE) {
		fprintf(logOut,"\n%s %02d:%02d:%02d.%03d %s%s", logTypeString[type], msg->time.h, msg->time.m, msg->time.s, msg->time.ms, arrows.c_str(), str);
		fprintf(stderr,"%s: %s\n", logTypeString[type], str);
	}
	else fprintf(logOut,"\n%s %02d:%02d:%02d.%03d %s%s", logTypeString[UMBRA_LOGTYPE_INFO], msg->time.h, msg->time.m, msg->time.s, msg->time.ms, arrows.c_str(), resultString[res]);
	fflush(logOut);
}

void UmbraLog::output(UmbraLogType type, UmbraLogResult res, std::string str) {
	output(type,res,str.c_str());
}

void UmbraLog::openBlock(const char* str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOGTYPE_INFO,(UmbraLogResult)(-1),s);
	++indent;
}

void UmbraLog::openBlock(std::string str) {
	output(UMBRA_LOGTYPE_INFO,(UmbraLogResult)(-1),str);
	++indent;
}

void UmbraLog::info(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOGTYPE_INFO,(UmbraLogResult)(-1),s);
}

void UmbraLog::info(std::string str) {
	output(UMBRA_LOGTYPE_INFO,(UmbraLogResult)(-1),str);
}

void UmbraLog::warning(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOGTYPE_WARNING,(UmbraLogResult)(-1),s);
}

void UmbraLog::warning(std::string str) {
	output(UMBRA_LOGTYPE_WARNING,(UmbraLogResult)(-1),str);
}

void UmbraLog::error(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOGTYPE_ERROR,(UmbraLogResult)(-1),s);
}

void UmbraLog::error(std::string str) {
	output(UMBRA_LOGTYPE_ERROR,(UmbraLogResult)(-1),str);
}

void UmbraLog::fatalError(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	output(UMBRA_LOGTYPE_FATAL,(UmbraLogResult)(-1),s);
}

void UmbraLog::fatalError(std::string str) {
	output(UMBRA_LOGTYPE_FATAL,(UmbraLogResult)(-1),str);
}

void UmbraLog::closeBlock(UmbraLogResult result) {
	output(UMBRA_LOGTYPE_INFO,result,"");
	if (indent > 0) --indent;
}
