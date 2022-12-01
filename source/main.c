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
#include "fsl_clock.h"
#include "event_groups.h"
#include "mahony.h"
#include "BMI160_i2c.h"
#include "math.h"
#include "i2c_tools.h"
/* TODO: insert other definitions and declarations here. */

#define DEADSCENE_DELAY         500
#define MAX_BAR 7u
#define DELAY_BARS 10000u
#define GET_ARGS(args,type) *((type*)args)

#define PROM_NUMBER     1
#define PRINT  (1U << 0UL)
#define BARS  (1U << 1UL)
#define MUSIC   (1U << 2UL)
#define CHAR  (1U << 3UL)

#define MCG_IRCLK_DISABLE 0U                   /*!< MCGIRCLK disabled */
#define MCG_PLL_DISABLE 0U                     /*!< MCGPLLCLK disabled */
#define OSC_CAP0P 0U                           /*!< Oscillator 0pF capacitor load */
#define OSC_ER_CLK_DISABLE 0U                  /*!< Disable external reference clock */
#define SIM_CLKOUT_SEL_FLEXBUS_CLK 0U          /*!< CLKOUT pin clock select: FlexBus clock */
#define SIM_ENET_1588T_CLK_SEL_OSCERCLK_CLK 2U /*!< SDHC clock select: OSCERCLK clock */
#define SIM_ENET_RMII_CLK_SEL_EXTAL_CLK 0U     /*!< SDHC clock select: Core/system clock */
#define SIM_OSC32KSEL_RTC32KCLK_CLK 2U         /*!< OSC32KSEL select: RTC32KCLK clock (32.768kHz) */
#define SIM_PLLFLLSEL_IRC48MCLK_CLK 3U         /*!< PLLFLL select: IRC48MCLK clock */
#define SIM_PLLFLLSEL_MCGPLLCLK_CLK 1U         /*!< PLLFLL select: MCGPLLCLK clock */
#define SIM_SDHC_CLK_SEL_OSCERCLK_CLK 2U       /*!< SDHC clock select: OSCERCLK clock */
#define SIM_TRACE_CLK_SEL_CORE_SYSTEM_CLK 1U   /*!< Trace clock select: Core/system clock */
#define SIM_USB_CLK_120000000HZ 120000000U     /*!< Input SIM frequency for USB: 120000000Hz */

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

typedef struct
{
    acc_data_t macc;
    gyr_data_t mgyr;
    MahonyAHRSEuler_t output;
}mahony_params_t;

extern const song_t scale_song;
extern const song_t Aura_Lee_song;
extern const song_t Away_in_the_Deep_Forest_song;
extern const song_t Song_of_the_storm_song;
extern const song_t Game_over_song;

extern tamagotchi_t Robot_skin;
extern tamagotchi_t Billotchi_skin;

extern deadscene_t deadscene_struct;

SemaphoreHandle_t g_xSemaphore_mahony = NULL;
SemaphoreHandle_t xBinarySemDeadscene = NULL;
EventGroupHandle_t init_event;


static uint16_t total_bars_health = MAX_BAR;
static uint16_t total_bars_happiness = MAX_BAR;
static uint8_t flag_bar_health = 0;
static uint8_t flag_bar_happiness = 0;
static menu_state_t menu_state = food;
static game_state_t game_state = select_pet;
static music_state_t music_state = song1;
static uint8_t button_selection = 0;
static uint8_t select_pet_flag = 0;
static uint8_t flag_pet_actions = 0;
/*
 * @brief   Application entry point.
 */


void music_task(void *pvParameters);
void state_bars_task(void *pvParameters);
void initialize(void *pvParameters);
void menu_select(void);
void system_clock_120MHz(void);
void print_control_task(void *pvParameters);
void Tamagotchi_deadscene(void *pvParameters);
void Tamagotchi_char(void *pvParameters);

void b0_callback(void);
void b1_callback(void);
void b2_callback(void);
void b3_callback(void);
void b4_callback(void);

void mahony_angle(void *Pvparameters);
void read_sensor(void *Pvparameters);



int main(void)
{
     mahony_params_t parameter = {{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0}};
     uint32_t time;
     BOARD_InitBootPins();
     BOARD_InitBootClocks();
     BOARD_InitBootPeripherals();
     /* Init FSL debug console. */
     BOARD_InitDebugConsole();

    init_event = xEventGroupCreate();
    g_xSemaphore_mahony = xSemaphoreCreateBinary();
    xBinarySemDeadscene = xSemaphoreCreateBinary();

    xTaskCreate(mahony_angle,"mahony",      200, &parameter, 7,NULL);
    xTaskCreate(read_sensor, "read",               250, &parameter, 8, NULL);

 	xTaskCreate(initialize, "INIT", 100, NULL, 10, NULL);
 	xTaskCreate(print_control_task, "PRINT", 200, NULL,3, NULL);
 	xTaskCreate(state_bars_task, "BARS", 200, NULL,3, NULL);
	xTaskCreate(music_task, "MUSIC", 100, (void*)(&time),9, NULL);
	xTaskCreate(Tamagotchi_char, "TAMAGOTCHI CHAR", 100, NULL, 1, NULL);
	//xTaskCreate(Tamagotchi_deadscene, "TAMAGOTCHI DEADSCENE", 100, NULL, 8, NULL);

    vTaskStartScheduler();
    while(1)
    {

    }
    return 0 ;
}

