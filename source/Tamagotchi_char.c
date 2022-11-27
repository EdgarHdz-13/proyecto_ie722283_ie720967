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
#include "Bits.h"

static tamagotchi_t pet;
static uint8_t x=34,y=2;
static emotions_state_t selector = HAPPY;
typedef struct
{
    emotions_state_t emotion;
    void (*fptrPrint)(tamagotchi_t,uint8_t,emotions_state_t);
    emotions_state_t next[7];
}Tamagotchi_state_t;

const Tamagotchi_state_t TAMAGOTCHI_FSM_Moore[7] =
{
        {GENERAL,           &tamagotchi_print,{GENERAL,HAPPY,SAD,DISSAPOINTMENT,ANGRY,NO,MUSIC}},//GERNERAL
        {HAPPY,             &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL}},//HAPPY
        {SAD,               &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL}},//SAD
        {DISSAPOINTMENT,    &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL}},//DISSAPOINTMENT
        {ANGRY,             &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL}},//ANGRY
        {NO,                &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL}},//NO
        {MUSIC,             &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL}},//MUSIC
};
void TAMAGOTCHI_FSM_sequency()
{
    /** Initial state of FSM */
    static emotions_state_t current_state = GENERAL;
    static uint8_t cont = 0;

    switch(current_state)
    {
    case GENERAL:
        if(cont+1 > pet.state.general_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case HAPPY:
        if(cont+1 > pet.state.happy_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case SAD:
        if(cont+1 > pet.state.happy_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case DISSAPOINTMENT:
        if(cont+1 > pet.state.dissapointment_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case ANGRY:
        if(cont+1 > pet.state.angry_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case NO:
        if(cont+1 > pet.state.no_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case MUSIC:
        if(cont+1 > pet.state.music_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    }
    /** Use the actual function pointer  */
    TAMAGOTCHI_FSM_Moore[current_state].fptrPrint(pet,cont,current_state);
    cont++;
}

void tamagotchi_print(tamagotchi_t pet,uint8_t cont, emotions_state_t emotion)
{
    uint8_t conty=0,contx=0,posx = cont<<4,posy = emotion<<1;
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
void tamagotchi_set_pet(tamagotchi_t tamagotchi_pet)
{
    pet = tamagotchi_pet;
}


