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


note_t default_note[] = {{DO,QUARTER},{RE,QUARTER},{MI,QUARTER},{FA,QUARTER},{SOL,QUARTER},{LA,QUARTER},{SI,QUARTER}};

const song_t default_music =
{
        default_note,
        DEFAULT_NOTE_SIZE
};

uint8_t g_volume = INITIALIZE_VOL;
song_t g_current_music = default_music;
uint16_t g_music_time = 0;


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

void MUSIC_pnote(uint16_t freq)
{
    FTM_pwm_update(MUSIC_FTM, MUSIC_FTM_CHANNEL, freq, g_volume);
}

void MUSIC_changeSong(song_t song)
{
    g_music_time = 0;
    g_current_music = song;
}

uint32_t MUSIC_playback(void)
{
    note_times_t note_time=0;
    uint16_t note;

    note = (uint16_t)((g_current_music.note_struct+ g_music_time)->note);
    note_time = (uint16_t)((g_current_music.note_struct+ g_music_time)->time);

    MUSIC_pnote(note);
    if(g_music_time < g_current_music.size - 1)
    {
        g_music_time++;
    }
    else
    {
        g_music_time = 0;
    }
    return  note_time;
}


