#ifndef SOUNDDEVICE_H
#define SOUNDDEVICE_H

#include <memory>
#include <string>
#include "Definitions.h"
#include "SDL_Mixer.h"

class AssetLibrary;

//Plays sound effects and musics
class SoundDevice
{
public:
	SoundDevice();
	~SoundDevice();
	bool Initialize(std::unique_ptr<AssetLibrary> const&);
	bool PlaySound(std::string, int);
	bool PlaySound(std::string, int, int);
	bool PlayMusic(std::string);
	void ShutDown();

private:
	AssetLibrary* aLibrary;
};

#endif // !SOUNDDEVICE_H
