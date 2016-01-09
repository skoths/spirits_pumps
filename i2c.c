/**
@brief I²C with user-space interface
@author Stephan Ruloff
@date 08.01.2016
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>


int i2c_open(void)
{
	int device = -1;
	unsigned long funcs = 0;

	if ((device = open("/dev/i2c-1", O_RDWR)) < 0) {
		return -1;
	}

	if (ioctl(device, I2C_FUNCS, &funcs) < 0) {
		close(device);
		device = -1;
	} else {
		if (funcs & I2C_FUNC_I2C) {
			//printf("I2C\n");
		} else {
			close(device);
			device = -1;
		}
	}

	return device;
}

void i2c_close(int fd)
{
	close(fd);
}

int i2c_write_2b(int fd, int addr, uint8_t data1, uint8_t data2)
{
	uint8_t buf[2];
	uint16_t result = 2;

	buf[0] = data1;
	buf[1] = data2;
	if (ioctl(fd, I2C_SLAVE, addr) >= 0) {
		if (write(fd, buf, 2) != 2) {
			return -1;
		}
	}

	return result;
}

int i2c_read_bytes(int fd, int addr, uint8_t *data, size_t len)
{
	int result = 1;

	if (ioctl(fd, I2C_SLAVE, addr) >= 0) {
		if (read(fd, data, len) != len) {
			return -1;
		}
	}

	return result;
}

int i2c_write_bytes(int fd, int addr, uint8_t *data, size_t len)
{
	int result = 1;

	if (ioctl(fd, I2C_SLAVE, addr) >= 0) {
		if (write(fd, data, len) != len) {
			return -1;
		}
	}

	return result;
}
