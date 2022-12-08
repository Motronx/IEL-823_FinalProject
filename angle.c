

#include "angle.h"          //Se incluye la libreria de encabezados

//Cuatro funciones a definir par la realizacion de las pruebas
void angle_generic_read ( angle_t *ctx, int reg, int *data_buf, int len )
{
}

//Esta funcion obtiene el angulo en dicha posicion del objeto

int angle_get_angle ( angle_t *ctx )
{
    int read_reg[ 2 ];
    int angle;
    int angle_val;
    angle_generic_read( ctx, 0x20, read_reg, 2 );
    angle = read_reg[ 0 ];
    angle <<= 8;
    angle |= read_reg[ 1 ];
    angle &= 0x0FFF;
    angle_val = ( int )( angle * (360 / 4096.0));
    return angle_val;
}

//Esta funcion obtiene la temperatura de operacion del dispositivo

int angle_get_temperature ( angle_t *ctx )
{
    int read_reg[ 2 ];
    int temp;
    int temp_val;
    angle_generic_read( ctx, 0x28, read_reg, 2 );
    temp = read_reg[ 0 ];
    temp <<= 8;
    temp |= read_reg[ 1 ];
    temp &= 0x0FFF;
    temp_val = ( int )temp / 8 - 273;
    return temp_val;
}

//Esta funcion me realiza el calculo de la fuerza magentica

int angle_get_magnetics ( angle_t *ctx )
{
    int read_reg[ 2 ];
    int magnet;
    int magnet_val;
    angle_generic_read( ctx, 0x2A, read_reg, 2 );
    magnet = read_reg[ 0 ];
    magnet <<= 8;
    magnet |= read_reg[ 1 ];
    magnet &= 0x0FFF;
    magnet_val = ( int )magnet;

    return magnet_val;
}
