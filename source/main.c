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
/* TODO: insert other definitions and declarations here. */


#define MAX_BAR 7u
#define DELAY_BARS 30000u
#define GET_ARGS(args,type) *((type*)args)

extern const song_t scale_song;
extern const song_t Aura_Lee_song;
extern const song_t Away_in_the_Deep_Forest_song;
extern const song_t Song_of_the_storm_song;

extern tamagotchi_t Robot_skin;
extern tamagotchi_t Billotchi_skin;

static uint16_t total_bars_health = MAX_BAR;
static uint16_t total_bars_happiness = MAX_BAR;
static uint8_t flag_bar_health = 0;
static uint8_t flag_bar_happiness = 0;
static menu_state_t menu_state = food;

/*
 * @brief   Application entry point.
 */
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


    vTaskSuspend(NULL);
}
void Tamagotchi_char(void *pvParameters)
{
    emotions_state_t emotion = GENERAL;
    uint8_t a = 0;
    tamagotchi_set_pet(Billotchi_skin);
    while(1)
    {
        if(a)
        {
            tamagotchi_set_emotion(emotion);
            a = 0;
        }
        tamagotchi_clear();
        tamagotchi_random_move();
        TAMAGOTCHI_FSM_sequency();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void state_bars_task(void *pvParameters);
void menu_task(void *pvParameters);

int main(void)
{
    uint32_t time;


    SPI_config();
    LCD_nokia_init();
    LCD_nokia_clear();

    LCD_nokia_happiness();
    LCD_nokia_health();
    LCD_nokia_health_bars(total_bars_health);
    LCD_nokia_happiness_bars(total_bars_happiness);

    total_bars_happiness = 5;
    total_bars_health = 3;
    LCD_nokia_happiness_bars(total_bars_happiness);
    LCD_nokia_health_bars(total_bars_health);

    LCD_nokia_menu(menu_state);

 	xTaskCreate(initialize, "INIT", 100, NULL, 10, NULL);


 	xTaskCreate(menu_task, "menu", 200, NULL,3, NULL);

	xTaskCreate(music_task, "MUSIC", 100, (void*)(&time),9, NULL);n
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
    	if(flag_bar_happiness && (flag_bar_happiness <= MAX_BAR))
    		total_bars_happiness++;
    	else
    		total_bars_happiness--; //if bars equals zero pet dies

    	if(flag_bar_health && (flag_bar_health <= MAX_BAR))
    		total_bars_health++;
    	else
    		total_bars_health--; //if bars equals zero pet dies

        vTaskDelay(pdMS_TO_TICKS(DELAY_BARS));
    }

}

void menu_task(void *pvParameters)
{
	uint8_t i = 0;
	while(1)
	{
		LCD_nokia_menu(i);
		i++;
		if(i == 6)
			i = 0;
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
