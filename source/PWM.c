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
#include "fsl_ftm.h"
#include "FTM_pwm.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define DO 1046
#define DORE 1108
#define RE 1174
#define REMI 1244
#define MI 1318
#define FA 1396
#define FASOL 1479
#define SOL 1567
#define SOLLA 1661
#define LA 1760
#define LASI 1864
#define SI 1975

#define DUTY 26
/*
 * @brief   Application entry point.
 */
void delay(void)
{
	for(int i=0;i<200000;i++){};
}
int main(void)
{
	uint8_t i;
    const port_pin_config_t porte7_config = {/* Internal pull-up resistor is enabled */
                                                            kPORT_PullDisable,
                                                           /* Fast slew rate is configured */
                                                           kPORT_FastSlewRate,
                                                           /* Passive filter is disabled */
                                                           kPORT_PassiveFilterDisable,
                                                           /* Open drain is disabled */
                                                           kPORT_OpenDrainDisable,
                                                           /* High drive strength is configured */
                                                           kPORT_HighDriveStrength,
                                                           /* Pin is configured as PTA4 */

														   kPORT_MuxAlt6,
                                                           /* Pin Control Register fields [15:0] are not locked */
                                                           kPORT_UnlockRegister};
    CLOCK_EnableClock(kCLOCK_PortE);
    PORT_SetPinConfig(PORTE, 7u, &porte7_config);
    FTM_pwm_init_detailed(FTM3,kFTM_Chnl_2, 1046,16);

    PRINTF("Hello World\n");


    while(1)
    {

		for(i=0;i<=40;i++)
		{
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, DO, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, FA, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, MI, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, FA, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, SOL, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, RE, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, SOL, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, FA, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, MI, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, RE, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, MI, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, FA, i);
	    	delay();
	    	FTM_pwm_update(FTM3, kFTM_Chnl_2, DO, i);
	    	delay();

		}
    }
    return 0 ;
}

