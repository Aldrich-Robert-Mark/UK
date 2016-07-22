#include "time_features.h"

void time_features::pause( float duration )
    {
    clock_t end_time = clock( ) + (clock_t)( (float)CLOCKS_PER_SEC * duration );
    while( clock( ) <= end_time );
    }
