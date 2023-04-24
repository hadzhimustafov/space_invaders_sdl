#ifndef AUDIO_H
#define AUDIO_H
#include <SDL2/SDL.h>

class Audio
{
private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
public:
    Audio();
    ~Audio();
    void Load(const char* filename);
    void Play();
};





#endif // AUDIO_H
