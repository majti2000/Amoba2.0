#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>

class Kocka
{
    private:
        int x,y,size;
        SDL_Surface *s;
    public:
        Kocka(int x, int y, int size, SDL_Color c):
            x(x),y(y),size(size)
        {
            s = SDL_CreateRGBSurface(0,size,size,32,0,0,0,0);
            SDL_FillRect(s,NULL,SDL_MapRGB(s->format,c.r,c.g,c.b));
        }

        ~Kocka(){
            SDL_FreeSurface(s);
        }

        void draw(SDL_Surface *to)
        {
            SDL_Rect rct = {x-(size/2),y-size/2,s->w,s->h};
            SDL_BlitSurface(s,NULL,to,&rct);
        }

        void grow()
        {
            size++;
        }

        void move_here(int x, int y)
        {
            this->x=x;
            this->y=y;
        }

        void move(int x, int y)
        {
            this->x+=x;
            this->y+=y;
        }

        int getX()
        {
            return x;
        }

        int getY()
        {
            return y;
        }

        int getSize()
        {
            return size;
        }

        bool love(Kocka k) //folotte
        {
            return x+size>k.x && k.x+k.size>x && y+size>k.y && k.y+k.size>y;
        }

};

class MovingKocka:public Kocka
{
    private:
        int x_direction, y_direction; 
        bool friend1;
        SDL_Surface *s;
    public:
        MovingKocka(int x, int y, int size, SDL_Color c, int x_direction, int y_direction, bool is_friend):
        Kocka(x,y,size,c), x_direction(x_direction), y_direction(y_direction), friend1(is_friend)
    {
        s = SDL_CreateRGBSurface(0,size,size,32,0,0,0,0);
        SDL_FillRect(s,NULL,SDL_MapRGB(s->format,c.r,c.g,c.b));
    }

    bool friend_e()
    {
        return friend1;
    }

    void move()
    {
        Kocka::move(x_direction, y_direction);
    }

    void draw(SDL_Surface *to)
    {
        SDL_Rect rct = {getX()-getSize()/2,getY()-getSize()/2,s->w,s->h};
            SDL_BlitSurface(s,NULL,to,&rct);
    }

};

int main()
{
    SDL_Window *w;
    SDL_Surface *s;
    

    if(SDL_Init(SDL_INIT_VIDEO)){
        return 1;
    }
    else 
    {
        w = SDL_CreateWindow("ABLAK", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        if (!w)
        {
            return 1;
        }
        else 
        {
            s = SDL_GetWindowSurface(w);
        }
    }
    SDL_Color cc;
    cc.r=240;
    cc.g=160;
    cc.b=200;
    
    int x,y;
    Kocka gamer(x,y,50,cc);
    std::vector<MovingKocka*> kockak;

    bool run = true;
    while (run) {
        SDL_Event ev;
        if (SDL_WaitEvent(&ev)){
            if (ev.type==SDL_MOUSEMOTION){
                SDL_GetGlobalMouseState(&x,&y);
                gamer.draw(s);
                SDL_UpdateWindowSurface(w);
            }

            switch (ev.type)
            {
            case SDL_QUIT:
                run=false;
                break;
            
            default:
                break;
            }
        }
    }
    
  // SDL_Delay(2000);


    SDL_UpdateWindowSurface(w);
    SDL_FreeSurface(s);
    SDL_DestroyWindow(w);
    SDL_Quit();
    


    

    return 0;
}