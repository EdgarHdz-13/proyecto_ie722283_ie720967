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
/* TODO: insert other definitions and declarations here. */
extern const song_t scale_song;
extern const song_t Aura_Lee_song;
extern const song_t Away_in_the_Deep_Forest_song;
extern const song_t Song_of_the_storm_song;

extern const uint8_t Robot[];
extern tamagotchi_t Robot_skin;
/*
 * @brief   Application entry point.
 */
void delay(void)
{
	for(int i=0;i<200000;i++){};
}
void music_task(void *pvParameters)
{
    uint32_t time;
    while(1)
    {
        time = MUSIC_playback();
        vTaskDelay(time/portTICK_PERIOD_MS);
    }

}
void initialize(void *pvParameters)
{
    MUSIC_initialize();
    MUSIC_changeSong(Song_of_the_storm_song);
    SPI_config();
    LCD_nokia_init();

    LCD_nokia_clear();


    vTaskSuspend(NULL);
}
void Tamagotchi_char(void *pvParameteres)
{
    emotions_state_t emotion = GENERAL;
    uint8_t a = 0;
    tamagotchi_set_pet(Robot_skin);
    while(1)
    {
        if(a)
        {
            tamagotchi_set_emotion(emotion);
            a = 0;
        }
        TAMAGOTCHI_FSM_sequency();
        vTaskDelay(pdMS_TO_TICKS(1000));
//        tamagotchi_print(Robot_skin,0,1);
//        vTaskDelay(pdMS_TO_TICKS(1000));
//        tamagotchi_print(Robot_skin,0,2);
//        vTaskDelay(pdMS_TO_TICKS(1000));
//        tamagotchi_print(Robot_skin,0,3);
//        vTaskDelay(pdMS_TO_TICKS(1000));
//        tamagotchi_print(Robot_skin,0,4);
//        vTaskDelay(pdMS_TO_TICKS(1000));
//        tamagotchi_print(Robot_skin,0,5);
//        vTaskDelay(pdMS_TO_TICKS(1000));
//        tamagotchi_print(Robot_skin,0,6);
//        vTaskDelay(pdMS_TO_TICKS(1000));
//        tamagotchi_print(Robot_skin,1,6);
//        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{

 	xTaskCreate(initialize, "INIT", 100, NULL, 10, NULL);
	xTaskCreate(music_task, "MUSIC", 100, NULL,2, NULL);
	xTaskCreate(Tamagotchi_char, "TAMAGOTCHI CHAR", 100, NULL, 1, NULL);
    PRINTF("Hello World\n");
    vTaskStartScheduler();


    while(1)
    {
        delay();

    }
    return 0 ;
}

