/*
 * FTM_pwm.c
 *
 *  Created on: 22 abr 2022
 *      Author: Edgar Hernández, Victor Cervantes
 */

#include "fsl_ftm.h"
#include "FTM_pwm.h"

void FTM_pwm_init_duty_50(uint32_t freq)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;

    /*!
     * brief  Fills in the FTM configuration structure with the default settings.
     *
     * The default values are:
     * code
     *   config->prescale = kFTM_Prescale_Divide_1;
     *   config->bdmMode = kFTM_BdmMode_0;
     *   config->pwmSyncMode = kFTM_SoftwareTrigger;
     *   config->reloadPoints = 0;
     *   config->faultMode = kFTM_Fault_Disable;
     *   config->faultFilterValue = 0;
     *   config->deadTimePrescale = kFTM_Deadtime_Prescale_1;
     *   config->deadTimeValue =  0;
     *   config->extTriggers = 0;
     *   config->chnlInitState = 0;
     *   config->chnlPolarity = 0;
     *   config->useGlobalTimeBase = false;
     * endcode
     * param config Pointer to the user configuration structure.
     */
    FTM_GetDefaultConfig(&ftmInfo);

    /** Use prescale div 1 */
    ftmInfo.prescale = FTM_CalculateCounterClkDiv(FTM_to_use, freq, FTM_SOURCE_CLOCK);

    FTM_Init(FTM_to_use, &ftmInfo);

    /** FTM param values */
    ftmParam.chnlNumber            = FTM_channel_to_use;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = 50;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary   = false;
    ftmParam.enableDeadtime        = false;

    FTM_SetupPwm(FTM_to_use, &ftmParam, 1, kFTM_CenterAlignedPwm, freq, FTM_SOURCE_CLOCK);

    FTM_StartTimer(FTM_to_use, kFTM_SystemClock);
}
void FTM_pwm_init(uint32_t pwm_freq)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;

    /*!
     * brief  Fills in the FTM configuration structure with the default settings.
     *
     * The default values are:
     * code
     *   config->prescale = kFTM_Prescale_Divide_1;
     *   config->bdmMode = kFTM_BdmMode_0;
     *   config->pwmSyncMode = kFTM_SoftwareTrigger;
     *   config->reloadPoints = 0;
     *   config->faultMode = kFTM_Fault_Disable;
     *   config->faultFilterValue = 0;
     *   config->deadTimePrescale = kFTM_Deadtime_Prescale_1;
     *   config->deadTimeValue =  0;
     *   config->extTriggers = 0;
     *   config->chnlInitState = 0;
     *   config->chnlPolarity = 0;
     *   config->useGlobalTimeBase = false;
     * endcode
     * param config Pointer to the user configuration structure.
     */
    FTM_GetDefaultConfig(&ftmInfo);

    /** Use prescale div 1 */
    ftmInfo.prescale = FTM_CalculateCounterClkDiv(FTM_to_use, pwm_freq, FTM_SOURCE_CLOCK);

    FTM_Init(FTM_to_use, &ftmInfo);

    /** FTM param values */
    ftmParam.chnlNumber            = FTM_channel_to_use;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = 80;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary   = false;
    ftmParam.enableDeadtime        = false;

    FTM_SetupPwm(FTM_to_use, &ftmParam, 1, kFTM_CenterAlignedPwm, pwm_freq, FTM_SOURCE_CLOCK);

    FTM_StartTimer(FTM_to_use, kFTM_SystemClock);
}
void FTM_pwm_updateHz(uint32_t Hz)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;
    FTM_StopTimer(FTM_to_use);

    /*!
     * brief  Fills in the FTM configuration structure with the default settings.
     *
     * The default values are:
     * code
     *   config->prescale = kFTM_Prescale_Divide_1;
     *   config->bdmMode = kFTM_BdmMode_0;
     *   config->pwmSyncMode = kFTM_SoftwareTrigger;
     *   config->reloadPoints = 0;
     *   config->faultMode = kFTM_Fault_Disable;
     *   config->faultFilterValue = 0;
     *   config->deadTimePrescale = kFTM_Deadtime_Prescale_1;
     *   config->deadTimeValue =  0;
     *   config->extTriggers = 0;
     *   config->chnlInitState = 0;
     *   config->chnlPolarity = 0;
     *   config->useGlobalTimeBase = false;
     * endcode
     * param config Pointer to the user configuration structure.
     */
    FTM_GetDefaultConfig(&ftmInfo);
    /** Use prescale div 1 */
    ftmInfo.prescale = FTM_CalculateCounterClkDiv(FTM_to_use, Hz, FTM_SOURCE_CLOCK);

    FTM_Init(FTM_to_use, &ftmInfo);

    /** FTM param values */
    ftmParam.chnlNumber            = FTM_channel_to_use;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = 80;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary   = false;
    ftmParam.enableDeadtime        = false;

    FTM_SetupPwm(FTM_to_use, &ftmParam, 1, kFTM_CenterAlignedPwm, Hz, FTM_SOURCE_CLOCK);

    FTM_StartTimer(FTM_to_use, kFTM_SystemClock);
}

