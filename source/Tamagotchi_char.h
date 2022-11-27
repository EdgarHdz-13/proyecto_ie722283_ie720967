/*
 * Tamagotchi_char.h
 *
 *  Created on: 14 nov 2022
 *      Author: Edgar
 */
/*
 *      THIS PROGRAM ONLY WORKS WITH 16x16 tamagotchi's
 *
 */
#ifndef TAMAGOTCHI_CHAR_H_
#define TAMAGOTCHI_CHAR_H_

#include "stdint.h"
#define CENTER_X    34
#define CENTER_Y    2

typedef enum
{
   GENERAL,
   HAPPY,
   SAD,
   DISSAPOINTMENT,
   ANGRY,
   NO,
   MUSIC
}emotions_state_t;
typedef struct
{
    emotions_state_t current_state;
    uint8_t general_size;
    uint8_t happy_size;
    uint8_t sad_size;
    uint8_t dissapointment_size;
    uint8_t angry_size;
    uint8_t no_size;
    uint8_t music_size;
}emotions_t;
typedef struct
{
    uint8_t     *skin;
    emotions_t  state;
    uint8_t     hungry;
    uint16_t    length;
}tamagotchi_t;


void TAMAGOTCHI_FSM_sequency();
void tamagotchi_print(tamagotchi_t pet,uint8_t cont, uint8_t emotion);
void tamagotchi_move(uint8_t posx, uint8_t posy);
void tamagotchi_set_pet(tamagotchi_t tamagotchi_pet);

#endif /* TAMAGOTCHI_CHAR_H_ */
