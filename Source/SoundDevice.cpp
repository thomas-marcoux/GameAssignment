#include "SoundDevice.h"
#include <iostream>
#include "AssetLibrary.h"

SoundDevice::SoundDevice()
{

}

SoundDevice::~SoundDevice()
{
	ShutDown();
}

bool SoundDevice::Initialize(std::unique_ptr<AssetLibrary> const& aL)
{
	int numChannels = 100;
	int flags = MIX_INIT_MP3;
	int init = Mix_Init(flags);

	if ((init&flags) != flags)
	{
		std::cout << "SDL_Mixer failed to initialize MP3 support. SDL_Mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "SDL_Mixer could not initialize. SDL_Mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	Mix_AllocateChannels(numChannels);
	aLibrary = aL.get();
	return true;
}

bool SoundDevice::PlaySound(std::string name, int loops)
{
	return PlaySound(name, loops, -1); //-1 is the first channel available
}

bool SoundDevice::PlaySound(std::string name, int loops, int channel)
{
	Mix_PlayChannelTimed(channel, aLibrary->SearchSound(name), loops, -1);
	//Mix_PlayChannel(channel, aLibrary->SearchSound(name), loops);
	return true;
}

bool SoundDevice::PlayMusic(std::string name)
{
	Mix_PlayMusic(aLibrary->SearchMusic(name), -1);
	return true;
}

void SoundDevice::ShutDown()
{
	Mix_CloseAudio();
}
