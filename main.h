#ifndef _MAIN_H
#define _MAIN_H

#include <string.h>

#include "configuration.h"
#include "top_level.h"

// DEFINE THE STRUCTURE OF THE MAIN PROGRAM


// Declare the application class
class MainProgram : public wxApp {
    public:
        // Called on application startup
        virtual bool OnInit( );
    };

#endif
