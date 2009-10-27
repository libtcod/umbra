#ifndef UMBRA_ENGINE_HPP
#define UMBRA_ENGINE_HPP

class UmbraModule;

//the main engine
class UmbraEngine {
    public:
        UmbraEngine (void); //constructor
        ~UmbraEngine (void); //destructor

        bool initialise (void); //initialises the engine
        int run (void); //runs the engine
        void registerModule (UmbraModule * module); //add a module to the modules list

    private:
        bool globalKeybindings (TCOD_key_t key);

        int currentModule; //actual module number
        UmbraModule * module; //currently running module
        TCODList <UmbraModule*> modules;
};

#endif
