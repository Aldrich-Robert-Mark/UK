#ifndef _OS_H
#define _OS_H

#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/utils.h>

using namespace std;

class OS
    {
    public:
        bool DirExists( const string name );
        bool FileExists( const string name );
        string UserDataDir( );
        string HomeDir( );
        char Slash( );
    private:
    };

#endif
