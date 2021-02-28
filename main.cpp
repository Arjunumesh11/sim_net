#include <stdio.h>
#include <stdlib.h>
#include "he_wlan.h"
#include <math.h>


void pureOfdmaThroughput() {
	struct wlan_result result;
	
	printf("Throughput of pure UL OFDMA (1x1 UL MU-MIMO):\n");
	printf("we measure the throughput as a function of the number of contending stations (not all stations)\n");
	printf("nRAStas    	throughput		BSR		suss_users		MAX_RARU\n");//    1RARUs    2RARUs    4RARUs    8RARUs   16RARUs\n");
	
	setApAntennas(1);
	
	int step = 20;
	for (int nStas = 10; nStas <= 500 ;nStas += step) {
		// if (nStas == 20) step = 10;

		printf("%7d", nStas);
		//case of nRARUs=0 is treated separately from the following "for" loop because 0 *= 2 is always 0 and causes an infinit loop
		for (int max_raru = 1; max_raru < 38; max_raru+=6)
		{
			result = simulate_wlan(BANDWIDTH_80MHz, PURE_UL_OFDMA, RU_SIZE_26_TONES, 37, nStas, MCS_6, 100,max_raru);
			printf("		%6.2fM     		%d	 		%d		%d", result.throughput,result.bsr,result.comp_user,max_raru);
		 	printf("\n");
		}
		 printf("\n");

	}
}


int main(int argc, char** argv) {
	pureOfdmaThroughput();
	printf("\n");	
	return 0;
}

