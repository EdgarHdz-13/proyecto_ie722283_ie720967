/*
 * i2c_tools.h
 *
 *  Created on: 1 abr 2022
 *      Author: edgar
 */

#ifndef I2C_TOOLS_H_
#define I2C_TOOLS_H_

#include "Bits.h"
#include "fsl_i2c_freertos.h"
#include "MK66F18.h"
#include "FreeRTOS.h"

/** i2c values */
#define I2C_DATA_LENGTH             33U
#define I2C_BAUDRATE                400000U
#define I2C_MASTER_CLK_FREQ         CLOCK_GetFreq(I2C0_CLK_SRC)


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  i2c init values.

     \param[in]     void.
     \return        void.
 */
void i2c_init(I2C_Type* i2c_to_use);
boolean_t i2c_write(I2C_Type* i2c_to_use ,uint8_t master_slave_addrs, uint16_t subaddress, uint8_t subsize, uint8_t bus[], uint16_t size);
boolean_t i2c_read(I2C_Type* i2c_to_use ,uint8_t master_slave_addrs, uint16_t subaddress, uint8_t subsize, uint8_t bus[], uint16_t size);

#endif /* I2C_TOOLS_H_ */
