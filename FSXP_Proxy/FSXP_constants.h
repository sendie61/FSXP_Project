/*
 * FSXP_constants.h
 *
 *  Created on: Nov 15, 2014
 *      Author: F
 */

#ifndef FSXP_CONSTANTS_H_
#define FSXP_CONSTANTS_H_

/**
 * @brief modules_type enum.
 * all supported hardware modules
 */
enum modules_type {
	UNKNOWN = 0, DUEPROXY, I2C_IO, SPI_LDISP, I2C_ARD, LAST_MODULE_TYPE
};
const char modType[LAST_MODULE_TYPE][11] PROGMEM = {"UNKNOWN\0  ", "DUEPROXY\0 ", "I2C_IO\0   ", "SPI_LDISP\0", "I2C_ARD\0  "};

#endif /* FSXP_CONSTANTS_H_ */
