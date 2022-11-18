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

void tamagotchi_print(tamagotchi_t pet,uint8_t posx, uint8_t posy)
{
    uint8_t conty=0,contx=0;
    posx = posx<<4;
    posy = posy<<1;
    for(conty = 0;conty < TAMAGOTCHI_HEIGHT;conty++)
    {
        for (contx = 0; contx < TAMAGOTCHI_LENGTH; contx++) {
            LCD_nokia_goto_xy(x+contx, y+conty);
            LCD_nokia_write_byte(LCD_DATA,(uint8_t)((*(pet.skin+(posx+contx)+((posy+conty)<<5))))); //y<<5 == y*32
        }
    }
}

void tamagotchi_move(uint8_t posx, uint8_t posy)
{
    x = posx;
    y = posy;
}