void mahony_angle(void *Pvparameters)
{
    mahony_params_t* params = (mahony_params_t*) Pvparameters;
    while(1)
    {
        xSemaphoreTake(g_xSemaphore_mahony,portMAX_DELAY);

        /* For unknown reason when params arrives here it has values E-16 we don't know where
         * or how but this validation will work */
        params->macc.acc_x = fabsf(params->macc.acc_x) < 0.00001 ? 0 : params->macc.acc_x;
        params->macc.acc_y = fabsf(params->macc.acc_y) < 0.00001 ? 0 : params->macc.acc_y;
        params->macc.acc_z = fabsf(params->macc.acc_z) < 0.00001 ? 0 : params->macc.acc_z;

        params->mgyr.gyr_x = fabsf(params->mgyr.gyr_x) < 0.00001 ? 0 : params->mgyr.gyr_x;
        params->mgyr.gyr_y = fabsf(params->mgyr.gyr_y) < 0.00001 ? 0 : params->mgyr.gyr_y;
        params->mgyr.gyr_z = fabsf(params->mgyr.gyr_z) < 0.00001 ? 0 : params->mgyr.gyr_z;


        params->output = MahonyAHRSupdateIMU(params->mgyr.gyr_x, params->mgyr.gyr_y, params->mgyr.gyr_z, params->macc.acc_x, params->macc.acc_y, params->macc.acc_z);
        PRINTF("ROLL:%d, PITCH:%d, YAW:%d\n\r",(uint32_t)params->output.roll,(uint32_t)params->output.pitch,(uint32_t)params->output.yaw);
    }

}

void read_sensor(void *Pvparameters)
{
    acc_data_t acc,promacc={0.0,0.0,0.0};
    gyr_data_t gyr,promgyr={0.0,0.0,0.0};
    mahony_params_t* params = (mahony_params_t*)Pvparameters;
    uint8_t cont=0;

    while(1)
    {
        acc =  BMI160_get_accel();
        gyr = BMI160_get_gyr();

        promacc.acc_x += acc.acc_x;
        promacc.acc_y += acc.acc_y;
        promacc.acc_z += acc.acc_z;
        promgyr.gyr_x += gyr.gyr_x;
        promgyr.gyr_y += gyr.gyr_y;
        promgyr.gyr_z += gyr.gyr_z;
        cont++;
        if(cont >= PROM_NUMBER)
        {
            params->macc.acc_x = promacc.acc_x/cont;
            params->macc.acc_y = promacc.acc_y/cont;
            params->macc.acc_z = promacc.acc_z/cont;
            params->mgyr.gyr_x = promgyr.gyr_x/cont;
            params->mgyr.gyr_y = promgyr.gyr_y/cont;
            params->mgyr.gyr_z = promgyr.gyr_z/cont;
            promacc.acc_x = 0.0;
            promacc.acc_y = 0.0;
            promacc.acc_z = 0.0;
            promgyr.gyr_x = 0.0;
            promgyr.gyr_y = 0.0;
            promgyr.gyr_z = 0.0;
            xSemaphoreGive(g_xSemaphore_mahony);
            cont = 0;
        }
        vTaskDelay( 40 / portTICK_RATE_MS ); //For the filter it needs 4 samples, so we can collect the info 4*data rates
    }
}

void state_bars_task(void *pvParameters)
{
    const EventBits_t BitToWaitFor = BARS;
    xEventGroupWaitBits(init_event, BitToWaitFor, pdFALSE, pdFALSE, portMAX_DELAY);
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


        vTaskDelay(pdMS_TO_TICKS(10000));
    }

}

