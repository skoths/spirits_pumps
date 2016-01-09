#ifndef _I2C_H_
#define _I2C_H_
/**
@brief I²C with user-space interface
@author Stephan Ruloff
@date 08.01.2016
*/

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int i2c_open(void);
void i2c_close(int fd);
int i2c_write_2b(int fd, uint8_t adr, uint8_t data1, uint8_t data2);
int i2c_read_bytes(int fd, int adr, uint8_t *data, size_t len);
int i2c_write_bytes(int fd, int adr, uint8_t *data, size_t len);

#ifdef _cplusplus
}
#endif

#endif
