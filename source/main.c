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
#define GET_ARGS(args,type) *((type*)args)
#define DEADSCENE_DELAY         500
extern const song_t scale_song;
extern const song_t Aura_Lee_song;
extern const song_t Away_in_the_Deep_Forest_song;
extern const song_t Song_of_the_storm_song;
extern const song_t Game_over_song;

extern tamagotchi_t Robot_skin;
extern tamagotchi_t Billotchi_skin;
extern deadscene_t deadscene_struct;

SemaphoreHandle_t xBinarySemDeadscene = NULL;

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
    MUSIC_changeSong(Game_over_song);
    SPI_config();
    LCD_nokia_init();

    LCD_nokia_clear();


    vTaskSuspend(NULL);
}
void Tamagotchi_char(void *pvParameters)
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
        tamagotchi_clear();
        //tamagotchi_random_move();
        TAMAGOTCHI_FSM_sequency();
        xSemaphoreGive(xBinarySemDeadscene);
        vTaskSuspend(NULL);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Tamagotchi_deadscene(void *pvParameters)
{
    uint16_t cont = 0;
    uint8_t message[] = "Quieres continuar?";
    while(1)
    {
        xSemaphoreTake(xBinarySemDeadscene,portMAX_DELAY);
        MUSIC_changeSong(Game_over_song);
        tamagotchi_clear();
        tamagotchi_move_center();
        tamagotchi_set_emotion(DYING);
        TAMAGOTCHI_FSM_sequency();
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        tamagotchi_clear();
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        TAMAGOTCHI_FSM_sequency();
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        tamagotchi_clear();
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        TAMAGOTCHI_FSM_sequency();
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        tamagotchi_clear();
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        TAMAGOTCHI_FSM_sequency();
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        tamagotchi_clear();
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        while(1)
        {
            if(cont >= deadscene_struct.length)
            {
                cont = 0;
            }
            LCD_nokia_goto_xy(0, 0);
            LCD_nokia_bitmap((deadscene_struct.deadscene+(cont*504)));
            cont++;
            vTaskDelay(pdMS_TO_TICKS(DEADSCENE_DELAY));
        }

    }
}

int main(void)
{
    uint32_t time;
    xBinarySemDeadscene = xSemaphoreCreateBinary();
 	xTaskCreate(initialize, "INIT", 100, NULL, 10, NULL);
 	xTaskCreate(Tamagotchi_char, "TAMAGOTCHI CHAR", 100, NULL, 2, NULL);
	xTaskCreate(music_task, "MUSIC", 100, (void*)(&time),9, NULL);
	xTaskCreate(Tamagotchi_deadscene, "TAMAGOTCHI DEADSCENE", 100, NULL, 8, NULL);

    vTaskStartScheduler();
    while(1)
    {

    }
    return 0 ;
}

