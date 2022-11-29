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
static void (*gpio_b5_callback)(void) = 0;
static void (*gpio_b6_callback)(void) = 0;
static void (*gpio_sw2_callback)(void) = 0;
static void (*gpio_sw3_callback)(void) = 0;

void PORTA_IRQHandler(void)
{
    GPIO_PortClearInterruptFlags(SW3_GPIO, 1U << SW3_PIN);
    if(gpio_sw3_callback)
    {
        gpio_sw3_callback();
    }
    status_interrupt_flag_porta = TRUE;
    SDK_ISR_EXIT_BARRIER;
}
void PORTB_IRQHandler(void)
{
    uint32_t pin = GPIO_PortGetInterruptFlags(GPIOB);
    /** Check pin interrupt */
    switch(pin)
    {
        case 1U << B2_PIN:
            if(gpio_b2_callback)
            {
                gpio_b2_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOB, 1U << B2_PIN);
        break;
        case 1U << B4_PIN:
            if(gpio_b4_callback)
            {
                gpio_b4_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOB, 1U << B4_PIN);
        break;
    }
    SDK_ISR_EXIT_BARRIER;
}
/** SW2 ISR */
void PORTC_IRQHandler(void)
{
    uint32_t pin = GPIO_PortGetInterruptFlags(GPIOC);
    /** Check pin interrupt */
    switch(pin)
    {
        case 1U << SW2_PIN:
            if(gpio_sw2_callback)
            {
                gpio_sw2_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOC, 1U << SW2_PIN);
        break;
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
        case 1U << B5_PIN:
            if(gpio_b5_callback)
            {
                gpio_b5_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOC, 1U << B5_PIN);
        break;
        case 1U << B6_PIN:
            if(gpio_b6_callback)
            {
                gpio_b6_callback();
            }
            GPIO_PortClearInterruptFlags(GPIOC, 1U << B6_PIN);
        break;
    }
    status_interrupt_flag_portc = TRUE;
    SDK_ISR_EXIT_BARRIER;
}

void PORTD_IRQHandler(void)
{
    if(gpio_b3_callback)
    {
        gpio_b3_callback();
    }
    GPIO_PortClearInterruptFlags(GPIOD, 1U << B3_PIN);
    SDK_ISR_EXIT_BARRIER;
}
void GPIO_init(void)
{
    gpio_pin_config_t sw2_config = {
        kGPIO_DigitalInput,
        0,
    };
    gpio_pin_config_t sw3_config = {
        kGPIO_DigitalInput,
        0,
    };
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
    gpio_pin_config_t b5_config = {
        kGPIO_DigitalInput,
        0,
    };
    gpio_pin_config_t b6_config = {
        kGPIO_DigitalInput,
        0,
    };
    /************* SW PIN CONFIG ************/
    const port_pin_config_t porta4_config = {/* Internal pull-up resistor is enabled */
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
    const port_pin_config_t portc6_config = {/* Internal pull-up resistor is enabled */
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
    /*********************  BUTTON PIN CONFIG PORTC ***********************/
    const port_pin_config_t portc5_config = {/* Internal pull-up resistor is enabled */
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
    const port_pin_config_t portc4_config = {/* Internal pull-up resistor is enabled */
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
    const port_pin_config_t portb3_config = {/* Internal pull-up resistor is enabled */
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
    const port_pin_config_t portd3_config = {/* Internal pull-up resistor is enabled */
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
    const port_pin_config_t portb11_config = {/* Internal pull-up resistor is enabled */
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
    const port_pin_config_t portc11_config = {/* Internal pull-up resistor is enabled */
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
    const port_pin_config_t portc10_config = {/* Internal pull-up resistor is enabled */
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

    /************ FTM PIN CONFIGURATION **********/
    const port_pin_config_t portc1_config = {/* Internal pull-up resistor is enabled */
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
                                                           kPORT_MuxAlt4,
                                                           /* Pin Control Register fields [15:0] are not locked */
                                                           kPORT_UnlockRegister};

    const port_pin_config_t portc2_config = {/* Internal pull-up resistor is enabled */
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
                                                           kPORT_MuxAlt4,
                                                           /* Pin Control Register fields [15:0] are not locked */
                                                           kPORT_UnlockRegister};
    const port_pin_config_t portc3_config = {/* Internal pull-up resistor is enabled */
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
                                                           kPORT_MuxAlt4,
                                                           /* Pin Control Register fields [15:0] are not locked */
                                                           kPORT_UnlockRegister};

    /* Port Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortD);
    CLOCK_EnableClock(kCLOCK_PortB);

    /* PORTC1 is configured as FTM0 */

    PORT_SetPinConfig(LED_PORT, R_PIN, &portc2_config);
    PORT_SetPinConfig(LED_PORT, G_PIN, &portc3_config);
    PORT_SetPinConfig(LED_PORT, B_PIN, &portc1_config);

    PORT_SetPinConfig(SW2_PORT, SW2_PIN, &porta4_config);
    PORT_SetPinConfig(SW3_PORT, SW3_PIN, &portc6_config);

    /** BUTTONS CONFIG*/
    PORT_SetPinConfig(PORTC, B0_PIN, &portc5_config);
    PORT_SetPinConfig(PORTC, B1_PIN, &portc4_config);
    PORT_SetPinConfig(PORTB, B2_PIN, &portb3_config);
    PORT_SetPinConfig(PORTD, B3_PIN, &portd3_config);
    PORT_SetPinConfig(PORTB, B4_PIN, &portb11_config);
    PORT_SetPinConfig(PORTC, B5_PIN, &portc11_config);
    PORT_SetPinConfig(PORTC, B6_PIN, &portc10_config);

    /** ADC CONFIG */
    /* PORTB2 (pin 55) is configured as ADC0_SE12 */
    PORT_SetPinMux(PORTB, 2U, kPORT_PinDisabledOrAnalog);

    /** BUTTONS INTERRUPT */
    PORT_SetPinInterruptConfig(SW2_PORT, SW2_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(SW3_PORT, SW3_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, B0_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, B1_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTB, B2_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTD, B3_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTB, B4_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, B5_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, B6_PIN, kPORT_InterruptFallingEdge);

    /** BUTTONS INIT */
    GPIO_PinInit(SW2_GPIO, SW2_PIN, &sw2_config);
    GPIO_PinInit(SW3_GPIO, SW3_PIN, &sw3_config);
    GPIO_PinInit(GPIOC, B0_PIN, &b0_config);
    GPIO_PinInit(GPIOC, B1_PIN, &b1_config);
    GPIO_PinInit(GPIOB, B2_PIN, &b2_config);
    GPIO_PinInit(GPIOD, B3_PIN, &b3_config);
    GPIO_PinInit(GPIOB, B4_PIN, &b4_config);
    GPIO_PinInit(GPIOC, B5_PIN, &b5_config);
    GPIO_PinInit(GPIOC, B6_PIN, &b6_config);
}

void GPIO_callback_assign(buttons_t button, void (*handler)(void))
{
    switch(button)
    {
        case SW2:
            gpio_sw2_callback = handler;
        break;
        case SW3:
            gpio_sw3_callback = handler;
        break;
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
        case B5:
            gpio_b5_callback = handler;
        break;
        case B6:
            gpio_b6_callback = handler;
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

