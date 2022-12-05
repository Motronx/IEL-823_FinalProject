

#include "angle.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS


void angle_generic_read ( angle_t *ctx, int reg, int *data_buf, int len )
{
   // i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

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



// ------------------------------------------------------------------------- END