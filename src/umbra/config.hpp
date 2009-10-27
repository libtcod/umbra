#ifndef UMBRA_CONFIG_HPP
#define UMBRA_CONFIG_HPP

class UmbraConfig {
    public:
    static void load (void);

    static int xSize;
    static int ySize;
    static int fontSize;
    static bool fullScreen;
    static std::string * fontFile;

    private:
    static TCODParser parser;
};

#endif
