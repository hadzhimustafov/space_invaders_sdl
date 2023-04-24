#include <iostream>
#include "audio.h"



Audio::Audio(/* args */)
{
}

Audio::~Audio()
{
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void Audio::Load(const char* filename){
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);

    std::cout << "audio loading error: " << SDL_GetError() << std::endl;

    deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
}

void Audio::Play(){
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}