#ifndef _OS_H
#define _OS_H

#include <wx/stdpaths.h>

class OS
    {
    public:
        OS( );
        bool DirExists( const string name );
        bool FileExists( const string name );
        string GetUserDataDir( );
        char Slash( );
    private:
    };

#endif
