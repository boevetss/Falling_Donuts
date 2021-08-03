#include <iostream>
#include <cstring>
#include <SDL.h>
#include <SDL_ttf.h>
#include <ctime>
#include "game.h"

int main(int argc, char *argv[])
{
    srand (time(NULL));
    if(SDL_Init(SDL_INIT_VIDEO))                                    //инициализация SDL
    {
        fprintf(stderr,"Ошибка в SDL_Init: %s\n",SDL_GetError());   //При ошибке формируем сообщение и выходим
        return 1;
    }
    if(TTF_Init())                                                  //инициализация SDL_ttf
    {
        fprintf(stderr,"Ошибка в TTF_Init: %s\n",SDL_GetError());   //При ошибке формируем сообщение и выходим
        return 1;
    }
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    class menu Menu;
    if(!Menu.Name())
        return 0;
    Menu.Move();

    return 0;
}

