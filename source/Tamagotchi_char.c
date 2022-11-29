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
#include "stdlib.h"

static tamagotchi_t pet;
static uint8_t x=32,y=2;
static emotions_state_t selector = GENERAL;
typedef struct
{
    emotions_state_t emotion;
    void (*fptrPrint)(tamagotchi_t,uint8_t,emotions_state_t);
    emotions_state_t next[12];
}Tamagotchi_state_t;

const Tamagotchi_state_t TAMAGOTCHI_FSM_Moore[12] =
{
        {GENERAL,           &tamagotchi_print,{GENERAL,HAPPY,SAD,DISSAPOINTMENT,ANGRY,NO,MUSIC,DYING,           EATING,SLEEPING,FLYING,BATH}},//GERNERAL
        {HAPPY,             &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,DYING,   EATING,SLEEPING,FLYING,BATH}},//HAPPY
        {SAD,               &tamagotchi_print,{GENERAL,GENERAL,SAD,GENERAL,GENERAL,GENERAL,GENERAL,DYING,       EATING,SLEEPING,FLYING,BATH}},//SAD
        {DISSAPOINTMENT,    &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,DYING,   EATING,SLEEPING,FLYING,BATH}},//DISSAPOINTMENT
        {ANGRY,             &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,DYING,   EATING,SLEEPING,FLYING,BATH}},//ANGRY
        {NO,                &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,DYING,   EATING,SLEEPING,FLYING,BATH}},//NO
        {MUSIC,             &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,MUSIC,DYING,     EATING,SLEEPING,FLYING,BATH}},//MUSIC
        {DYING,             &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,MUSIC,SAD,       EATING,SLEEPING,FLYING,BATH}},//DYING
        {EATING,            &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,MUSIC,DYING,     EATING,SLEEPING,FLYING,BATH}},//EATING
        {SLEEPING,          &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,MUSIC,DYING,     EATING,SLEEPING,FLYING,BATH}},//SLEEPING
        {FLYING,            &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,MUSIC,DYING,     EATING,SLEEPING,FLYING,BATH}},//FLYING
        {BATH,              &tamagotchi_print,{GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,GENERAL,MUSIC,DYING,     EATING,SLEEPING,FLYING,BATH}} //BATH
};
void TAMAGOTCHI_FSM_sequency(void)
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
        if(cont+1 > pet.state.sad_size)
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
    case DYING:
        if(cont+1 > pet.state.dying_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case EATING:
        if(cont+1 > pet.state.eating_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case SLEEPING:
        if(cont+1 > pet.state.sleeping_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case FLYING:
        if(cont+1 > pet.state.flying_size)
        {
            cont = 0;
            current_state = TAMAGOTCHI_FSM_Moore[current_state].next[selector];
        }
    break;
    case BATH:
        if(cont+1 > pet.state.bath_size)
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
            LCD_nokia_write_byte(LCD_DATA,(uint8_t)((*(pet.skin+(posx+contx)+((posy+conty)<<pet.length))))); //y<<5 == y*32
        }
    }
}
void tamagotchi_clear(void)
{
    uint8_t conty=0,contx=0;
    for(conty = 0;conty < TAMAGOTCHI_HEIGHT;conty++)
    {
        for (contx = 0; contx < TAMAGOTCHI_LENGTH; contx++) {
            LCD_nokia_goto_xy(x+contx, y+conty);
            LCD_nokia_write_byte(LCD_DATA,0x00); //y<<5 == y*32
        }
    }
}
void tamagotchi_move(uint8_t posx, uint8_t posy)
{
    x = posx;
    y = posy;
}
void tamagotchi_move_add(int8_t addx, int8_t addy)
{
    x = x+addx;
    y = y+addy;
}
void tamagotchi_move_center(void)
{
    tamagotchi_move(CENTER_X, CENTER_Y);
}
void tamagotchi_random_move(void)
{
    uint32_t random = rand() & 0x0F;
    if((random & 0x02) == (0x02) || (random & 0x04) == (0x04))
    {
        if((random & 0x01) == 0x01)      //Move right
        {
            if(x < UPPER_LIMIT_X)
            {
                tamagotchi_move_add(RANDOM_X_RIGHT_MOVE,0);
            }
        }
        else                            //Move left
        {
            if(x > LOWER_LIMIT_X)
            {
                tamagotchi_move_add(RANDOM_X_LEFT_MOVE,0);
            }
        }
    }
    if((random & 0x0E)  == (0x0E))
    {
        if((random & 0x01) == 0x01)      //Move up
        {
            if(y > UPPER_LIMIT_Y)
            {
                tamagotchi_move_add(0,RANDOM_Y_UP_MOVE);
            }
        }
        else                            //Move down
        {
            if(y < LOWER_LIMIT_Y)
            {
                tamagotchi_move_add(0,RANDOM_Y_DOWN_MOVE);
            }
        }
    }
}
void tamagotchi_set_pet(tamagotchi_t tamagotchi_pet)
{
    pet = tamagotchi_pet;
}
void tamagotchi_set_emotion(emotions_state_t emotion)
{
    selector = emotion;
}
uint8_t tamagotchi_get_x_position()
{
    return x;
}
uint8_t tamagotchi_get_y_position()
{
    return y;
}


