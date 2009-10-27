#ifndef UMBRA_ERROR_HPP
#define UMBRA_ERROR_HPP

#include <iostream>

class UmbraError {
    private:
    static TCODList <std::string*> errors; //list of all errors as strings
    static void save (void); //saves the error log to an external file for further examination

    public:
    static void add (const char * errStr, ...); //adds an error to the list
    static bool fileExists (const char * filename, ...); //confirms the existence of a file
};

#endif
