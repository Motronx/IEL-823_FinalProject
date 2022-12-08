#include <Arduino.h>            //Se llama a la libreria de arduino para que reconoceza las funciones porpias de el
#include "testinghall.h"        //Se llama a la libreria .h de nuestro proyecto
#include "angle.h"              //Se llama a la libreria de encabezado

static angle_t angle;
int angle_val;
int magnetics_val;

void application_init ( void )
{
    angle_cfg_t cfg;
    angle_cfg_setup( &cfg );
}

void application_task ( void )
{
    angle_val = angle_get_angle( &angle );
    magnetics_val = angle_get_magnetics( &angle );    
    delay(1000);
}