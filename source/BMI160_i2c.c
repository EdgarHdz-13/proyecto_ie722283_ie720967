/*
 * BMI160_i2c.c
 *
 *  Created on: Oct 20, 2022
 *      Author: edgar
 */
#include "BMI160_i2c.h"
#include "i2c_tools.h"

#include <stdio.h>
#include <math.h>

#define ARRAY_X     0u
#define ARRAY_Y     1u
#define ARRAY_Z     2u

static float g_acc_var[3] = {0.0,0.0,0.0};
static float g_gyr_var[3] = {0.0,0.0,0.0};

void BMI160_read_status(uint8_t bus[])
{
    i2c_read(I2C_BMI_MASTER, I2C_BMI160_MASTER_SLAVE_ADDR_7BIT, PMU_REGISTER, DIR_SIZE, bus, CONFIG_SIZE);
}

void BMI160_cmd(uint8_t cmd)
{
    uint8_t Txbus[1] = {cmd};
    i2c_write(I2C_BMI_MASTER, I2C_BMI160_MASTER_SLAVE_ADDR_7BIT, CMD_REGISTER, DIR_SIZE, Txbus, CONFIG_SIZE);
}

void BMI160_accel_config(uint8_t flags, uint8_t range)
{
    uint8_t Txbus[2] = {flags,range};
    i2c_write(I2C_BMI_MASTER, I2C_BMI160_MASTER_SLAVE_ADDR_7BIT, ACC_CONFIG_REGISTER, DIR_SIZE, Txbus, TWO_CONFIG_SIZE);
}

void BMI160_read_accel(int8_t bus[])
{
    i2c_read(I2C_BMI_MASTER, I2C_BMI160_MASTER_SLAVE_ADDR_7BIT, ACC_X_LSB, DIR_SIZE, bus, ALL_DATA);
}

acc_data_t BMI160_get_accel(void)
{
    acc_data_t acc_struct;
    int8_t rxbuff[6];
    BMI160_read_accel(rxbuff);

    acc_struct.acc_x = (float)(rxbuff[0] | rxbuff[1] << DATA_OFFSET)*ACC_FACTOR_2g;
    acc_struct.acc_y = (float)(rxbuff[2] | rxbuff[3] << DATA_OFFSET)*ACC_FACTOR_2g;
    acc_struct.acc_z = (float)(rxbuff[4] | rxbuff[5] << DATA_OFFSET)*ACC_FACTOR_2g;

    acc_struct.acc_x = fabsf(acc_struct.acc_x) < g_acc_var[ARRAY_X] ? 0 : acc_struct.acc_x;
    acc_struct.acc_y = fabsf(acc_struct.acc_y) < g_acc_var[ARRAY_Y] ? 0 : acc_struct.acc_y;
    acc_struct.acc_z = fabsf(acc_struct.acc_z) < g_acc_var[ARRAY_Z] ? 0 : acc_struct.acc_z;

    return acc_struct;
}

void BMI160_gyr_config(uint8_t flags, uint8_t range)
{
    uint8_t Txbus[2] = {flags,range};
    i2c_write(I2C_BMI_MASTER, I2C_BMI160_MASTER_SLAVE_ADDR_7BIT, GYR_CONFIG_REGISTER, DIR_SIZE, Txbus, TWO_CONFIG_SIZE);
}
void BMI160_read_gyr(int8_t bus[])
{
    i2c_read(I2C_BMI_MASTER, I2C_BMI160_MASTER_SLAVE_ADDR_7BIT, GYR_X_LSB, DIR_SIZE, bus, ALL_DATA);
}

gyr_data_t BMI160_get_gyr(void)
{
    gyr_data_t gyr_struct;
    int8_t rxbuff[6];
    BMI160_read_gyr(rxbuff);

    gyr_struct.gyr_x = (float)(rxbuff[0] | rxbuff[1] << DATA_OFFSET)*GYR_FACTOR_125;
    gyr_struct.gyr_y = (float)(rxbuff[2] | rxbuff[3] << DATA_OFFSET)*GYR_FACTOR_125;
    gyr_struct.gyr_z = (float)(rxbuff[4] | rxbuff[5] << DATA_OFFSET)*GYR_FACTOR_125;

    gyr_struct.gyr_x = fabsf(gyr_struct.gyr_x) < g_gyr_var[ARRAY_X] ? 0 : gyr_struct.gyr_x;
    gyr_struct.gyr_y = fabsf(gyr_struct.gyr_y) < g_gyr_var[ARRAY_Y] ? 0 : gyr_struct.gyr_y;
    gyr_struct.gyr_z = fabsf(gyr_struct.gyr_z) < g_gyr_var[ARRAY_Z] ? 0 : gyr_struct.gyr_z;

    return gyr_struct;
}


void BMI160_read_err(uint8_t bus[])
{
    i2c_read(I2C_BMI_MASTER, I2C_BMI160_MASTER_SLAVE_ADDR_7BIT, ERR_REGISTER, DIR_SIZE, bus, 1);
}

