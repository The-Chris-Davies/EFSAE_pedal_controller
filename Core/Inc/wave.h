/*
 * wave.h
 *
 *  Created on: Feb 6, 2020
 *      Author: Chris Davies
 */

#ifndef INC_WAVE_H_
#define INC_WAVE_H_

/*
Wave struct header file
(currently only supports PCM audio)
*/

#include <stdint.h>
#include "main.h"

//externs for SPI2 and tim4 objects
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim4;

//defines
#define AUDIO_BUFFER_SIZE 1024	//size of audio buffer, in samples

//enum definitions
enum AUDIO_FLAGS {
	AUDIO_OK = 0,			//no flags
	AUDIO_EOF = 1,			//EOF has been reached
	AUDIO_LOADLAST = 2,		//set if the first half of the buffer has been filled
							// (the last half of the buffer must be filled next)
};

//wave data struct definitions
typedef struct{
	char chunkID[4];
	int32_t chunkSize;
	char format[4];
	char sub1ID[4];
	int32_t sub1Size;
	int16_t audioFormat;
	int16_t numChannels;
	int32_t sampleRate;
	int32_t byteRate;
	int16_t blockAlign;
	int16_t bitsPerSample;
	char sub2ID[4];
	int32_t sub2Size;
}Wave;

//function definitions
void fixWave(Wave*);
void writeDAC(short);
void sendSample();

//object definitions
int16_t audioBuffer[AUDIO_BUFFER_SIZE];	//storage for audio samples
unsigned int audioDataInd;				//current index of the audio data
int audioFlag;			//flag for audio stream (uses audioFlags enum)

#endif /* INC_WAVE_H_ */