void music_task(void *pvParameters)
{
    uint32_t time = GET_ARGS(pvParameters,uint32_t);
    const EventBits_t BitToWaitFor = MUSIC;
    xEventGroupWaitBits(init_event, BitToWaitFor, pdFALSE, pdFALSE, portMAX_DELAY);
    while(1)
    {
        time = MUSIC_playback();
        vTaskDelay((time)/portTICK_PERIOD_MS);
    }

}
void initialize(void *pvParameters)
{
	//system_clock_120MHz();
	SPI_config();
    LCD_nokia_init();
    LCD_nokia_clear();
	MUSIC_initialize();
	MUSIC_changeSong(Song_of_the_storm_song);
    tamagotchi_set_pet(Billotchi_skin);

    GPIO_init();
	NVIC_SetPriority(PORTC_IRQn, 0x3);
	EnableIRQ(PORTC_IRQn);
    GPIO_callback_assign(B0, b0_callback);
    GPIO_callback_assign(B1, b1_callback);
    GPIO_callback_assign(B2, b2_callback);
    GPIO_callback_assign(B3, b3_callback);
    GPIO_callback_assign(B4, b4_callback);

    i2c_init(I2C_BMI_MASTER);

    BMI160_gyr_config(GYR_NORMAL_CONFIG| GYR_BWP_OSR4 | GYR_DATA_RATE_100, GYR_RANGE_125);
    BMI160_accel_config(ACC_BWP_OSR4 | ACC_data_rate_100, ACC_RANGE_2g);


    BMI160_cmd(CMD_ACC_SET_PMU_MODE | CMD_NORMAL);
    vTaskDelay( 5 / portTICK_RATE_MS );

    BMI160_cmd(CMD_GYR_SET_PMU_MODE | CMD_NORMAL);
    vTaskDelay( 80 / portTICK_RATE_MS );

    BMI160_cmd(CMD_START_FOC);
    vTaskDelay( 5 / portTICK_RATE_MS );

    BMI160_calibrate_gyr_acc(100,TRUE);

    xEventGroupSetBits(init_event,PRINT | BARS | MUSIC | CHAR );

    vTaskSuspend(NULL);
}
void Tamagotchi_char(void *pvParameters)
{
    const EventBits_t BitToWaitFor = CHAR;
    xEventGroupWaitBits(init_event, BitToWaitFor, pdFALSE, pdFALSE, portMAX_DELAY);
    while(1)
    {
    	switch(game_state)
    	{
    	case select_pet:
    		tamagotchi_clear();
    		tamagotchi_move_center();
    		break;
    	case main_menu:
            tamagotchi_clear();
            if(flag_pet_actions)
            {
                tamagotchi_move_center();
            }
            else
            {
                tamagotchi_random_move();
            }
    		break;
    	case game_menu:
    		break;
    	case music_menu:
            tamagotchi_clear();
            tamagotchi_move_center();
    		break;
    	case dead_pet:
    		break;
    	}
    	TAMAGOTCHI_FSM_sequency();
		if(0) // flag that says pet died
		{
			xSemaphoreGive(xBinarySemDeadscene);
			vTaskSuspend(NULL);
		}
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

void print_control_task(void *pvParameters)
{
	uint8_t select_pet_text[] = "Choose pet";
	uint8_t select_pet_text_e[] = "           ";
	const EventBits_t BitToWaitFor = PRINT;
	xEventGroupWaitBits(init_event, BitToWaitFor, pdFALSE, pdFALSE, portMAX_DELAY);

    while(1)
    {
		LCD_nokia_goto_xy(0, 0);
		LCD_nokia_send_string(select_pet_text_e);
		if(select_pet_flag != 0)
		{
			LCD_nokia_health_bars(total_bars_health);
			LCD_nokia_happiness_bars(total_bars_happiness);
		}
		LCD_nokia_health_bars(total_bars_health);
		LCD_nokia_happiness_bars(total_bars_happiness);
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

void system_clock_120MHz(void)
{
    mcg_pll_config_t    pll0Config =
            {
                .enableMode = MCG_PLL_DISABLE, /* MCGPLLCLK disabled */
                .prdiv      = 0x13U,            /* PLL Reference divider: divided by 20 */
                .vdiv       = 0x18U,            /*  VCO divider: multiplied by 48 */
            }; /** (50E6/20) * 24 =  60E6 Hz*/


    const osc_config_t osc_config = {
    .freq        = 50000000U,    /* Oscillator frequency: 50000000Hz */
    .capLoad     = (OSC_CAP0P),  /* Oscillator capacity load: 0pF */
    .workMode    = kOSC_ModeExt, /* Use external clock */
    .oscerConfig = {
        .enableMode =
            kOSC_ErClkEnable, /* Enable external reference clock, disable external reference clock in STOP mode */
    }};


    CLOCK_SetSimSafeDivs();

    CLOCK_InitOsc0(&osc_config);

    CLOCK_SetXtal0Freq(osc_config.freq);

    CLOCK_SetFbiMode(kMCG_Dmx32Default, kMCG_DrsLow, NULL);
    CLOCK_SetFbeMode(0, kMCG_Dmx32Default, kMCG_DrsLow, NULL);
    CLOCK_SetPbeMode(kMCG_PllClkSelPll0, &pll0Config);
    CLOCK_SetPeeMode();
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
	flag_pet_actions = 1;
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
		flag_pet_actions = 0;
		tamagotchi_set_emotion(GENERAL);
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
	MUSIC_music_volume(TURN_DOWN);
}
void b4_callback(void)
{
	//volume up
	MUSIC_music_volume(TURN_UP);
}
