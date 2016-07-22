#ifndef _TOP_LEVEL_H
#define _TOP_LEVEL_H

#include <wx/wx.h>

#include "configuration.h"

// Declare the main frame class
class TopLevel : public wxFrame
    {
    public:
        // Constructor
        TopLevel( Configuration *config );

        // Event handlers
        void OnQuit( wxCommandEvent& event );

    private:
        // This class handles events
        DECLARE_EVENT_TABLE( );
    };

#endif
