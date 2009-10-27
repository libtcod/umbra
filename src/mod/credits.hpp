#ifndef MODULE_CREDITS_HPP
#define MODULE_CREDITS_HPP

#include "umbra/module.hpp"

class Credits : public UmbraModule {
    public:
        Credits (void);
        bool render (void);

    private:
        char credits[32];
};

#endif
