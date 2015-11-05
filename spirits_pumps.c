/**

@brief Pumpenansteuerung
@author Sascha Koths, Stephan Ruloff
@date fall 2014

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "io_23s17.h"

#define MAX_PUMPS 8

#define DIR_FORWARD 0
#define DIR_REVERSE 1

typedef struct 
{
	uint32_t mDelayTime;
	uint32_t mPumpTime;
	uint8_t mDirection;
} PumpData;

int FindMaxTime(PumpData* p)
{
	int i;
	int result = 0;
	int sum;
	
	for (i = 0; i < MAX_PUMPS; i++) {
		sum = p[i].mDelayTime + p[i].mPumpTime;
		if (sum > result) {
			result = sum;
		}
	}

	return result; 
}

uint8_t StrToPump(const char* str, PumpData *p)
{
	char c;
	int a;
	int b;
	int ret;
	
	ret = sscanf(str, "%c:%i:%i", &c, &a, &b);
	if (ret == 3) {
		p->mDelayTime = a;
		p->mPumpTime = b;
		c = toupper(c);
		if (c == 'F') {
			p->mDirection = DIR_FORWARD;
		} else if (c == 'R') {
			p->mDirection = DIR_REVERSE;
		} else {
			return 2;
		}
		
		return 0;
	}
	
	return 1;
}

void Usage(void)
{
	printf("Pump-Control\n");
	printf("./spirits_pumps (Pump1) [(Pump2)] ... [(Pump8)]\n\n");
	printf("PumpX : <Direction>:<Delay-Time>:<Pump-Time>\n\n");
	printf("  <Direction>: f (forward) or r (reverse)\n");
	printf("  <Delay-Time>: Seconds to wait befor pumping\n");
	printf("  <Pump-Time>: Seconds to pump\n");
	printf("\n");
	printf("e.g.: ./spirits_pumps r:1:2 f:5:1\n");
}

int main(int argc, char **argv)
{
	int out = 0;
	int i, k;
	int maxtime = 0;
	int no_of_pumps = argc - 1;
	PumpData pumps[8];
	uint8_t pumpOn;
	
	if (no_of_pumps < 1 || no_of_pumps > MAX_PUMPS) {
		Usage();
		exit(1);
	}
	
	memset(pumps, 0, sizeof(pumps));
	
	printf("Anzahl Pumpen: %d\n", no_of_pumps);
	printf("Pumpenzeiten: \n");
	
	for (i = 0; i < no_of_pumps; i++) {
		if (StrToPump(argv[i + 1], &pumps[i])) {
			printf("Eingabefehler\n");
			exit(2);
		}
		
		printf("Pumpe %d: %d sek %d sek %c\n", i + 1 ,pumps[i].mDelayTime, 
				pumps[i].mPumpTime, 
				pumps[i].mDirection == DIR_FORWARD ? 'F' : 'R');
	}
	
	maxtime = FindMaxTime(pumps);
	printf("Maxtime: %d sek\n", maxtime);
	
#ifndef SIM
	pfio_init();
#endif
	
	for (i = 0; i < maxtime; i++) {
		out = 0;
		
		for (k = 0; k < no_of_pumps; k++) {
			pumpOn = (i >= pumps[k].mDelayTime) && i < (pumps[k].mDelayTime + pumps[k].mPumpTime);
			if (pumpOn) {
				if (pumps[k].mDirection == DIR_REVERSE) {
					out |= (1) << (k * 2);
				} else {
					out |= (2) << (k * 2);
				}
			}
		}
		
		printf("Binaryout: %04x \n", out);
#ifndef SIM
		pfio_write_output(out);
#endif
		sleep(1);
	}

#ifndef SIM
	pfio_write_output(0);
	pfio_deinit();
#endif
	
	return 0;
}
