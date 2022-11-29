/*
 * BMI160_i2c.h
 *
 *  Created on: 20 oct 2022
 *      Author: Edgar
 */

#ifndef BMI160_I2C_H_
#define BMI160_I2C_H_

#include "stdint.h"
#include "fsl_i2c.h"
#include "fsl_debug_console.h"
#include "Bits.h"

//If is used PTB2 = SCL, PTB3 = SDA in BMI160 pin 17 = SDA pin ,18 = SCL
#define I2C_BMI160_MASTER_SLAVE_ADDR_7BIT       0x68 //0110 1000
#define MASTERXFER_SIZE                         33U

#define I2C_BMI                                 I2C0
#define I2C_BMI_MASTER                          ((I2C_Type *)I2C_BMI_MASTER_BASE)
#define I2C_BMI_MASTER_BASE                     (I2C0_BASE)

#define ERR_REGISTER                            0x02
#define ACC_CONFIG_REGISTER                     0x40
#define ACC_RANGE_REGISTER                      0x41
#define GYR_CONFIG_REGISTER                     0x42
#define GYR_RANGE_REGISTER                      0x43
#define PMU_REGISTER                            0x03
#define CMD_REGISTER                            0x7E

#define ACC_X_LSB								0x12
#define ACC_X_MSB								0x13
#define ACC_Y_LSB								0x14
#define ACC_Y_MSB								0x15
#define ACC_Z_LSB								0x16
#define ACC_Z_MSB								0x17

#define ACC_NORMAL_CONFIG                       0x20
#define ACC_data_rate_100                       0x08
#define ACC_data_rate_800                       0x0B
#define ACC_data_rate_1600                      0x0C
#define ACC_ACC_US                              0x80
#define ACC_BWP_OSR2                            0x10
#define ACC_BWP_OSR4                            0x00

#define ACC_RANGE_2g                            0x03
#define ACC_RANGE_4g                            0x05
#define ACC_RANGE_8g                            0x08
#define ACC_RANGE_16g                            0x0C

#define GYR_X_LSB								0x0C
#define GYR_X_MSB								0x0D
#define GYR_Y_LSB								0x0E
#define GYR_Y_MSB								0x0F
#define GYR_Z_LSB								0x10
#define GYR_Z_MSB                               0x11

#define GYR_NORMAL_CONFIG                       0x02
#define GYR_BWP_OSR2                            0x20
#define GYR_BWP_OSR4                            0x00

#define GYR_DATA_RATE_25                        0x06
#define GYR_DATA_RATE_100                       0x08
#define GYR_DATA_RATE_1600                      0x0C
#define GYR_DATA_RATE_3200                      0x0D

#define GYR_RANGE_2000                          0x00
#define GYR_RANGE_1000                          0x01
#define GYR_RANGE_500                           0x02
#define GYR_RANGE_250                           0x03
#define GYR_RANGE_125                           0x04

#define PMU_ACC_SUSPEND                         0x00 << 4
#define PMU_ACC_NORMAL                          0x01 << 4
#define PMU_ACC_LOWPOWER                        0x02 << 4

#define PMU_GYR_SUSPEND                         0x00 << 2
#define PMU_GYR_NORMAL                          0x01 << 2
#define PMU_GYR_LOWPOWER                        0x02 << 2

#define CMD_ACC_SET_PMU_MODE                    0x10
#define CMD_GYR_SET_PMU_MODE                    0x14
#define CMD_MAG_SET_PMU_MODE                    0x18
#define CMD_START_FOC                           0x03

#define CMD_SUSPEND                             0x00
#define CMD_NORMAL                              0x01
#define CMD_LOWPOWER                            0x02

#define ALL_DATA                                6u
#define CONFIG_SIZE                             1u
#define TWO_CONFIG_SIZE                         2u
#define DIR_SIZE                                1u
#define BUS_SIZE

#define ACC_FACTOR_2g                           0.000061035156f//range 2; 2/2^15
#define GYR_FACTOR_125                          0.003814697266f //range = 125; 125f/2^15

#define DATA_OFFSET                             8u

#define DEADZONE_RESOLUTION                     0.05f
typedef struct
{
    float acc_x;
    float acc_y;
    float acc_z;
}acc_data_t;
typedef struct
{
    float gyr_x;
    float gyr_y;
    float gyr_z;
}gyr_data_t;

void BMI160_read_err(uint8_t bus[]);

void BMI160_cmd(uint8_t cmd);

void BMI160_read_status(uint8_t bus[]);

void BMI160_accel_config(uint8_t flags, uint8_t range);

void BMI160_read_accel(int8_t bus[]);

acc_data_t BMI160_get_accel(void);

void BMI160_gyr_config(uint8_t flags, uint8_t range);

void BMI160_read_gyr(int8_t bus[]);

gyr_data_t BMI160_get_gyr(void);

/* var_deadzone = 0: Var; var_deadzone = 1: deadzone;*/
void BMI160_calibrate_gyr_acc(uint16_t samples,boolean_t var_deadzone);

#endif /* MAHONY_BMI160_I2C_H_ */
