#ifndef Floofy_hpp
#define Floofy_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

class Floofy{

public:
    Floofy();
    ~Floofy();


    int width;
    int height;
    int FPS;
    int XSize;
    int YSize;

    void init(const char* title, int xpos, int ypos);

    void Input();

    bool Click(){return LeftClick;};

    void Update();

    void OpenTCP(const char* WEBSITE, int PORT);

    void Pixel(int X, int Y, int R, int G, int B);

    void Line(float sX, float sY, float dX, float dY ,int R, int G, int B);

    bool Button(const char* LABLE, int TopX, int TopY, int R, int G, int B, const char* FontFile, int Size);

    void Text(const char* TEXT, int TopX, int TopY, int R, int G, int B, const char* FontFile, int size);

    void Rect2D(int TopX, int TopY, int BottomX, int BottomY, int R, int G, int B);

    void background(int R, int G, int B);

    void ClearScreen() {SDL_RenderClear(renderer);};

    void Render(int FrameStart);

    bool Running() {return running;};

    void Clean();


    static SDL_Renderer* renderer;


private:
  bool running;
  bool fullscreen;
  bool LeftClick;
  bool RightClick;
  int mouseX;
  int mouseY;
  int Count = 0;
  int FrameTime;
  SDL_Window *window;
  IPaddress ip;
  TCPsocket tcpsock;

};


#endif
