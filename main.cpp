#include <iostream>
#include <cstring>
#include <SDL.h>
#include <SDL_ttf.h>
#include <ctime>
#include "game.h"

int main(int argc, char *argv[])
{
    srand (time(NULL));
    if(SDL_Init(SDL_INIT_VIDEO))                                    //������������� SDL
    {
        fprintf(stderr,"������ � SDL_Init: %s\n",SDL_GetError());   //��� ������ ��������� ��������� � �������
        return 1;
    }
    if(TTF_Init())                                                  //������������� SDL_ttf
    {
        fprintf(stderr,"������ � TTF_Init: %s\n",SDL_GetError());   //��� ������ ��������� ��������� � �������
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

