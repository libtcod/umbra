#include "umbra.hpp"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

FILE * UmbraLog::out = NULL;
time_t UmbraLog::rawTime;
struct tm * UmbraLog::timeInfo;

UmbraLogEntry::UmbraLogEntry() {
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	result = UMBRA_LOG_SUCCESS;
}

void UmbraLogEntry::set(const char * str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);
	message = s;
}

void UmbraLog::initialise() {
	out = fopen("log.txt","w");
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	fprintf(out,"%s ver. %s (%s) Log file, created on %04d-%02d-%02d, %02d:%02d:%02d.\n"
	            "---===---",
	            UMBRA_TITLE, UMBRA_VERSION, UMBRA_STATUS,
	            timeInfo->tm_year, timeInfo->tm_mon, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
	fflush(out);
}

void UmbraLog::save() {
	UmbraLog::add("Log file saved.");
	if (out != NULL) fclose(out);
}

void UmbraLog::add(const char* str, ...) {
	char s[2048];
	va_list ap;
	va_start(ap,str);
	vsprintf(s,str,ap);
	va_end(ap);

	if (!UmbraConfig::debug) return;
	if (out == NULL) initialise();

	time(&rawTime);
	timeInfo = localtime(&rawTime);

	fprintf(out,"\n%02d:%02d:%02d - %s", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, s);
	fflush(out);
}

void UmbraLog::add(std::string str) {
	if (!UmbraConfig::debug) return;
	if (out == NULL) initialise();

	time(&rawTime);
	timeInfo = localtime(&rawTime);

	fprintf(out,"\n%02d:%02d:%02d - %s", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, str.c_str());
	fflush(out);
}

void UmbraLog::add(UmbraLogResult result) {
	if (!UmbraConfig::debug) return;
	if (result == UMBRA_LOG_FAILURE)
		fprintf(out," [FAILED]");
	if (result == UMBRA_LOG_SUCCESS)
		fprintf(out," [  OK  ]");
}

void UmbraLog::add(UmbraLogEntry entry) {
	if (!UmbraConfig::debug) return;
	if (out == NULL) initialise();

	time(&rawTime);
	timeInfo = localtime(&rawTime);

	fprintf(out,"\n%02d:%02d:%02d through %02d:%02d:%02d - %s %s",
	            entry.timeInfo->tm_hour, entry.timeInfo->tm_min, entry.timeInfo->tm_sec,
	            timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec,
	            entry.message.c_str(), entry.result == UMBRA_LOG_SUCCESS ? "[  OK  ]" : "[FAILED]");
	fflush(out);
}
