/*
 * MUSIC_album.c
 *
 *  Created on: 30 sep 2022
 *      Author: Edgar
 */


#include "MUSIC_album.h"

note_t scale_note[] = {{DO,THIRTYSECOND},{DORE,SIZTEENTH},{RE,EIGHTH},{REMI,QUARTER},{MI,HALF},{FA,WHOLE},
        {FASOL,DOUBLEWHOLE},{SOL,QUARTER},{SOLLA,QUARTER},{LA,QUARTER}};
const song_t scale_song =
{
        scale_note,
        10
};

note_t Aura_Lee_note[] = {{DO,QUARTER},{FA,QUARTER},{MI,QUARTER},{FA,QUARTER},{SOL,QUARTER},{RE,QUARTER},{SOL,HALF},
        {FA,QUARTER},{MI,QUARTER},{RE,QUARTER},{MI,QUARTER},{FA,HALF}, {DO,HALF},{DO,QUARTER},{FA,QUARTER},
        {MI,QUARTER},{FA,QUARTER},{SOL,QUARTER},{RE,QUARTER},{SOL,HALF},{FA,QUARTER},{MI,QUARTER},{RE,QUARTER},
        {MI,QUARTER},{FA,WHOLE}};
const song_t Aura_Lee_song =
{
        Aura_Lee_note,
        25
};

note_t Away_in_the_Deep_Forest_note[] = {{DO,WHOLE},{DO,QUARTER},{DO,QUARTER},{DO,QUARTER},{MI,QUARTER},
        {DO,HALF},{DO,QUARTER},{MI,QUARTER},{RE,QUARTER},{DO,QUARTER},{RE,QUARTER},{MI,QUARTER},
        {DO,HALF},{DO,QUARTER},{DO,QUARTER},{DO,QUARTER},{DO,QUARTER},{MI,QUARTER},{DO,HALF},
        {DO,QUARTER},{MI,QUARTER},{RE,QUARTER},{DO,QUARTER},{RE,QUARTER},{MI,QUARTER},{DO,HALF},{SOL,QUARTER},
        {MI,HALF},{SOL,QUARTER},{MI,HALF},{SOL,QUARTER},{FA,QUARTER},{MI,QUARTER},{FA,QUARTER},{SOL,QUARTER},
        {MI,HALF},{SOL,QUARTER},{MI,HALF},{SOL,QUARTER},{MI,HALF},{SOL,QUARTER},{FA,QUARTER},{MI,QUARTER},
        {FA,QUARTER},{SOL,QUARTER},{MI,HALF}};
const song_t Away_in_the_Deep_Forest_song =
{
        Away_in_the_Deep_Forest_note,
        46
};
/*      re fa re* re fa re*
        mi* fa* mi* fa* mi* do* la
        la re fa soI la
        la re fa soI mi.
*/
note_t Song_of_the_storm_note[] = {
        {RE,EIGHTH},{FA,EIGHTH},{REMA,HALF},{RE,EIGHTH},{FA,EIGHTH},{REMA,HALF},
        {MIMA,QUARTER},{FAMA,EIGHTH},{MIMA,EIGHTH},{FAMA,EIGHTH},{MIMA,EIGHTH},{DOMA,EIGHTH},{LA,HALF},
        {LA,QUARTER},{RE,QUARTER},{FA,EIGHTH},{SOL,EIGHTH},{LA,HALF},
        {LA,QUARTER},{RE,QUARTER},{FA,EIGHTH},{SOL,EIGHTH},{MI,HALF}
};
const song_t Song_of_the_storm_song =
{
        Song_of_the_storm_note,
        26
};
