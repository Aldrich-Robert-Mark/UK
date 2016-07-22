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
    ARCHIVE_LOCAL_ORIGIN  = 7,
    ARCHIVE_REMOTE_ORIGIN = 8
    };

enum DatabaseOperations
    {
    OPEN        = 0,
    CLOSE       = 1,
    PREPARE     = 2,
    RUN         = 3,
    FINALIZE    = 4
    };

#endif
