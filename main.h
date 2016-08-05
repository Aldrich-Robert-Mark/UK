#ifndef _MAIN_H
#define _MAIN_H

#include <string.h>
#include <iostream>

#include "configuration.h"
#include "graphics.h"

// DEFINE THE STRUCTURE OF THE MAIN PROGRAM


// Declare the application class
class MainProgram : public wxApp {
    public:
        // Called on application startup
        virtual bool OnInit( );
    };

#endif
