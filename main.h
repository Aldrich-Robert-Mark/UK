#ifndef _MAIN_H
#define _MAIN_H

#include <wx/wx.h>
#include <string.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/stdpaths.h>
#include "configuration.h"
#include "top_level.h"

// DEFINE THE STRUCTURE OF THE MAIN PROGRAM


// Declare the application class
class MainProgram : public wxApp {
    public:
        // Called on application startup
        virtual bool OnInit( );
    };

// Implements MainProgram GetApp( )
DECLARE_APP( MainProgram )

#endif
