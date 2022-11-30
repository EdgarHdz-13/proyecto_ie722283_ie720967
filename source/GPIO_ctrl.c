/*
 * GPIO_ctrl.c
 *
 *  Created on: 22 abr 2022
 *      Author: Edgar Hernández, Victor Cervantes
 */
#include "MK66F18.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "GPIO_ctrl.h"
#include "Bits.h"

static boolean_t status_interrupt_flag_portc = FALSE;
static boolean_t status_interrupt_flag_porta = FALSE;

/** All callbacks */
static void (*gpio_b0_callback)(void) = 0;
static void (*gpio_b1_callback)(void) = 0;
static void (*gpio_b2_callback)(void) = 0;
static void (*gpio_b3_callback)(void) = 0;
static void (*gpio_b4_callback)(void) = 0;

void PORTC_IRQHandler(void)
{
    uint32_t pin = GPIO_PortGetInterruptFlags(GPIOC);
    /** Check pin interrupt */
    switch(pin)
    {
        case 1U << B0_PIN:
            if(gpio_b0_callback)
            {
                gpio_b0_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOC, 1U << B0_PIN);
        break;
        case 1U << B1_PIN:
            if(gpio_b1_callback)
            {
                gpio_b1_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOC, 1U << B1_PIN);
        break;
        case 1U << B2_PIN:
            if(gpio_b2_callback)
            {
                gpio_b2_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOC, 1U << B2_PIN);
        break;
        case 1U << B3_PIN:
            if(gpio_b3_callback)
            {
                gpio_b3_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOC, 1U << B3_PIN);
        break;
        case 1U << B4_PIN:
            if(gpio_b4_callback)
            {
                gpio_b4_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOC, 1U << B4_PIN);
        break;
    }
    status_interrupt_flag_portc = TRUE;
    SDK_ISR_EXIT_BARRIER;
}

void GPIO_init(void)
{
    gpio_pin_config_t b0_config = {
        kGPIO_DigitalInput,
        0,
    };
    gpio_pin_config_t b1_config = {
        kGPIO_DigitalInput,
        0,
    };
    gpio_pin_config_t b2_config = {
        kGPIO_DigitalInput,
        0,
    };
    gpio_pin_config_t b3_config = {
        kGPIO_DigitalInput,
        0,
    };
    gpio_pin_config_t b4_config = {
        kGPIO_DigitalInput,
        0,
    };

    /*********************  BUTTON PIN CONFIG PORTC ***********************/
    const port_pin_config_t port_button_config = {/* Internal pull-up resistor is enabled */
                                                       kPORT_PullUp,
                                                       /* Fast slew rate is configured */
                                                       kPORT_FastSlewRate,
                                                       /* Passive filter is disabled */
                                                       kPORT_PassiveFilterEnable,
                                                       /* Open drain is disabled */
                                                       kPORT_OpenDrainDisable,
                                                       /* High drive strength is configured */
                                                       kPORT_HighDriveStrength,
                                                       /* Pin is configured as PTA4 */
                                                       kPORT_MuxAsGpio,
                                                       /* Pin Control Register fields [15:0] are not locked */
                                                       kPORT_UnlockRegister};


    /* Port Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);


    /** BUTTONS CONFIG*/
    PORT_SetPinConfig(PORTC, B0_PIN, &port_button_config);
    PORT_SetPinConfig(PORTC, B1_PIN, &port_button_config);
    PORT_SetPinConfig(PORTC, B2_PIN, &port_button_config);
    PORT_SetPinConfig(PORTC, B3_PIN, &port_button_config);
    PORT_SetPinConfig(PORTC, B4_PIN, &port_button_config);

    /** BUTTONS INTERRUPT */
    PORT_SetPinInterruptConfig(PORTC, B0_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, B1_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, B2_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, B3_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, B4_PIN, kPORT_InterruptFallingEdge);

    /** BUTTONS INIT */
    GPIO_PinInit(GPIOC, B0_PIN, &b0_config);
    GPIO_PinInit(GPIOC, B1_PIN, &b1_config);
    GPIO_PinInit(GPIOC, B2_PIN, &b2_config);
    GPIO_PinInit(GPIOC, B3_PIN, &b3_config);
    GPIO_PinInit(GPIOC, B4_PIN, &b4_config);

}

void GPIO_callback_assign(buttons_t button, void (*handler)(void))
{
    switch(button)
    {
        case B0:
            gpio_b0_callback = handler;
        break;
        case B1:
            gpio_b1_callback = handler;
        break;
        case B2:
            gpio_b2_callback = handler;
        break;
        case B3:
            gpio_b3_callback = handler;
        break;
        case B4:
            gpio_b4_callback = handler;
        break;
    }
}

boolean_t get_interrupt_flag_portc(void)
{
    return status_interrupt_flag_portc;
}

boolean_t get_interrupt_flag_porta(void)
{
    return status_interrupt_flag_porta;
}

void clear_interrupt_flag_portc(void)
{
    status_interrupt_flag_portc = FALSE;
}

void clear_interrupt_flag_porta(void)
{
    status_interrupt_flag_porta = FALSE;
}

