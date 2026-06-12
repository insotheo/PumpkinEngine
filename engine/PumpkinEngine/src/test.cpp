#include "test.h"

#include <iostream>
#include <SDL3/SDL.h>

void test(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "Failed to init SDL3: " << SDL_GetError() << "\n";
        return;
    }

    SDL_Window* wnd = SDL_CreateWindow("Test window", 800, 600,  SDL_WINDOW_RESIZABLE);
    if(!wnd){
        std::cerr << "Failed to init window: " << SDL_GetError() << "\n";
        SDL_Quit();
        return;
    }

    std::cout << "Pumpkin engine has created window succefully!\n";

    SDL_Event event;
    bool isRunning = true;

    while(isRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                isRunning = false;
            }
        }

        SDL_Delay(16);
    }

    SDL_DestroyWindow(wnd);
    SDL_Quit();

    return;
}