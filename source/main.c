/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    PWM.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "fsl_ftm.h"
#include "MUSIC_gen.h"
#include "MUSIC_album.h"
#include "FTM_pwm.h"
#include "task.h"
#include "FreeRTOS.h"
#include "LCD_nokia.h"
#include "SPI.h"
#include "Tamagotchi_skin.h"
#include "Tamagotchi_char.h"
#include "semphr.h"
#include "GPIO_ctrl.h"
#include "fsl_gpio.h"
/* TODO: insert other definitions and declarations here. */


#define MAX_BAR 7u
#define DELAY_BARS 10000u
#define GET_ARGS(args,type) *((type*)args)

typedef enum
{
	select_pet,
	main_menu,
	game_menu,
	music_menu,
	dead_pet
}game_state_t;

typedef enum
{
	song1,
	song2,
	song3,
	song4
}music_state_t;

extern const song_t scale_song;
extern const song_t Aura_Lee_song;
extern const song_t Away_in_the_Deep_Forest_song;
extern const song_t Song_of_the_storm_song;
extern const song_t Game_over_song;

extern tamagotchi_t Robot_skin;
extern tamagotchi_t Billotchi_skin;
static emotions_state_t emotion = GENERAL;

static uint16_t total_bars_health = MAX_BAR;
static uint16_t total_bars_happiness = MAX_BAR;
static uint8_t flag_bar_health = 0;
static uint8_t flag_bar_happiness = 0;
static menu_state_t menu_state = food;
static game_state_t game_state = select_pet;
static music_state_t music_state = song1;
static uint8_t button_selection = 0;
static uint8_t select_pet_flag = 0;
/*
 * @brief   Application entry point.
 */


void music_task(void *pvParameters);
void state_bars_task(void *pvParameters);
void initialize(void *pvParameters);
void menu_select(void);
void print_control_task(void *pvParameters);

void b0_callback(void);
void b1_callback(void);
void b2_callback(void);
void b3_callback(void);
void b4_callback(void);
void Tamagotchi_char(void *pvParameters);

int main(void)
{
    uint32_t time;

//    LCD_nokia_happiness();
//    LCD_nokia_health();
//    LCD_nokia_health_bars(total_bars_health);
//    LCD_nokia_happiness_bars(total_bars_happiness);
//
//    total_bars_happiness = 5;
//    total_bars_health = 3;
//    LCD_nokia_happiness_bars(total_bars_happiness);
//    LCD_nokia_health_bars(total_bars_health);
//
//    LCD_nokia_menu(menu_state);

 	xTaskCreate(initialize, "INIT", 100, NULL, 10, NULL);
 	xTaskCreate(print_control_task, "PRINT", 200, NULL,3, NULL);
 	xTaskCreate(state_bars_task, "BARS", 200, NULL,3, NULL);
	xTaskCreate(music_task, "MUSIC", 100, (void*)(&time),9, NULL);
	xTaskCreate(Tamagotchi_char, "TAMAGOTCHI CHAR", 100, NULL, 1, NULL);

    vTaskStartScheduler();
    while(1)
    {

    }
    return 0 ;
}

void state_bars_task(void *pvParameters)
{
    while(1)
    {
    	if(flag_bar_happiness && (total_bars_happiness <= MAX_BAR))
    		total_bars_happiness++;
    	else if (total_bars_happiness >0)
    		total_bars_happiness--; //if bars equals zero pet dies

    	if(flag_bar_health && (total_bars_health <= MAX_BAR))
    		total_bars_health++;
    	else if (total_bars_health >0)
    		total_bars_health--; //if bars equals zero pet dies


        vTaskDelay(pdMS_TO_TICKS(5000));
    }

}