void FTM_pwm_init_detailed(FTM_Type* ftm,ftm_chnl_t channel, uint32_t pwm_freq,uint16_t duty)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;

    /*!
     * brief  Fills in the FTM configuration structure with the default settings.
     *
     * The default values are:
     * code
     *   config->prescale = kFTM_Prescale_Divide_1;
     *   config->bdmMode = kFTM_BdmMode_0;
     *   config->pwmSyncMode = kFTM_SoftwareTrigger;
     *   config->reloadPoints = 0;
     *   config->faultMode = kFTM_Fault_Disable;
     *   config->faultFilterValue = 0;
     *   config->deadTimePrescale = kFTM_Deadtime_Prescale_1;
     *   config->deadTimeValue =  0;
     *   config->extTriggers = 0;
     *   config->chnlInitState = 0;
     *   config->chnlPolarity = 0;
     *   config->useGlobalTimeBase = false;
     * endcode
     * param config Pointer to the user configuration structure.
     */
    FTM_GetDefaultConfig(&ftmInfo);

    /** Use prescale div 1 */
    ftmInfo.prescale = FTM_CalculateCounterClkDiv(ftm, pwm_freq, FTM_SOURCE_CLOCK);

    FTM_Init(ftm, &ftmInfo);

    /** FTM param values */
    ftmParam.chnlNumber            = channel;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = duty;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary   = false;
    ftmParam.enableDeadtime        = false;

    FTM_SetupPwm(ftm, &ftmParam, 1, kFTM_EdgeAlignedPwm, pwm_freq, FTM_SOURCE_CLOCK);

    FTM_StartTimer(ftm, kFTM_SystemClock);
}
void FTM_pwm_update(FTM_Type* ftm,ftm_chnl_t channel, uint32_t pwm_freq,uint16_t duty)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;

    /*!
     * brief  Fills in the FTM configuration structure with the default settings.
     *
     * The default values are:
     * code
     *   config->prescale = kFTM_Prescale_Divide_1;
     *   config->bdmMode = kFTM_BdmMode_0;
     *   config->pwmSyncMode = kFTM_SoftwareTrigger;
     *   config->reloadPoints = 0;
     *   config->faultMode = kFTM_Fault_Disable;
     *   config->faultFilterValue = 0;
     *   config->deadTimePrescale = kFTM_Deadtime_Prescale_1;
     *   config->deadTimeValue =  0;
     *   config->extTriggers = 0;
     *   config->chnlInitState = 0;
     *   config->chnlPolarity = 0;
     *   config->useGlobalTimeBase = false;
     * endcode
     * param config Pointer to the user configuration structure.
     */
    FTM_GetDefaultConfig(&ftmInfo);

    /** Use prescale div 1 */
    ftmInfo.prescale = FTM_CalculateCounterClkDiv(ftm, pwm_freq, FTM_SOURCE_CLOCK);

    FTM_StopTimer(ftm);

    /** FTM param values */
    ftmParam.chnlNumber            = channel;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = duty;
    ftmParam.firstEdgeDelayPercent = 0U;
    ftmParam.enableComplementary   = false;
    ftmParam.enableDeadtime        = false;

    FTM_SetupPwm(ftm, &ftmParam, 1, kFTM_EdgeAlignedPwm, pwm_freq, FTM_SOURCE_CLOCK);

    FTM_StartTimer(ftm, kFTM_SystemClock);
}

