#include <wx/wx.h>


// Declare the main frame class
class PrimaryWindow : public wxFrame {
    public:
        // Constructor
        PrimaryWindow( const wxString& title );

        // Event handlers
        void OnQuit( wxCommandEvent& event );

    private:
        // This class handles events
        DECLARE_EVENT_TABLE( );
    };


