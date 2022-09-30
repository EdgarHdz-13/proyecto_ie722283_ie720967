/*
 * MUSIC_gen.c
 *
 *  Created on: 30 sep 2022
 *      Author: Edgar
 */
#include "pin_mux.h"
#include "fsl_port.h"

void initialize(void)
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
}

