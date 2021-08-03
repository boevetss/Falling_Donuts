#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class moving
{
protected:
    SDL_Surface *surf;
    int speed;
public:
    SDL_Rect rect;
};

class player: public moving
{
protected:
    SDL_Surface *surf2;
    SDL_Rect text_rect;
public:
    player();
    ~player();
    void Move(int xShift,int yShift);
    bool Draw(SDL_Surface *scr, int p);
};

class ponch: public moving
{
protected:
    SDL_Rect rect2;
public:
    ponch(SDL_Rect temp);
    ~ponch();
    int Draw(SDL_Surface *scr, SDL_Rect temp);
    bool Fall(int num, SDL_Surface *scr, SDL_Rect temp, bool del,int &p);
};

struct file
{
    Uint16 name[14];
    int point;
};

class window
{
protected:
    SDL_Rect rect;
    TTF_Font *font;
    SDL_Color text_color;
    SDL_Surface *backGround, *surf, *text_screen;
    SDL_Event event;
public:
    window();
    ~window();
};

class result: public window
{
protected:
    struct file mas[10];
    FILE* f;
    int size;
public:
    result();
    ~result();
    bool Save(Uint16* name);
    bool Add(Uint16* name, int point);
    bool Draw(SDL_Surface *scr);
};

class game: public window
{
protected:
    player *Player;
    ponch *Pon;
    int item;
    int point1;
public:
    game();
    ~game();
    bool Count(int temp);
    bool Play(result *Result,Uint16 *name,SDL_Surface *scr);
    bool Pausa(Uint16 *name,SDL_Surface *scr);
    bool Draw(Uint16 *name,SDL_Surface *scr, int item);
    bool GameOver(SDL_Surface *scr, Uint16* name);
};

class menu: public window
{
protected:
    SDL_Surface *scr, *backGround1, *line;
    result *Result;
    game *Game;
    Uint16 name[14];
    int item, num;
public:
    menu();
    ~menu();
    bool Name();
    bool Move();
    bool Rules();
    void Draw(int item);
    bool Games();
 };

#endif // GAME_H_INCLUDED
