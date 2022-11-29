 /*
 * i2c_tools.c
 *
 *  Created on: 1 abr 2022
 *      Author: edgar
 */
#include "i2c_tools.h"
#include "fsl_i2c.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_debug_console.h"

uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];

static i2c_master_transfer_t g_masterXfer;
static i2c_rtos_handle_t master_rtos_handle;

SemaphoreHandle_t g_i2c_sem;

void i2c_init(I2C_Type* i2c_to_use)
{

    i2c_master_config_t masterConfig;
    uint32_t sourceClock;
    status_t status;
    /** PTB2 configuration to output to I2C0 SCL */
    const port_pin_config_t portb2_config = {/* Internal pull-up resistor is enabled */
                                                   kPORT_PullUp,
                                                   /* Fast slew rate is configured */
                                                   kPORT_FastSlewRate,
                                                   /* Passive filter is disabled */
                                                   kPORT_PassiveFilterDisable,
                                                   /* Open drain is enabled */
                                                   kPORT_OpenDrainEnable,
                                                   /* Low drive strength is configured */
                                                   kPORT_LowDriveStrength,
                                                   /* Pin is configured as I2C0_SCL */
                                                   kPORT_MuxAlt2,
                                                   /* Pin Control Register fields [15:0] are not locked */
                                                   kPORT_UnlockRegister};

    /** PTB3 configuration to output to I2C0 SDA */
    const port_pin_config_t portb3_config = {/* Internal pull-up resistor is enabled */
                                                   kPORT_PullUp,
                                                   /* Fast slew rate is configured */
                                                   kPORT_FastSlewRate,
                                                   /* Passive filter is disabled */
                                                   kPORT_PassiveFilterDisable,
                                                   /* Open drain is enabled */
                                                   kPORT_OpenDrainEnable,
                                                   /* Low drive strength is configured */
                                                   kPORT_LowDriveStrength,
                                                   /* Pin is configured as I2C0_SDA */
                                                   kPORT_MuxAlt2,
                                                   /* Pin Control Register fields [15:0] are not locked */
                                                   kPORT_UnlockRegister};
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* PORTB2 is configured as I2C0_SCL */
    PORT_SetPinConfig(PORTB, 2U, &portb2_config);
    /* PORTB3 is configured as I2C0_SDA */
    PORT_SetPinConfig(PORTB, 3U, &portb3_config);

    /*
     * masterConfig.baudRate_Bps = 100000U;
     * masterConfig.enableStopHold = false;
     * masterConfig.glitchFilterWidth = 0U;
     * masterConfig.enableMaster = true;
     */
    I2C_MasterGetDefaultConfig(&masterConfig);

    masterConfig.baudRate_Bps = I2C_BAUDRATE;
    sourceClock               = I2C_MASTER_CLK_FREQ;


    status = I2C_RTOS_Init(&master_rtos_handle, i2c_to_use, &masterConfig, sourceClock);
    if (status != kStatus_Success)
    {
        PRINTF("I2C master: error during init, %d", status);
    }
    memset(&g_masterXfer, 0, sizeof(g_masterXfer));

    g_i2c_sem = xSemaphoreCreateMutex();
}

boolean_t i2c_write(I2C_Type* i2c_to_use ,uint8_t master_slave_addrs, uint16_t subaddress, uint8_t subsize, uint8_t bus[], uint16_t size)
{
    xSemaphoreTake(g_i2c_sem,portMAX_DELAY);
    status_t state = FALSE;

    g_masterXfer.slaveAddress   = master_slave_addrs;
    g_masterXfer.direction      = kI2C_Write;
    g_masterXfer.subaddress     = (uint32_t)subaddress;
    g_masterXfer.subaddressSize = subsize;
    g_masterXfer.data           = bus;
    g_masterXfer.dataSize       = size;
    g_masterXfer.flags          = kI2C_TransferDefaultFlag;

    state = I2C_MasterTransferBlocking(i2c_to_use, &g_masterXfer);
    if (state != kStatus_Success)
    {
        PRINTF("I2C master: error during read transaction, %d", state);
    }
    xSemaphoreGive(g_i2c_sem);

    return ~state;
}
boolean_t i2c_read(I2C_Type* i2c_to_use ,uint8_t master_slave_addrs, uint16_t subaddress, uint8_t subsize, uint8_t bus[], uint16_t size)
{
    xSemaphoreTake(g_i2c_sem,portMAX_DELAY);
    status_t state = FALSE;
    g_masterXfer.slaveAddress   = master_slave_addrs;
    g_masterXfer.direction      = kI2C_Read;
    g_masterXfer.subaddress     = (uint32_t)subaddress;
    g_masterXfer.subaddressSize = subsize;
    g_masterXfer.data           = bus;
    g_masterXfer.dataSize       = size;
    g_masterXfer.flags          = kI2C_TransferDefaultFlag;


    state = I2C_MasterTransferBlocking(i2c_to_use, &g_masterXfer);
    if (state != kStatus_Success)
    {
        PRINTF("I2C master: error during read transaction, %d", state);
    }
    xSemaphoreGive(g_i2c_sem);

    return ~state;
}
