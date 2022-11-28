/*
 * MUSIC_gen.h
 *
 *  Created on: 30 sep 2022
 *      Author: Edgar
 */

#ifndef MUSIC_GEN_H_
#define MUSIC_GEN_H_

#define SIMA                3951
#define LASIMA              3729
#define LAMA                3520
#define SOLLAMA             3322
#define SOLMA               3135
#define FASOLMA             2959
#define FAMA                2793
#define MIMA                2637
#define REMIMA              2489
#define REMA                2349
#define DOREMA              2217
#define DOMA                2093

#define SI 				    1975
#define LASI                1864
#define LA                  1760
#define SOLLA               1661
#define SOL                 1567
#define FASOL               1479
#define FA                  1396
#define MI                  1318
#define REMI                1244
#define RE                  1174
#define DORE                1108
#define DO                  1046

#define SIME                987
#define LASIME              932
#define LAME                880
#define SOLLAME             830
#define SOLME               783
#define FASOLME             739
#define FAME                698
#define MIME                659
#define REMIME              622
#define REME                587
#define DOREME              554
#define DOM E               523

#define INITIALIZE_VOL      40
#define MAX_VOL			    40u
#define MIN_VOL			    0u

#define BASE_FREQ_IN_MS     500

#define MUSIC_FTM           FTM2
#define MUSIC_FTM_CHANNEL   kFTM_Chnl_0

#define OFF                 0

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
void MUSIC_off(void);
void MUSIC_changeSong(song_t song);
uint32_t MUSIC_playback(void);
#endif /* MUSIC_GEN_H_ */
