#ifndef _IDENTIFICATIONS_H
#define _IDENTIFICATIONS_H

enum FrameTitle
    {
    TOPLEVEL    = 0,
    LETTERS     = 1,
    ENVELOPES   = 2,
    ADDRESSING  = 3,
    OUTGOING    = 4,
    INCOMING    = 5,
    RECEIVED    = 6,
    ARCHIVE_LOCAL  = 7,
    ARCHIVE_REMOTE = 8
    };

enum DatabaseOperations
    {
    OPEN        = 0,
    CLOSE       = 1,
    PREPARE     = 2,
    RUN         = 3,
    FINALIZE    = 4
    };

enum WindowControl
    {
    RESET_WINDOWS               = 0,
    ID_LETTERS_WINDOW           = 1,
    ID_ENVELOPES_WINDOW         = 2,
    ID_ADDRESSING_WINDOW        = 3,
    ID_OUTGOING_WINDOW          = 4,
    ID_INCOMING_WINDOW          = 5,
    ID_RECEIVED_WINDOW          = 6,
    ID_LOCAL_WINDOW             = 7,
    ID_REMOTE_WINDOW            = 8
    };

#endif
