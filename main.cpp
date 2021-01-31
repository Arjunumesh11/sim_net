#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "he_wlan.h"
#include <math.h>       /* ceil */


/*
This function measures the collision rate of pure UL OFDMA as a function of the number of contending stations and the number of RA RUs.
It is used to build Figure 6 of the paper (Performance Evaluation of OFDMA and MU-MIMO in 802.11ax Networks)
*/
void pureOfdmaCollisionRate() {
	struct wlan_result result;
	
	printf("Collision rate of pure UL OFDMA (1x1 UL MU-MIMO):\n");
	printf("nRAStas    1RARUs    2RARUs    4RARUs    8RARUs   16RARUs\n");
	
	setApAntennas(1);
	
	int step = 1;
	for (int nRAStas = 1; nRAStas <= 100; nRAStas += step) {
		if (nRAStas == 10) step = 10;
		
		printf("%7d", nRAStas);
		for (int nRARUs = 1; nRARUs <= 16; nRARUs *= 2) {
			result = simulate_wlan(BANDWIDTH_80MHz, PURE_UL_OFDMA, RU_SIZE_26_TONES, nRARUs, nRAStas, MCS_6, 100);
			printf("    %5.2f%%", result.ofdma_collision_rate);
		}
		printf("\n");
	}
}


/*
This function measures the throughput of pure UL OFDMA as a function of the number of contending stations and the number of RA RUs.
It is used to build Figure 7 of the paper
*/
void pureOfdmaThroughput() {
	struct wlan_result result;
	
	printf("Throughput of pure UL OFDMA (1x1 UL MU-MIMO):\n");
	printf("we measure the throughput as a function of the number of contending stations (not all stations)\n");
	printf("nRAStas    10RARUs\n");//    1RARUs    2RARUs    4RARUs    8RARUs   16RARUs\n");
	
	setApAntennas(1);
	
	int step = 1;
	for (int nStas = 1; nStas <= 10; nStas += step) {
		if (nStas == 20) step = 10;

		printf("%7d    ", nStas);
		
		//case of nRARUs=0 is treated separately from the following "for" loop because 0 *= 2 is always 0 and causes an infinit loop
		result = simulate_wlan(BANDWIDTH_80MHz, PURE_UL_OFDMA, RU_SIZE_26_TONES, 10, nStas, MCS_6, 100);
		printf("%6.2fM   ", result.throughput);

		// for (int nRARUs = 1; nRARUs <= 16; nRARUs *= 2) {
		// 	result = simulate_wlan(BANDWIDTH_80MHz, PURE_UL_OFDMA, RU_SIZE_26_TONES, 10, nStas, MCS_6, 10);
		// 	printf("%6.2fM   ", result.throughput);
		// }
		
		printf("\n");
	}
}


int main(int argc, char** argv) {
	pureOfdmaThroughput();
	printf("\n");

	
	
	return 0;
}

