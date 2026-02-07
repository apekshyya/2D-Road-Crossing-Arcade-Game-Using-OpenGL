#pragma once
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

class SoundManager {
public:
  // OpenAL device and context
  ALCdevice* device;
  ALCcontext* context;
  
  // Sound buffer IDs
  ALuint ambience;
  ALuint footstepGrass;
  ALuint footstepRoad;
  ALuint coinPick;
  ALuint horn1;
  ALuint horn2;
  ALuint horn3;
  ALuint horn4;
  ALuint gameOver;
  ALuint carHit;
  
  // Source IDs for playback
  ALuint ambienceSource;
  ALuint effectSource;
  
  // Constructor and destructor
  SoundManager();
  ~SoundManager();
  
  // Initialize sound effects with OpenAL
  void initSounds();
  
  // Play sound helper methods
  void playSound(ALuint buffer, ALuint source, bool loop = false);
  void setVolume(ALuint source, float volume);
  
private:
  ALuint loadWavFile(const char* filename);
};

