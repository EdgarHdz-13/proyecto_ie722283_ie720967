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

        /*  SOL, SOLME, DO, MI, REMI, SOLME, SI SIME    8
         *  LA, DO, MI, LA, SOL, DO, RE, MI, LA, DO,    10
         *  FA, LA, SOLLA, DO, RE, FA, MI, SOLME, DO,   9
         *  MI, RE, LAME, SIME, RE                      5
         */
note_t Game_over_note[] = {
        {SOL,QUARTER},{SOLME,QUARTER},{DO,QUARTER},{MI,QUARTER},{REMI,QUARTER},{SOLME,QUARTER},{SI,QUARTER},{SIME,QUARTER},
        {LA,QUARTER},{DO,QUARTER},{MI,QUARTER},{LA,QUARTER},{SOL,QUARTER},{DO,QUARTER},{RE,QUARTER},{MI,QUARTER},{LA,QUARTER},{DO,QUARTER},
        {FA,QUARTER},{LA,QUARTER},{SOLLA,QUARTER},{DO,QUARTER},{RE,QUARTER},{FA,QUARTER},{MI,QUARTER},{SOLME,QUARTER},{DO,QUARTER},
        {MI,QUARTER},{RE,QUARTER},{LAME,QUARTER},{SIME,QUARTER},{RE,QUARTER}
};
const song_t Game_over_song =
{
        Game_over_note,
        32
};
    /*  LA,  LAME,  SOL,   SOLME,   FASOL, FASOLME, MI, MIME    8
     *  SOL, SOLME, FASOL, FASOLME, MI,    MIME,    RE, REME    8
     */

note_t Metroid_title_theme_note[] = {
        {LA,EIGHTH}, {LAME,EIGHTH}, {SOL,EIGHTH}, {SOLME,EIGHTH}, {FASOL,EIGHTH}, {FASOLME,EIGHTH}, {MI,EIGHTH}, {MIME,EIGHTH},
        {SOL,EIGHTH}, {SOLME,EIGHTH}, {FASOL,EIGHTH}, {FASOLME,EIGHTH}, {MI}, {MIME,EIGHTH}, {RE,EIGHTH}, {REME,EIGHTH}
};
const song_t Metroid_title_theme_song =
{
        Metroid_title_theme_note,
        16
};

