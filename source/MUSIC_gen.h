/*
 * MUSIC_gen.h
 *
 *  Created on: 30 sep 2022
 *      Author: Edgar
 */

#ifndef MUSIC_GEN_H_
#define MUSIC_GEN_H_

#define DO 				    1046
#define DORE 			    1108
#define RE 				    1174
#define REMI 			    1244
#define MI 				    1318
#define FA 				    1396
#define FASOL 			    1479
#define SOL 			    1567
#define SOLLA 			    1661
#define LA 				    1760
#define LASI 			    1864
#define SI 				    1975

#define INITIALIZE_VOL      20
#define MAX_VOL			    40u
#define MIN_VOL			    0u

#define BASE_FREQ_IN_MS     500

#define MUSIC_FTM           FTM3
#define MUSIC_FTM_CHANNEL   kFTM_Chnl_2

#define DEFAULT_NOTE_SIZE   7

typedef enum
{
    DOUBLEWHOLE = 64,
    WHOLE = 32,
    HALF = 16,
    QUARTER = 8,
    EIGHTH = 4,
    SIZTEENTH = 2,
    THIRTYSECOND = 1
}note_times_t;

typedef struct
{
    uint16_t note;
    note_times_t time;
}note_t;

typedef struct
{
    note_t *note_struct;
    uint16_t size;
}song_t;



void MUSIC_initialize(void);
void MUSIC_pnote(uint16_t freq);
void MUSIC_changeSong(song_t song);
uint32_t MUSIC_playback(void);
#endif /* MUSIC_GEN_H_ */
