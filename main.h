#include <wx/wx.h>

#include "mondrian.xpm"

// DEFINE THE STRUCTURE OF THE MAIN PROGRAM

// Declare the application class
class MainProgram : public wxApp {
    public:
        // Called on application startup
        virtual bool OnInit( );
    };

// Implements MainProgram GetApp( )
DECLARE_APP( MainProgram )

class GlobalVariables
    {
    public:
        virtual bool GetProgramName( char *name );
    private:
        char official_program_name;
    };
