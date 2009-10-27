#include "main.hpp"

UmbraModule::UmbraModule (void) {
    this->fadeIn = 0;
    this->fadeOut = 0;
}

void UmbraModule::setFade (int in, int out) {
    fadeIn = in;
    fadeOut = out;
}
