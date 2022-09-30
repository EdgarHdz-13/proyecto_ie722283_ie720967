/*
 * MUSIC_gen.c
 *
 *  Created on: 30 sep 2022
 *      Author: Edgar
 */
#include "pin_mux.h"
#include "fsl_port.h"
#include "fsl_ftm.h"
#include "FTM_pwm.h"
#include "MUSIC_gen.h"

uint8_t g_volume = INITIALIZE_VOL;

void MUSIC_initialize(void)
{
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
    FTM_pwm_init_detailed(FTM3,kFTM_Chnl_2, 30,0);
}

void MUSIC_pnote(uint16_t freq){
    FTM_pwm_update(MUSIC_FTM, MUSIC_FTM_CHANNEL, freq, g_volume);
}


