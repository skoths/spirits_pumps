#ifndef _IO_23017_h_
#define _IO_23017_h_
/**
@brief MCP23017, I²C IO Expander
@author Stephan Ruloff
@date 08.01.2016
*/

#include <stdint.h>

#define MCP23017_BASE_ADDR 0x20

// Port configuration
#define IODIRA 0x00 // I/O direction A
#define IODIRB 0x01 // I/O direction B
#define IOCON  0x0A // I/O config
#define GPIOA  0x12 // port A
#define GPIOB  0x13 // port B
#define GPPUA  0x0C // port A pullups
#define GPPUB  0x0D // port B pullups


#ifdef __cplusplus
extern "C" {
#endif

void mcp23017_init(int bus, uint8_t addr);
int mcp23017_write(int bus, uint8_t addr, uint8_t reg, uint8_t data);
int mcp23017_read(int bus, uint8_t adr, uint8_t reg, uint8_t *data);

#ifdef _cplusplus
}
#endif

#endif
