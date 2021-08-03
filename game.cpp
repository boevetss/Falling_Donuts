#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iomanip>
#include "game.h"
#define weight 800
#define height 600

SDL_Surface *image(char *filename)
{
    SDL_Surface *im1 = NULL;
    SDL_Surface *im2 = NULL;
    im1=SDL_LoadBMP(filename);          //путь к изображению, возвращает указатель на загруженную SDL_Surface, иначе null
    if(im1!=NULL)
    {
        im2=SDL_DisplayFormat(im1);
        SDL_FreeSurface(im1);
    }
    if(im2!=NULL)
    {
        Uint32 color=SDL_MapRGB(im2->format, 255, 0, 255);    //пурпурный цвет
        SDL_SetColorKey(im2, SDL_SRCCOLORKEY, color);         //меняет пурпурный на прозрачный
    }
    return im2;
}
window::window()
{}
window::~window()
{}
menu::menu()
{
    for(int i=0; i<15; i++)
        name[i]='\0';
    scr=SDL_SetVideoMode(weight, height, 32, SDL_SWSURFACE);
    backGround=image("Img\\2.bmp");
    backGround1=image("Img\\3.bmp");
    line = image("Img\\Line.bmp");
    rect.x=100;
    rect.y=200;
    font = TTF_OpenFont("calibri.ttf", 30);
    item=0;
    num=0;
    Result=new result();
}
menu::~menu()
{
    delete Result;
    SDL_FreeSurface(backGround1);
    SDL_FreeSurface(backGround);
    SDL_FreeSurface(line);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(text_screen);
    TTF_CloseFont(font);
}
bool menu::Name()
{
    SDL_EnableUNICODE(SDL_ENABLE);                                                  //перевод символов в юникод
    Uint16 unicodeCode;
    text_color.r=128;
    text_color.g=0;
    text_color.b=64;
    while(SDL_WaitEvent(&event))
    {
        SDL_BlitSurface(backGround1, NULL, scr, NULL);
        rect.x=100;
        rect.y=200;
        text_screen=TTF_RenderUTF8_Solid(font, "Введите Ваше имя:", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
        text_color.r=72;
        text_color.g=0;
        text_color.b=36;
        rect.y=280;
        SDL_BlitSurface(line, NULL, scr, &rect);
        text_screen=TTF_RenderUNICODE_Solid(font, name, text_color);
        rect.y=250;
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
        rect.y=300;
        text_color.r=128;
        text_color.g=0;
        text_color.b=64;
        text_screen=TTF_RenderUTF8_Solid(font, "Для продолжения нажмите клавишу Enter", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
        SDL_Flip(scr);
        if(event.type==SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_ESCAPE)
                return false;
            unicodeCode = event.key.keysym.unicode;
            if(((unicodeCode >= static_cast<Uint16>(0x0410))&&(unicodeCode <= static_cast<Uint16>(0x044F)))||((unicodeCode == static_cast<Uint16>(0x0401)) || (unicodeCode == static_cast<Uint16>(0x0451))))
                if(num<14)
                    name[num++]=unicodeCode;                   //заносится имя в массив
            if(event.key.keysym.sym == SDLK_BACKSPACE)         //затирка ненужных букв
                if(num>0)
                    name[--num]='\0';
            if(event.key.keysym.sym == SDLK_RETURN)
                return true;
         }
   }
}
bool menu::Rules()
{
    text_color.r=128;
    text_color.g=0;
    text_color.b=64;
    SDL_BlitSurface(backGround, NULL, scr, NULL);
    rect.x=15;
    rect.y=70;
    text_screen=TTF_RenderUTF8_Solid(font, "        Помогите Биллу скинуть пару килограмм, убегая от ", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=30;
    text_screen=TTF_RenderUTF8_Solid(font, "пончиков.", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=30;
    text_screen=TTF_RenderUTF8_Solid(font, "        Сверху произвольным образом (в разных местах экрана", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=30;
    text_screen=TTF_RenderUTF8_Solid(font, "и с разной скоростью) падают шоколадные пончики.", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=50;
    text_screen=TTF_RenderUTF8_Solid(font, "        Цель игры: набрать как можно больше очков,", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=30;
    text_screen=TTF_RenderUTF8_Solid(font, "которые начисляются за каждый пропущенный пончик.", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=50;
    text_screen=TTF_RenderUTF8_Solid(font, "        Игра заканчивается, когда Билл не успевает уклониться", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=30;
    text_screen=TTF_RenderUTF8_Solid(font, "от пончика.", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=50;
    text_screen=TTF_RenderUTF8_Solid(font, "        Результатом является количество набранных очков.", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=30;
    text_screen=TTF_RenderUTF8_Solid(font, "10 лучших результатов выводятся на экран по запросу", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y+=30;
    text_screen=TTF_RenderUTF8_Solid(font, "пользователя.", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    text_color.r=72;
    text_color.g=0;
    text_color.b=36;
    rect.y=500;
    text_screen=TTF_RenderUTF8_Solid(font, "               Нажмите клавишу Enter для выхода в меню", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.x=300;
    rect.y=10;
    text_screen=TTF_RenderUTF8_Solid(font, "Правила игры", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    SDL_Flip(scr);
    while(SDL_WaitEvent(&event))
    {
        if(event.type==SDL_KEYDOWN)
            if(event.key.keysym.sym == SDLK_ESCAPE||event.key.keysym.sym == SDLK_RETURN)
                return false;
      }
}
bool menu::Move()
{
    while(SDL_WaitEvent(&event))
    {
        Draw(item);
        if(event.type==SDL_KEYDOWN)
        {
            if(event.key.keysym.sym==SDLK_DOWN)
            {
                if(item!=4)
                    item++;
                else
                    item=0;
                Draw(item);
            }
            if(event.key.keysym.sym==SDLK_UP)
            {
                if(item!=0)
                    item--;
                else
                    item=4;
                Draw(item);
            }
            if(event.key.keysym.sym==SDLK_RETURN)
            {
                switch(item)
                {
                    case 0: Games();                //Начать игру
                            break;
                    case 1: Name();                 //Смена игрока
                            break;
                    case 2: Result->Draw(scr);     //Просмотр результатов
                            break;
                    case 3: Rules();                //Правила игры
                            break;
                    case 4: Result->Save(name);     //Сохранение резльтата
                            return false;
                            break;
                }
            }
            Draw(item);
        }
    }
}
void menu::Draw(int item)
{
    SDL_BlitSurface(backGround, NULL, scr, NULL);
    text_color.r=128;
    text_color.g=0;
    text_color.b=64;
    rect.y=25;
    rect.x=300;
    if(item==0)
    {
        rect.y=200;
        //темно-бордовый
        text_color.r=72;
        text_color.g=0;
        text_color.b=36;
        text_screen=TTF_RenderUTF8_Solid(font, "Новая игра", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    else
    {
        rect.y=200;
        text_color.r=128;
        text_color.g=0;
        text_color.b=64;
        text_screen=TTF_RenderUTF8_Solid(font, "Новая игра", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    if(item==1)
    {
        //темно-бордовый
        rect.y=250;
        text_color.r=72;
        text_color.g=0;
        text_color.b=36;
        text_screen=TTF_RenderUTF8_Solid(font, "Смена игрока", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    else
    {
        rect.y=250;
        text_color.r=128;
        text_color.g=0;
        text_color.b=64;
        text_screen=TTF_RenderUTF8_Solid(font, "Смена игрока", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    if(item==2)
    {
        //темно-бордовый
        rect.y=300;
        text_color.r=72;
        text_color.g=0;
        text_color.b=36;
        text_screen=TTF_RenderUTF8_Solid(font, "Просмотр результатов", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    else
    {
        rect.y=300;
        text_color.r=128;
        text_color.g=0;
        text_color.b=64;
        text_screen=TTF_RenderUTF8_Solid(font, "Просмотр результатов", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    if(item==3)
    {
        //темно-бордовый
        rect.y=350;
        text_color.r=72;
        text_color.g=0;
        text_color.b=36;
        text_screen=TTF_RenderUTF8_Solid(font, "Правила игры", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    else
    {
        rect.y=350;
        text_color.r=128;
        text_color.g=0;
        text_color.b=64;
        text_screen=TTF_RenderUTF8_Solid(font, "Правила игры", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    if(item==4)
    {
        //темно-бордовый
        rect.y=400;
        text_color.r=72;
        text_color.g=0;
        text_color.b=36;
        text_screen=TTF_RenderUTF8_Solid(font, "Выход", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    else
    {
        rect.y=400;
        text_color.r=128;
        text_color.g=0;
        text_color.b=64;
        text_screen=TTF_RenderUTF8_Solid(font, "Выход", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    rect.y=25;
    rect.x=10;
    text_screen=TTF_RenderUTF8_Solid(font, "Игрок:", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.x=100;
    text_screen=TTF_RenderUNICODE_Solid(font, name, text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    SDL_Flip(scr);
}
bool menu::Games()
{
    Game=new game();
    while(Game->Play(Result, name, scr)==true)
        SDL_Delay(10);
    return false;
}
game::game()
{
    point1=0;
    text_color.r=128;
    text_color.g=0;
    text_color.b=64;
    font = TTF_OpenFont("calibri.ttf", 30);
    backGround=image("Img\\2.bmp");
    Player=new player();
    SDL_Rect temp;
    Pon=new ponch(temp);
    item=0;
}
game::~game()
{
    SDL_FreeSurface(backGround);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(text_screen);
    TTF_CloseFont(font);
    delete Player;
    delete Pon;
}
bool game::Play(result* Result, Uint16 *name, SDL_Surface *scr)
{
    static int num=90,i=0;
    SDL_BlitSurface(backGround, NULL, scr, NULL);
    while(SDL_PollEvent(&event))
        if(event.key.keysym.sym == SDLK_SPACE)
            if(Pausa(name, scr)==false)
                return Pon->Fall(0, scr, Player->rect, false, point1);
    if(event.type==SDL_KEYDOWN)
    {
        if(event.key.keysym.sym==SDLK_a || event.key.keysym.sym==SDLK_LEFT)
            Player->Move(-10,0);
        if(event.key.keysym.sym==SDLK_d || event.key.keysym.sym==SDLK_RIGHT)
            Player->Move(10,0);
    }
    Count(point1);
    Player->Draw(scr,point1);
    if(i==num)
    {
        if(Pon->Fall(1, scr, Player->rect, true, point1)==false)
        {
            Result->Add(name, point1);
            GameOver(scr, name);
            return false;
        }
        i=0;
        if(num!=15)
            num-=3;
    }
    else
    {
        i++;
        if(Pon->Fall(0, scr, Player->rect, true, point1)==false)
        {
            Result->Add(name, point1);
            GameOver(scr, name);
            return false;
        }
    }
    SDL_Flip(scr);
    return true;
}
char *itoa1(int val)
{
    static const int MAX = 32;
    static char buff[MAX]={0};
    char *res = buff + MAX - 2;
    do
    {
        *(res--) = '0' + val%10;
        val/=10;
    }
    while (val > 0);
    return res + 1;
};
bool game::GameOver(SDL_Surface *scr, Uint16* name)
{
    text_color.r=128;
    text_color.g=0;
    text_color.b=64;
    static char* str;
    SDL_BlitSurface(backGround, NULL, scr, NULL);
    str=itoa1(point1);
    rect.y=250;
    rect.x=200;
    text_screen=TTF_RenderUTF8_Solid(font, "Ой, вы проиграли. Попробуйте снова", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y=280;
    text_screen=TTF_RenderUTF8_Solid(font, "Очки :", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.x=300;
    text_screen=TTF_RenderText_Solid(font, str, text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.x=120;
    rect.y=550;
    text_screen=TTF_RenderUTF8_Solid(font, "Нажмите клавищу Enter для выхода в меню", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    SDL_Flip(scr);
    while(SDL_WaitEvent(&event))
    {
        if(event.type==SDL_KEYDOWN)
            if(event.key.keysym.sym == SDLK_ESCAPE||event.key.keysym.sym == SDLK_RETURN)
        return false;
    }
}
bool game::Pausa(Uint16 *name, SDL_Surface *scr)
{
    while(SDL_WaitEvent(&event))
    {
        Draw(name, scr, item);
        if(event.type==SDL_KEYDOWN)
        {
            if(event.key.keysym.sym==SDLK_DOWN)
            {
                if(item==0)
                    item=1;
                else
                    item=0;
                Draw(name, scr, item);
            }
            if(event.key.keysym.sym==SDLK_UP)
            {
                if(item==1)
                    item=0;
                else
                    item=1;
                Draw(name, scr, item);
            }
            while (SDL_WaitEvent(&event))
            {
                switch(item)
                {
                    case 0: return true;
                            break;
                    case 1:
                            if(event.type==SDL_KEYDOWN)
                                if(event.key.keysym.sym == SDLK_ESCAPE||event.key.keysym.sym == SDLK_RETURN)
                                    return false;
                            break;
                }
            }
        }
    }
}
bool game::Draw(Uint16 *name, SDL_Surface *scr, int item)
{
    SDL_BlitSurface(backGround, NULL, scr, NULL);
    text_color.r=128;
    text_color.g=0;
    text_color.b=64;
    rect.y=25;
    rect.x=300;
    if(item==0)
    {
        rect.y=200;
        text_color.r=72;
        text_color.g=0;
        text_color.b=36;
        text_screen=TTF_RenderUTF8_Solid(font, "Продолжить", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    else
    {
        rect.y=200;
        text_color.r=128;
        text_color.g=0;
        text_color.b=64;
        text_screen=TTF_RenderUTF8_Solid(font, "Продолжить", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    if(item==1)
    {
        rect.y=250;
        text_color.r=72;
        text_color.g=0;
        text_color.b=36;
        text_screen=TTF_RenderUTF8_Solid(font, "Выйти из игры", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    else
    {
        rect.y=250;
        text_color.r=128;
        text_color.g=0;
        text_color.b=64;
        text_screen=TTF_RenderUTF8_Solid(font, "Выйти из игры", text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
    }
    rect.x=130;
    rect.y=500;
    text_screen=TTF_RenderUTF8_Solid(font, "Выберите продолжить или выход из игры. ", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    SDL_Flip(scr);
}
result::result()
{
    text_color.r=128;   //цвет выведенного текста
    text_color.g=0;
    text_color.b=64;
    font = TTF_OpenFont("calibri.ttf", 30);
    backGround=image("Img\\2.bmp");
    size=0;
    f=fopen("record.bin", "rb+");
    if(f==NULL)
        f=fopen("record.bin", "wb+");
    for(int i=0; i<10 && fread(&mas[i], 1, sizeof(struct file), f); i++)
        size++;
}
result::~result()
{
    SDL_FreeSurface(backGround);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(text_screen);
    TTF_CloseFont(font);
    fclose(f);
}
bool result::Save(Uint16* name)
{
    fseek(f, 0, SEEK_SET); //(файл,сдвиг от начала,начало текста)
    for(int j=0; j<size; j++)
        fwrite(&mas[j], 1, sizeof(struct file), f); //(указатель на массив, размер элемента, количество элементов, указатель на файл)
    return true;
}
bool result::Add(Uint16* name, int point)
{
    for(int i=0; i<10; i++)
        if(point>mas[i].point)
        {
            for(int j=9;j>i; j--)
                mas[j]=mas[j-1];
            mas[i].point=point;
            for(int k=0; k<14; k++)
                mas[i].name[k]=name[k];
            if(size<10)
                size++;
            return true;
        }
    return false;
}
bool result::Draw(SDL_Surface *scr)
{
    char* str;
    SDL_BlitSurface(backGround, NULL, scr, NULL);
    rect.y=30;
    rect.x=250;
    text_screen=TTF_RenderUTF8_Solid(font, "Топ 10 лучших результатов", text_color);
    SDL_BlitSurface(text_screen, NULL, scr, &rect);
    rect.y=90;
    for(int i=0; i<size; i++)
    {
        rect.x=200;
        text_screen=TTF_RenderText_Solid(font, str=itoa1(i+1), text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
        rect.x=250;
        text_screen= TTF_RenderUNICODE_Solid(font, mas[i].name, text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
        rect.x=450;
        text_screen=TTF_RenderText_Solid(font, str=itoa1(mas[i].point), text_color);
        SDL_BlitSurface(text_screen, NULL, scr, &rect);
        rect.y+=50;
    }
    SDL_Flip(scr);
    while(SDL_WaitEvent(&event))
    {
        if(event.type==SDL_KEYDOWN)
            if(event.key.keysym.sym == SDLK_ESCAPE||event.key.keysym.sym == SDLK_RETURN)
                return false;
    }
}
player::player()
{
    rect.x = 400;
    rect.y = 450;
    rect.w = 60;
    rect.h = 150;
    surf = image("Img\\Igr.bmp");
}
player::~player()
{
    SDL_FreeSurface(surf);
    SDL_FreeSurface(surf2);
}
void player::Move(int xShift,int yShift)
{
    if((rect.x+xShift>0)&&(rect.x+rect.w+xShift<800))
        rect.x+=xShift;
    if((rect.y+yShift>0)&&(rect.y+rect.h+yShift<800))
        rect.y+=yShift;
}
bool player::Draw(SDL_Surface *scr,int poi)
{
    TTF_Font *font;
    font = TTF_OpenFont("calibri.ttf", 28);
    SDL_Color text_color;
    text_color.r=128;
    text_color.g=0;
    text_color.b=64;
    static char *str;
    SDL_BlitSurface(surf, NULL, scr, &rect);
    str=itoa1(poi);
    text_rect.y=10;
    text_rect.x=690;
    surf2=TTF_RenderUTF8_Solid(font, "Очки:", text_color);
    SDL_BlitSurface(surf2, NULL, scr, &text_rect);
    text_rect.x=770;
    surf2=TTF_RenderText_Solid(font, str, text_color);
    SDL_BlitSurface(surf2, NULL, scr, &text_rect);
    TTF_CloseFont(font);
    return true;
}
bool game::Count(int temp)
{
    if(point1=temp)
        return true;
}
bool ponch::Fall(int num, SDL_Surface *scr, SDL_Rect temp, bool del,int &poi)
{
    static ponch* ponch1[15];
    static int size1=0;
    int tmp,i,j,k;
    if(del==false)
        for(i=0;i<size1;i++)
            delete ponch1[i];
    else
    {
        if(num)
            if(size1<15)
                ponch1[size1++]=new ponch(rect);
        for(i=0;i<size1;i++)
        {
            if(ponch1[i]!=NULL)
            {
                tmp=ponch1[i]->Draw(scr, temp);
                if(tmp==1)                          //если убежал, то начисляются очки
                {
                    poi++;
                    delete ponch1[i];
                    ponch1[i]=NULL;
                    size1--;
                    for(k=i;k<=size1;k++)
                        ponch1[k]=ponch1[k+1];
                }
                else
                    if(tmp==2)                          //если упал на голову, то завершение
                    {
                        for(i=0;i<size1;i++)            //освобождение памяти
                            delete ponch1[i];
                        size1=0;                        //обнуление размера
                        return false;
                    }
            }
        }
        return true;
    }
}
ponch::ponch(SDL_Rect temp)
{
    speed=3+rand()%10;                      //чем больше значение, тем быстрее
    surf=image("Img\\Ponch.bmp");
    rect2.x=1+rand()%749;                   //рандомное местоположения в рамке экрана
    rect2.y=temp.y+temp.h/2;
    rect2.h=50;
    rect2.w=50;
}
ponch::~ponch()
{
    SDL_FreeSurface(surf);
}
int ponch::Draw(SDL_Surface *scr,SDL_Rect temp)
{
     if(abs(rect2.x-(rect2.w)-temp.x+(temp.w)/2)<=rect2.w && abs(temp.y-rect2.y+rect2.h)<=temp.h/2)
     {
        return 2;
     }
     else
     {
        rect2.y+=speed;
     }
     SDL_BlitSurface(surf, NULL, scr, &rect2);
     if(rect2.y+rect2.h==600)
        return 1;
     return 0;
}
