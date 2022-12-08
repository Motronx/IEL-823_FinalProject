
extern "C"{
#ifndef ANGLE_H
#define ANGLE_H
#define ANGLE_OK           0x00
#define ANGLE_INIT_ERROR   0xFF

/**
 * \defgroup error_register_status Error register status
 * \{
 */
#define ANGLE_ERROR_REG_MASK              0x34 
#define ANGLE_EXTENDED_ERROR_REG_MASK     0x36 
#define ANGLE_EXTENDED_ERROR_REG          0x26 
#define ANGLE_ERROR_REG                   0x24 
#define ANGLE_STATUS_REG                  0x22 
#define ANGLE_SETTINGS_REG                0x1E 
/** \} */

/**
 * \defgroup processor_state Change Processor State
 * \{
 */
#define ANGLE_CDS_NO_CHANGLE              0x0000 << 13
#define ANGLE_CDS_IDLE_MODE               0x0002 << 13
#define ANGLE_CDS_RUN_MODE                0x0003 << 13
/** \} */

/**
 * \defgroup hard_reset Hard reset
 * \{
 */
#define ANGLE_HDR_RESET_0                 0x0000 << 12
#define ANGLE_HDR_RESET_1                 0x0001 << 12
/** \} */

/**
 * \defgroup soft_reset Soft Reset
 * \{
 */
#define ANGLE_SFR_RESET_0                 0x0000 << 11
#define ANGLE_SFR_RESET_1                 0x0001 << 11

#define ANGLE_CSR_STA_0                   0x0000 << 9
#define ANGLE_CSR_STA_1                   0x0001 << 9

#define ANGLE_CXE_0                       0x0000 << 8
#define ANGLE_CXE_1                       0x0001 << 8

#define ANGLE_CER_0                      0x0000 << 7
#define ANGLE_CER_1                      0x0001 << 7
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES

typedef struct
{
 
} angle_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{


} angle_cfg_t;

#ifdef __cplusplus
#endif


void angle_cfg_setup ( angle_cfg_t *cfg );

int angle_get_angle ( angle_t *ctx );

int angle_get_temperature ( angle_t *ctx );

int angle_get_magnetics ( angle_t *ctx );
}
#ifdef __cplusplus
#endif
#endif

