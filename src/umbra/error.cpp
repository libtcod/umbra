#include "main.hpp"
#include <stdarg.h>
#include <stdio.h>

//initialise empty error list
TCODList <std::string*> UmbraError::errors;

//append an error message
void UmbraError::add (const char * errStr, ...) {
    char err[2048];
    va_list ap;
    va_start(ap,errStr);
    vsprintf(err,errStr,ap);
    va_end(ap);

    std::string * errorMessage = new std::string (err);

    errors.push(errorMessage);
    fprintf(stderr,"%s\n",errorMessage->c_str());

    save();
}

//save the error log
void UmbraError::save (void) {
    //if there are no errors, return
    if (errors.size() == 0) return;
    //else create the log file
    else {
        //create an empty error log file
        FILE * out = fopen("errorlog.txt","w");

        //print the log header
        fprintf(out,"%s ver. %s (%s) Error Log\n"
                    "---===---\n"
                    "%d error(s) registered in the log.\n"
                    "\n"
                    "\n"
                    "BEGIN ERROR LOG\n"
                    "---===---\n"
                    "\n",
                    UMBRA_TITLE,UMBRA_VERSION,UMBRA_STATUS,errors.size());

        //print the errors
        int i = 0;
        do {
            std::string * msg = errors.get(i);
            fprintf(out,"%03d: %s\n",i+1,msg->c_str());
        } while (++i < errors.size());

        //print the log footer
        fprintf(out,"\n"
                    "---===---\n"
                    "END ERROR LOG\n");

        //close the log file
        fclose(out);
    }
}

//confirms the existence of a file. Returns false if there is no such file.
bool UmbraError::fileExists (const char * filename, ...) {
    char f[256];
    va_list ap;
    va_start(ap,filename);
    vsprintf(f,filename,ap);
    va_end(ap);

    bool retVal = false;
    FILE * in = fopen(f,"rb");
    if (in != NULL) {
        retVal = true;
        fclose(in);
    }
    return retVal;
}
