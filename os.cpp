#ifndef _OSS_CPP
#define _OSS_CPP

#include "os.h"

using namespace std;


bool OS::DirExists( const string name )
    {
    wxString string_name = name.c_str( );
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
string OS::UserDataDir( )
    {
    wxStandardPaths StandardPaths = wxStandardPaths::Get( );
    return string( StandardPaths.GetUserDataDir( ));
    }
string OS::HomeDir( )
    {
    return string( wxGetHomeDir( ));
    }

#endif
