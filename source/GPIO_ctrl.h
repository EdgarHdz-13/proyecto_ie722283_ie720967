/*
 * GPIO_ctrl.h
 *
 *  Created on: 22 abr 2022
 *      Author: Edgar Hernández, Victor Cervantes
 */

#ifndef GPIO_CTRL_H_
#define GPIO_CTRL_H_

#include "MK66F18.h"
#include "Bits.h"

#define LED_PORT    PORTC
#define R_PIN       2U
#define G_PIN       3U
#define B_PIN       1U

/** PORTC */
#define B0_PIN      3U
#define B1_PIN      4U
#define B2_PIN      16U
#define B3_PIN      8U
#define B4_PIN      12U


/** Switch */
#define SW2_PORT    PORTC
#define SW2_PIN     6
#define SW2_GPIO    GPIOC

#define SW3_PORT    PORTA
#define SW3_PIN     4
#define SW3_GPIO    GPIOA

typedef enum {
    B0,
    B1,
    B2,
    B3,
    B4,
}buttons_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  Minimal system to GPIO.

     \param[in]     void.
     \return        void.
 */
void GPIO_init(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  getting interrupt flag portc.

     \param[in]     void.
     \return        boolean_t.
 */
boolean_t get_interrupt_flag_portc(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  getting interrupt flag port a.

     \param[in]     void.
     \return        boolean_t.
 */
boolean_t get_interrupt_flag_porta(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  clearing interrupt flag static port c.

     \param[in]     void.
     \return        void.
 */
void clear_interrupt_flag_portc(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  clearing interrupt flag static port a.

     \param[in]     void.
     \return        void.
 */
void clear_interrupt_flag_porta(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  Assign a function in interrupt callback.

     \param[in]     buttons_t button        Where will go the callback.
     \param[in]     void (*handler)(void)   Function to callback.
     \return        void.
 */
void GPIO_callback_assign(buttons_t button, void (*handler)(void));

#endif /* GPIO_CTRL_H_ */
