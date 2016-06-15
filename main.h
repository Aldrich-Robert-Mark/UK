#include <wx/wx.h>
#include <string.h>

#include "mondrian.xpm"

// DEFINE THE STRUCTURE OF THE MAIN PROGRAM

class GlobalVariables
    {
    public:
        char * GetProgramName( )
            {
            return official_program_name;
            }
        char * GetDefaultPath( )
            {
            return default_base_path;
            }
        char * SetDefaultPath( char * name )
            {
            strcpy( default_base_path, name );
            }
        GlobalVariables( )
            {
            strcpy( official_program_name, "1840" );
            }
    private:
        char official_program_name[5];
        char default_base_path[256];
    };

// Declare the application class
class MainProgram : public wxApp {
    public:
        // Called on application startup
        virtual bool OnInit( );
    };

// Implements MainProgram GetApp( )
DECLARE_APP( MainProgram )