void BMI160_calibrate_gyr_acc(uint16_t samples,boolean_t var_deadzone)
{
    acc_data_t acc,aprom = {0.0,0.0,0.0},a2prom = {0.0,0.0,0.0},adeadzone = {0.0,0.0,0.0};
    gyr_data_t gyr,gprom = {0.0,0.0,0.0},g2prom = {0.0,0.0,0.0},gdeadzone = {0.0,0.0,0.0};
    uint16_t cont = 0;
    if(!var_deadzone)
    {
        while(cont < samples)
        {
            acc = BMI160_get_accel();
            gyr = BMI160_get_gyr();
            cont++;
            aprom.acc_x += acc.acc_x;
            aprom.acc_y += acc.acc_y;
            aprom.acc_z += acc.acc_z;
            gprom.gyr_x += gyr.gyr_x;
            gprom.gyr_y += gyr.gyr_y;
            gprom.gyr_z += gyr.gyr_z;

            a2prom.acc_x += acc.acc_x*acc.acc_x;
            a2prom.acc_y += acc.acc_y*acc.acc_y;
            a2prom.acc_z += acc.acc_z*acc.acc_z;
            g2prom.gyr_x += gyr.gyr_x*gyr.gyr_x;
            g2prom.gyr_y += gyr.gyr_y*gyr.gyr_y;
            g2prom.gyr_z += gyr.gyr_z*gyr.gyr_z;
            if(cont >= samples)
            {
                /* E^2x */
                aprom.acc_x = aprom.acc_x/cont;
                aprom.acc_y = aprom.acc_y/cont;
                aprom.acc_z = aprom.acc_z/cont;
                gprom.gyr_x = gprom.gyr_x/cont;
                gprom.gyr_y = gprom.gyr_y/cont;
                gprom.gyr_z = gprom.gyr_z/cont;

                aprom.acc_x *= aprom.acc_x;
                aprom.acc_y *= aprom.acc_y;
                aprom.acc_z *= aprom.acc_z;
                gprom.gyr_x *= gprom.gyr_x;
                gprom.gyr_y *= gprom.gyr_y;
                gprom.gyr_z *= gprom.gyr_z;

                /* Ex^2 */
                a2prom.acc_x = a2prom.acc_x/cont;
                a2prom.acc_y = a2prom.acc_y/cont;
                a2prom.acc_z = a2prom.acc_z/cont;
                g2prom.gyr_x = g2prom.gyr_x/cont;
                g2prom.gyr_y = g2prom.gyr_y/cont;
                g2prom.gyr_z = g2prom.gyr_z/cont;

                /* Ex^2 - E^2x */
                g_acc_var[ARRAY_X] = fabsf(a2prom.acc_x - aprom.acc_x)*4;
                g_acc_var[ARRAY_Y] = fabsf(a2prom.acc_y - aprom.acc_x)*4;
                g_acc_var[ARRAY_Z] = fabsf(a2prom.acc_z - aprom.acc_x)*4;
                g_gyr_var[ARRAY_X] = fabsf(g2prom.gyr_x - gprom.gyr_x)*4;
                g_gyr_var[ARRAY_Y] = fabsf(g2prom.gyr_y - gprom.gyr_y)*4;
                g_gyr_var[ARRAY_Z] = fabsf(g2prom.gyr_z - gprom.gyr_z)*4;
            }
        }
    }
    else
    {
        while(cont < samples)
        {
            acc = BMI160_get_accel();
            gyr = BMI160_get_gyr();
            cont++;
            adeadzone.acc_x = adeadzone.acc_x < fabsf(acc.acc_x) ? fabsf(acc.acc_x) : adeadzone.acc_x;
            adeadzone.acc_y = adeadzone.acc_y < fabsf(acc.acc_y) ? fabsf(acc.acc_y) : adeadzone.acc_y;
            adeadzone.acc_z = adeadzone.acc_z < fabsf(acc.acc_z) ? fabsf(acc.acc_z) : adeadzone.acc_z;
            gdeadzone.gyr_x = gdeadzone.gyr_x < fabsf(gyr.gyr_x) ? fabsf(gyr.gyr_x) : gdeadzone.gyr_x;
            gdeadzone.gyr_y = gdeadzone.gyr_y < fabsf(gyr.gyr_y) ? fabsf(gyr.gyr_y) : gdeadzone.gyr_y;
            gdeadzone.gyr_z = gdeadzone.gyr_z < fabsf(gyr.gyr_z) ? fabsf(gyr.gyr_z) : gdeadzone.gyr_z;
        }
        g_acc_var[ARRAY_X] = adeadzone.acc_x + adeadzone.acc_x*DEADZONE_RESOLUTION;
        g_acc_var[ARRAY_Y] = adeadzone.acc_y + adeadzone.acc_y*DEADZONE_RESOLUTION;
        g_acc_var[ARRAY_Z] = adeadzone.acc_z + adeadzone.acc_z*DEADZONE_RESOLUTION;
        g_gyr_var[ARRAY_X] = gdeadzone.gyr_x + gdeadzone.gyr_x*DEADZONE_RESOLUTION;
        g_gyr_var[ARRAY_Y] = gdeadzone.gyr_y + gdeadzone.gyr_y*DEADZONE_RESOLUTION;
        g_gyr_var[ARRAY_Z] = gdeadzone.gyr_z + gdeadzone.gyr_z*DEADZONE_RESOLUTION;
    }
}