void music_task(void *pvParameters)
{
    uint32_t time = GET_ARGS(pvParameters,uint32_t);
    while(1)
    {
        time = MUSIC_playback();
        vTaskDelay((time)/portTICK_PERIOD_MS);
    }

}
void initialize(void *pvParameters)
{
    MUSIC_initialize();
    MUSIC_changeSong(Song_of_the_storm_song);
    tamagotchi_set_pet(Billotchi_skin);

    SPI_config();
    LCD_nokia_init();
    LCD_nokia_clear();
    GPIO_init();
	NVIC_SetPriority(PORTC_IRQn, 0x3);
	EnableIRQ(PORTC_IRQn);
    GPIO_callback_assign(B0, b0_callback);
    GPIO_callback_assign(B1, b1_callback);
    GPIO_callback_assign(B2, b2_callback);
    GPIO_callback_assign(B3, b3_callback);
    GPIO_callback_assign(B4, b4_callback);


    vTaskSuspend(NULL);
}
void Tamagotchi_char(void *pvParameters)
{
    uint8_t a = 0;
    while(1)
    {
    	switch(game_state)
    	{
    	case select_pet:
    		tamagotchi_clear();
    		tamagotchi_move_center();
    		TAMAGOTCHI_FSM_sequency();
    		break;
    	case main_menu:
            tamagotchi_clear();
            tamagotchi_random_move();
            TAMAGOTCHI_FSM_sequency();
    		break;
    	case game_menu:
    		break;
    	case music_menu:
            tamagotchi_clear();
            tamagotchi_random_move();
            TAMAGOTCHI_FSM_sequency();
    		break;
    	case dead_pet:
    		break;
    	}
        if(a)
        {
            tamagotchi_set_emotion(emotion);
            a = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void print_control_task(void *pvParameters)
{
	uint8_t select_pet_text[] = "Select your pet";
	uint8_t select_pet_text_e[] = "                ";
	uint8_t select_music_text_e[] = "           ";
    while(1)
    {
		LCD_nokia_goto_xy(0, 0);
		LCD_nokia_send_string(select_music_text_e);
		if(select_pet_flag != 0)
		{
			LCD_nokia_health_bars(total_bars_health);
			LCD_nokia_happiness_bars(total_bars_happiness);
		}
    	switch(game_state)
		{
    	case select_pet:
    		LCD_nokia_goto_xy(0, 0);
    		LCD_nokia_send_string(select_pet_text);
    		break;
    	case main_menu:
    		if(select_pet_flag != 0)
    			LCD_nokia_send_string(select_pet_text_e);
    		LCD_nokia_menu(menu_state);
    		break;
    	case game_menu:
    		break;
    	case music_menu:
    		LCD_nokia_goto_xy(0, 0);
    		LCD_nokia_send_string(songs_to_play[music_state]);
			break;
    	case dead_pet:
			break;
		}
    	vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void menu_select(void)
{
	switch(menu_state)
	{
	case food:
		tamagotchi_set_emotion(EATING);
		break;
	case sleep:
		tamagotchi_set_emotion(SLEEPING);
		break;
	case water:
		tamagotchi_set_emotion(BATH);
		break;
	case play:
		tamagotchi_set_emotion(FLYING);
		game_state = game_menu;
		break;
	case music:
		tamagotchi_set_emotion(MUSIC);
		game_state = music_menu;
		break;
	case restroom:
		break;
	default:
		break;
	}
}


/** Boton select */
void b0_callback(void)
{
	switch(game_state)
	{
	case select_pet:
		if(button_selection < 1)
		{
			button_selection++;
			tamagotchi_set_pet(Robot_skin);
		}

		else if(button_selection == 1)
		{
			button_selection = 0;
			tamagotchi_set_pet(Billotchi_skin);
		}
		break;
	case main_menu:
		if(menu_state<restroom)
			menu_state++;
		else
			menu_state = food;
		break;
	case game_menu:
		break;
	case music_menu:
		if(music_state < song4)
			music_state++;
		else
			music_state = 0;
		break;
	case dead_pet:
		break;
	}
}
/** Boton enter */
void b1_callback(void)
{
	switch(game_state)
	{
	case select_pet:
		button_selection = 0;
		game_state = main_menu;
		select_pet_flag = 1;
		break;
	case main_menu:
		select_pet_flag = 0;
		menu_select();
		//if menu different from food change state
		break;
	case game_menu:
		break;
	case music_menu:
		switch(music_state)
		{
		case song1:
			MUSIC_changeSong(Aura_Lee_song);
			break;
		case song2:
			MUSIC_changeSong(Away_in_the_Deep_Forest_song);
			break;
		case song3:
			MUSIC_changeSong(Song_of_the_storm_song);
			break;
		case song4:
			MUSIC_changeSong(Game_over_song);
			break;
		default:
			break;
		}
		break;
	case dead_pet:
		break;
	}
}
/** Boton back */
void b2_callback(void)
{
	switch(game_state)
	{
	case select_pet:
		button_selection = 0;
		game_state = main_menu;

		break;
	case main_menu:
		break;
	case game_menu:
		game_state = main_menu;
		break;
	case music_menu:
		game_state = main_menu;
		break;
	case dead_pet:
		break;
	}
}
void b3_callback(void)
{
	//volume down
}
void b4_callback(void)
{
	//volume up
}
