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

#define BASE_FREQ_IN_US     500

#define MUSIC_FTM           FTM3
#define MUSIC_FTM_CHANNEL   kFTM_Chnl_2

void MUSIC_initialize(void);
void MUSIC_pnote(uint16_t freq);

#endif /* MUSIC_GEN_H_ */
