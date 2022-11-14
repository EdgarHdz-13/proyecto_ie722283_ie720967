/*
 * SPI.h
 *
 *  Created on: 19 jun. 2021
 *      Author: Edgar Hernández, Victor Cervantes
 */
#include "SPI.h"
#include "fsl_dspi.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"

void SPI_config(void)
{
	dspi_master_config_t masterConfig;
	uint32_t srcClock_Hz;

	CLOCK_SetSimSafeDivs();
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortC);
	
	PORT_SetPinMux(PORTD, PIN0_IDX, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAlt2);
	PORT_SetPinMux(PORTD, PIN2_IDX, kPORT_MuxAlt2);


	/* Master Config NOKIA */
	masterConfig.whichCtar                                  = kDSPI_Ctar0;
	masterConfig.ctarConfig.bitsPerFrame                    = 	8U;
	masterConfig.ctarConfig.baudRate                        = TRANSFER_BAUDRATE_NOKIA;
	masterConfig.ctarConfig.cpol                            = kDSPI_ClockPolarityActiveHigh;
	masterConfig.ctarConfig.cpha                            = kDSPI_ClockPhaseFirstEdge;
	masterConfig.ctarConfig.direction                       = kDSPI_MsbFirst;
	masterConfig.ctarConfig.pcsToSckDelayInNanoSec          = 100000000U / TRANSFER_BAUDRATE_NOKIA;
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec      = 100000000U / TRANSFER_BAUDRATE_NOKIA;
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec   = 100000000U / TRANSFER_BAUDRATE_NOKIA;

	masterConfig.whichPcs = kDSPI_Pcs0;
	masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

	masterConfig.enableContinuousSCK = false;
	masterConfig.enableRxFifoOverWrite = false;
	masterConfig.enableModifiedTimingFormat = false;
	masterConfig.samplePoint = kDSPI_SckToSin0Clock;

	srcClock_Hz = CLOCK_GetFreq(DSPI0_CLK_SRC);
	DSPI_MasterInit(SPI0, &masterConfig, srcClock_Hz);

}
