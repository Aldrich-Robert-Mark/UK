#include "top_level.h"

using namespace std;

// Construct top level object (CONSTRUCTOR)
TopLevel::TopLevel( Configuration *config )
    {
    // Create the base window
    Create( NULL, TOPLEVEL, _( config->ProgramName( )));


    }



