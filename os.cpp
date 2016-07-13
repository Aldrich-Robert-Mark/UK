#include "os.h"

using namespace std;

wxStandardPaths StandardPaths = wxStandardPaths::Get( );

OS::OS( )
    {
    }
bool OS::DirExists( const string name )
    {
    wxString string_name;
    string_name.FromAscii( name.c_str( ));
    return wxDirExists( string_name );
    }
bool OS::FileExists( const string name )
    {
    wxString StringName = StringName.FromAscii( name.c_str( ));;
    wxFileName FileName( StringName, wxPATH_NATIVE );
    return FileName.FileExists( );
    }
char OS::Slash( )
    {
    return (char) wxFileName::GetPathSeparator( ).GetValue( );
    }
string OS::GetUserDataDir( )
    {
    return string( StandardPaths.GetUserDataDir( ));
    }
