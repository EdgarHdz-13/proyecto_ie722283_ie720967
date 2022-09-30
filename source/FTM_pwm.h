/*
 * FTM_pmw.h
 *
 *  Created on: 22 abr 2022
 *      Author: Edgar Hernández, Victor Cervantes
 */

#ifndef FTM_PMW_H_
#define FTM_PMW_H_

#include "fsl_ftm.h"
#include "MK66F18.h"

#define FTM_SOURCE_CLOCK    21000000

#define FTM_to_use          FTM0
#define FTM_channel_to_use  kFTM_Chnl_0

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  Init pwm with 50 duty.

     \param[in]     uint32_t    frequency to operate PWM.
     \return        void.
 */
void FTM_pwm_init_duty_50(uint32_t freq);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  Init PWM with 80 duy.

     \param[in]     uint32_t    Frequency to operate FTM PWM.
     \return        void.
 */
void FTM_pwm_init(uint32_t pwm_freq);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  new pwm frequency.

     \param[in]     uint32_t frequency to operate.
     \return        void.
 */
void FTM_pwm_updateHz(uint32_t);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  Initialize PWM with all the parameters.

     \param[in]     FTM_Type* ftm           FTM to use.
     \param[in]     ftm_chnl_t channel      FTM channel.
     \param[in]     uint32_t pwm_freq       FTM frequency.
     \param[in]     uint16_t duty           FTM duty of the signal.
     \return        void.
 */
void FTM_pwm_init_detailed(FTM_Type* ftm,ftm_chnl_t channel, uint32_t pwm_freq,uint16_t duty);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  Detailed update PWM with new values.

     \param[in]     FTM_Type* ftm           FTM to use.
     \param[in]     ftm_chnl_t channel      FTM channel.
     \param[in]     uint32_t pwm_freq       FTM frequency.
     \param[in]     uint16_t duty           FTM duty of the signal.
     \return        void.
 */
void FTM_pwm_update(FTM_Type* ftm,ftm_chnl_t channel, uint32_t pwm_freq,uint16_t duty);

#endif /* FTM_PWM_H_ */
