#ifndef _TOP_LEVEL_H
#define _TOP_LEVEL_H

#include <wx/wx.h>

#include "configuration.h"
#include "point_def.h"

// Declare the main frame class
class TopLevel : public wxFrame
    {
    public:
        // Constructor
        TopLevel( Configuration *config );

        // Event handlers
        void OnQuit( wxCommandEvent& event );

    private:
        Point Position( );
        void Position( const Point ip );
        Point Size( );
        void Size( const Point ip );

        // This class handles events
        DECLARE_EVENT_TABLE( );
    };

#endif
