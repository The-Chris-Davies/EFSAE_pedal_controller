/*
 * wave.c
 *
 *  Created on: Feb 6, 2020
 *      Author: Chris Davies
 */
#include "wave.h"
#include <stdint.h>
#include <string.h>

void fixWave(Wave* w){
	//swaps the little-endian data to big-endian

	//swap little-endian data
	__builtin_bswap32(w->chunkSize);
	__builtin_bswap32(w->sub1Size);
	//bswap16(w->audioFormat);
	//bswap16(w->numChannels);
	__builtin_bswap32(w->sampleRate);
	__builtin_bswap32(w->byteRate);
	//bswap16(w->blockAlign);
	//bswap16(w->bitsPerSample);
	__builtin_bswap32(w->sub2Size);
}

void sendSample(){
	//sends a sample to the DAC

	//load sample into nextVal
	int16_t nextVal = audioBuffer[audioDataInd];
	//divide by 16 to convert signed 16 bit to signed 12 bit
	nextVal /= 16;
	//make unsigned 12 bit and add option bits for DAC
	nextVal = (nextVal+(1<<11))&4095;

	HAL_SPI_Transmit(&hspi2, &audioBuffer[audioDataInd], 2, -1);	//TODO: change timeout value, add error checking
	audioDataInd++;
	if(audioDataInd >= AUDIO_BUFFER_SIZE) {
		if(audioFlag&AUDIO_EOF) HAL_TIM_Base_Stop_IT(&htim4);
		audioDataInd = 0;
	}
	else if(audioDataInd == AUDIO_BUFFER_SIZE/2) {
		if(audioFlag&AUDIO_EOF) HAL_TIM_Base_Stop_IT(&htim4);
	}

}
