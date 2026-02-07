#include "SoundManager.hpp"
#include "WavLoader.hpp"
#include <iostream>

SoundManager::SoundManager() {
  // Initialize OpenAL
  device = alcOpenDevice(nullptr);
  if (!device) {
    std::cerr << "Failed to open OpenAL device" << std::endl;
    return;
  }
  
  context = alcCreateContext(device, nullptr);
  if (!context) {
    std::cerr << "Failed to create OpenAL context" << std::endl;
    alcCloseDevice(device);
    return;
  }
  
  alcMakeContextCurrent(context);
  
  // Generate sources
  alGenSources(1, &ambienceSource);
  alGenSources(1, &effectSource);
}

SoundManager::~SoundManager() {
  // Delete sources
  alDeleteSources(1, &ambienceSource);
  alDeleteSources(1, &effectSource);
  
  // Delete buffers
  alDeleteBuffers(1, &ambience);
  alDeleteBuffers(1, &footstepGrass);
  alDeleteBuffers(1, &footstepRoad);
  alDeleteBuffers(1, &coinPick);
  alDeleteBuffers(1, &horn1);
  alDeleteBuffers(1, &horn2);
  alDeleteBuffers(1, &horn3);
  alDeleteBuffers(1, &horn4);
  alDeleteBuffers(1, &gameOver);
  alDeleteBuffers(1, &carHit);
  
  // Cleanup OpenAL
  alcMakeContextCurrent(nullptr);
  alcDestroyContext(context);
  alcCloseDevice(device);
}

ALuint SoundManager::loadWavFile(const char* filename) {
  WavData wav = WavLoader::loadWav(filename);
  
  if (wav.data.empty()) {
    return 0;
  }
  
  ALenum format;
  if (wav.channels == 1) {
    format = (wav.bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
  } else {
    format = (wav.bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
  }
  
  ALuint buffer;
  alGenBuffers(1, &buffer);
  alBufferData(buffer, format, wav.data.data(), wav.data.size(), wav.sampleRate);
  
  ALenum error = alGetError();
  if (error != AL_NO_ERROR) {
    std::cerr << "OpenAL error loading " << filename << ": " << error << std::endl;
    return 0;
  }
  
  return buffer;
}

void SoundManager::initSounds() {
  ambience = loadWavFile("media/ambience.wav");
  gameOver = loadWavFile("media/gameOver.wav");
  coinPick = loadWavFile("media/coin.wav");
  carHit = loadWavFile("media/hit.wav");
  footstepGrass = loadWavFile("media/footstep_grass.wav");
  footstepRoad = loadWavFile("media/footstep_road.wav");
  horn1 = loadWavFile("media/horn_1.wav");
  horn2 = loadWavFile("media/horn_2.wav");
  horn3 = loadWavFile("media/horn_3.wav");
  horn4 = loadWavFile("media/horn_4.wav");
}

void SoundManager::playSound(ALuint buffer, ALuint source, bool loop) {
  alSourceStop(source);
  alSourcei(source, AL_BUFFER, buffer);
  alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
  alSourcePlay(source);
}

void SoundManager::setVolume(ALuint source, float volume) {
  alSourcef(source, AL_GAIN, volume);
}


