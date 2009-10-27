#ifndef UMBRA_MODULE_HPP
#define UMBRA_MODULE_HPP

//all screens or views, such as credits, main menu, map view, etc. have to inherit this
class UmbraModule {
    public:
        UmbraModule (void); //constructor
        virtual ~UmbraModule (void) {} //destructor
        virtual bool render (void) { return true; } //render the module on the root console
        virtual bool update (void) { return true; } //update the module's logic
        virtual void localKeybindings (TCOD_key_t key) { return; } //module-specific keyboard

        void setFade (int in, int out); //set fade lengths in milliseconds

    private:
        int fadeIn;
        int fadeOut;
};

#endif
