
// ------------------------------------------------------------------- INCLUDES

#include <Arduino.h>
#include "angle.h"
// ------------------------------------------------------------------ VARIABLES

static angle_t angle;
//tatic log_t logger;

int angle_val;
int magnetics_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    //log_cfg_t log_cfg;
    angle_cfg_t cfg;


    //  Click initialization.

    angle_cfg_setup( &cfg );
}

void application_task ( void )
{
    angle_val = angle_get_angle( &angle );
   // log_printf( &logger, "Angle :%d \r\n", angle_val );
    
    magnetics_val = angle_get_magnetics( &angle );
    //log_printf( &logger, "Magnetics :%d \r\n", magnetics_val );
    
    delay(1000);
}