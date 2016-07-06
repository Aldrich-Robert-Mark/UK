#ifndef _PRIMARY_H
#define _PRIMARY_H

#include <wx/wx.h>
#include "configuration.h"


// Declare the main frame class
class PrimaryFrame : public wxFrame {
    public:
        // Constructor
        PrimaryFrame( Configuration *config );

        // Event handlers
        void OnQuit( wxCommandEvent& event );

    private:
        // This class handles events
        DECLARE_EVENT_TABLE( );
        void pause( float seconds );
    };

#endif
