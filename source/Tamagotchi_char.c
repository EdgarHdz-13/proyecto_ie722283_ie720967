/*
 * Tamagotchi_char.c
 *
 *  Created on: 14 nov 2022
 *      Author: Edgar
 *
 */
#include "Tamagotchi_char.h"
#include "Tamagotchi_skin.h"
#include "LCD_nokia.h"

#include "stdint.h"
static uint8_t x,y;

void tamagotchi_print(tamagotchi_t pet)
{
    uint8_t y=0,x=0;
    for(y = 0;y < TAMAGOTCHI_HEIGHT;y++)
    {
        for (x = 0; x < TAMAGOTCHI_LENGTH; x++) {
            LCD_nokia_goto_xy(x, y);
            LCD_nokia_write_byte(LCD_DATA,(uint8_t)((*pet.skin+x+(y<<5)))); //y<<5 == y*32
        }
    }
}


