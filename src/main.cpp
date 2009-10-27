#include "main.hpp"

int main()
{
    //create the engine
    UmbraEngine * engine = new UmbraEngine();
    //declare modules
    engine->registerModule(new Credits());
    //initialise and run the engine
    if (engine->initialise()) return engine->run();
    else return 1;
}
