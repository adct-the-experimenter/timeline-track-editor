#ifndef OPENALSOFT_PLAYER
#define OPENALSOFT_PLAYER

#include <assert.h>
#include <math.h>

#include "time.h"

#include "AL/al.h" //header for OpenAL Soft
#include "AL/alc.h" //header for OpenAL Soft
#include "AL/alext.h" //header for OpenAL Soft


#include "sndfile.h"

#include <cassert>
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>

class OpenALSoftPlayer()
{
public:
	OpenALSoftPlayer();
	~OpenALSoftPlayer();
	
	//initialize audio device and context passed into openal soft
	void InitOpenALSoft(ALCdevice* thisAudioDevice, ALCcontext* thisContext);
	
	void SetReferenceToAudioDevice(ALCdevice* thisAudioDevice);
	void SetReferenceToAudioContext(ALCcontext* thisAudioContext);
	
	//function to play source
	void playSource(ALuint* thisSource);
	
	
private:
	ALCdevice* audioDevicePtr; //pointer to audio device to be used
    ALCcontext* alContextPtr; //pointer to context of where audio is played
};

#endif
