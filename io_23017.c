/**
@brief MCP23017, I²C IO Expander
@author Stephan Ruloff
@date 08.01.2016
*/

#include "i2c.h"
#include "io_23017.h"

void mcp23017_init(int bus, uint8_t addr)
{
	i2c_write_2b(bus, addr, IOCON, 8); // enable hardware addressing
	i2c_write_2b(bus, addr, GPIOA, 0x00); // all off
	i2c_write_2b(bus, addr, GPIOB, 0x00);
	i2c_write_2b(bus, addr, IODIRA, 0x00); // all output
	i2c_write_2b(bus, addr, IODIRB, 0x00);
}

int mcp23017_write(int bus, uint8_t addr, uint8_t reg, uint8_t data)
{
	return i2c_write_2b(bus, addr, reg, data);
}

int mcp23017_read(int bus, uint8_t addr, uint8_t reg, uint8_t *data)
{
	uint8_t res_data = 0;
	int result = -1;

	if (i2c_write_bytes(bus, addr, &reg, 1) < 0) {
		return -1;
	}
	if (i2c_read_bytes(bus, addr, &res_data, 1) > 0) {
		*data = res_data;
		result = 1;
	}

	return result;
}
