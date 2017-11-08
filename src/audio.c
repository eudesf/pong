#include "audio.h"
#include "common.h"

typedef struct {
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
} Wav;

Wav paddleBallTouchWAV;
Wav backgroundWAV;
Wav wallTouchWAV;

int loadWAVFile(const char* path, Wav* wav) {
    if (SDL_LoadWAV(path,
                    &wav->wavSpec,
                    &wav->wavBuffer,
                    &wav->wavLength) == NULL) {
        printf("could not open wav file %s: %s\n", path, SDL_GetError());
        return 1;
    }
    return 0;
}

void loadWAVFiles() {
    loadWAVFile("resources/paddle-ball-touch.wav", &paddleBallTouchWAV);
    loadWAVFile("resources/background.wav", &backgroundWAV);
    loadWAVFile("resources/wall-touch.wav", &wallTouchWAV);
}

void freeWAVFiles() {
    SDL_FreeWAV(paddleBallTouchWAV.wavBuffer);
    SDL_FreeWAV(backgroundWAV.wavBuffer);
    SDL_FreeWAV(wallTouchWAV.wavBuffer);
}

void playWAV(Wav* wav) {
    SDL_ClearQueuedAudio(wav->deviceId);
    SDL_QueueAudio(wav->deviceId, wav->wavBuffer, wav->wavLength);
    SDL_PauseAudioDevice(wav->deviceId, 0);
}

int a_startup() {
    SDL_Init(SDL_INIT_AUDIO);

    loadWAVFiles();

    backgroundWAV.deviceId = SDL_OpenAudioDevice(NULL, 0, &backgroundWAV.wavSpec, NULL, 0);
    paddleBallTouchWAV.deviceId = SDL_OpenAudioDevice(NULL, 0, &paddleBallTouchWAV.wavSpec, NULL, 0);
    wallTouchWAV.deviceId = SDL_OpenAudioDevice(NULL, 0, &wallTouchWAV.wavSpec, NULL, 0);
    
    return 0;
}

void a_finalize() {
    SDL_CloseAudioDevice(wallTouchWAV.deviceId);
    SDL_CloseAudioDevice(paddleBallTouchWAV.deviceId);
    SDL_CloseAudioDevice(backgroundWAV.deviceId);
    freeWAVFiles();
}

void playCollisionSound(CollisionType collisionType) {
    switch (collisionType) {
    case NO_COLLISION: break;
    case LEFT_PADDLE_COLLISION:
    case RIGHT_PADDLE_COLLISION:
        playWAV(&paddleBallTouchWAV);
        break;
    case LEFT_EDGE_COLLISION:
    case RIGHT_EDGE_COLLISION:
    case TOP_EDGE_COLLISION:
    case BOTTOM_EDGE_COLLISION:
        playWAV(&wallTouchWAV);
        break;
    default:
        printf("collision audio not handled. COLLISION_TYPE=%d\n", collisionType);
    }
}
