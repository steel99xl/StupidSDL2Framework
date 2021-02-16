#include "Floofy.hpp"

SDL_Renderer* Floofy::renderer = nullptr;

Floofy::Floofy()
{}
Floofy::~Floofy()
{}

void Floofy::init(const char * title, int xpos, int ypos){
  if( SDL_Init(SDL_INIT_EVERYTHING) == 0){
    std::cout <<"SDL Init Succesful" << std::endl;
    if (SDLNet_Init() == -1) {
    printf("SDLNet_Init: %s\n", SDLNet_GetError());
    exit(2);
  }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_RESIZABLE);
    if(window){
      std::cout << "Window Produced" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer){
      //SDL_RenderSetLogicalSize(renderer, XSize+1, YSize+1);
      SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);

      std::cout << "Render Working" << std::endl;
    }

    running = true;
  }
  else{
    running = false;
  }

}


void Floofy::Input(){
  SDL_Event event;
  SDL_PollEvent(&event);
  if(event.type == SDL_QUIT){running = false;}
  if(event.window.event == SDL_WINDOWEVENT_MAXIMIZED){fullscreen = true; }
  if(event.window.event == SDL_WINDOWEVENT_MINIMIZED){fullscreen = false; }
  if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
    SDL_GetWindowSize(window, &width, &height);
  }
  if(event.type == SDL_MOUSEMOTION){
      //SDL_GetMouseState(&mouseX,&mouseY);
  }
  if(event.type == SDL_MOUSEBUTTONDOWN){
      if(event.button.button == SDL_BUTTON_LEFT){
          LeftClick = true;
      }

  }else{
          LeftClick = false;
      }

}


void Floofy::Update(){
  if(fullscreen){SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);}
  if(!fullscreen){SDL_SetWindowFullscreen(window, 0);}

}

void Floofy::OpenTCP(const char* WEBSITE, int PORT){

    if (SDLNet_ResolveHost(&ip, WEBSITE, PORT) == -1) {
      printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
      exit(1);
    }

    tcpsock = SDLNet_TCP_Open(&ip);
    if (!tcpsock) {
      printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
      exit(2);
    }

}

void Floofy::Pixel(int X, int Y, int R, int G, int B){
  SDL_SetRenderDrawColor(renderer, R,G,B,255);
  SDL_RenderDrawPoint(renderer, X, Y);

}

void Floofy::Line(float sX, float sY, float dX, float dY, int R, int G, int B){
  float X;
  float Y;
  float oY;
  float oX;


  SDL_SetRenderDrawColor(renderer, R,G,B,255);

  X = dX - sX;
  Y = dY - sY;

  if(X >= 0 || Y >=0){
    if(X == 0){
      for(float i = 0; i <= Y; i++){
        oX = sX + X * (sY+i - sY) / Y;
        oY = sY + i;
        SDL_RenderDrawPoint(renderer, oX, oY);
        }
    }
    else{
      for(float i = 0; i <= X; i++){
        oY = sY + Y * (sX+i - sX) / X;
        oX = sX + i;
        SDL_RenderDrawPoint(renderer, oX, oY);
      }
      }
    }
  else{
    X = X*-1;
    Y = Y*-1;
    for(float i = 0; i <= X; i++){
      oY = dY + Y * (dX+i - dX) / X;
      oX = dX + i;
      SDL_RenderDrawPoint(renderer, oX, oY);
      }
    }
}

bool Floofy::Button(const char* LABLE, int TopX, int TopY, int R, int G, int B, const char* FontFile, int Size){
  bool MouseOver = false;

  TTF_Init();

  TTF_Font *Font = TTF_OpenFont(FontFile, Size);
  SDL_Color textColor = { 0, 0, 0, 255 };
  SDL_Surface *textSurface = TTF_RenderText_Solid(Font, LABLE, textColor);
  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

  SDL_Rect textRect;
  textRect.x = TopX; //- textSurface->w * 0.5;
  textRect.y = TopY; //- textSurface->h * 0.5;
  textRect.w = textSurface->w;
  textRect.h = textSurface->h;


  if(mouseX >= TopX && mouseX <= textRect.w+TopX && mouseY >= TopY && mouseY <= textRect.h+TopY){
      MouseOver = true;
        R += 10;
        if(R >= 255){
          R = 255;
        }
        G += 10 ;
        if(G >= 255){
          G = 255;
        }
        B += 10;
        if(B >= 255){
          B = 255;
        }
      if(LeftClick){
        R -= 30;
        if(R <= 0){
          R = 0;
        }
        G -= 30 ;
        if(G <= 0){
          G = 0;
        }
        B -= 30;
        if(B <=0){
          B = 0;
        }
      }
  }
  SDL_SetRenderDrawColor(renderer, R,G,B,255);
  SDL_RenderFillRect(renderer, &textRect);

  SDL_FreeSurface(textSurface);

  SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

  TTF_CloseFont(Font);
  SDL_DestroyTexture(textTexture);
  TTF_Quit();

  return MouseOver;
}

void Floofy::Text(const char* TEXT, int TopX, int TopY, int R, int G, int B, const char* FontFile, int size){
  TTF_Init();

  TTF_Font *Font = TTF_OpenFont(FontFile, size);

  SDL_Color textColor = {R, G, B, 255};
  SDL_Surface *textSurface = TTF_RenderText_Solid(Font, TEXT, textColor);
  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);


  SDL_Rect textRect;
  textRect.x = TopX;
  textRect.y = TopY;
  textRect.w = textSurface->w;
  textRect.h = textSurface->h;

  SDL_FreeSurface(textSurface);

  SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

  SDL_DestroyTexture(textTexture);
  TTF_CloseFont(Font);
  TTF_Quit();
}



void Floofy::Rect2D(int TopX, int TopY, int BottomX, int BottomY, int R, int G, int B){
    SDL_SetRenderDrawColor(renderer, R,G,B,255);
    SDL_Rect rect;

    rect.x = TopX;
    rect.y = TopY;
    rect.w = BottomX;
    rect.h = BottomY;

    SDL_RenderFillRect(renderer, &rect);

}

void Floofy::background(int R, int G, int B){

    SDL_SetRenderDrawColor(renderer, R, G, B, 255);

    SDL_Rect background;
    background.x = background.y = 0;
    background.w = width;
    background.h = height;
    SDL_RenderFillRect(renderer, &background);
}

void Floofy::Render(int FrameStart){
  int FrameDelay = 1000/FPS;
  SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
  SDL_RenderPresent(renderer);
  FrameTime = SDL_GetTicks() - FrameStart;

  if(FrameDelay > FrameTime){
    SDL_Delay(FrameDelay - FrameTime);
  }
}

void Floofy::Clean(){

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Floofy is Clean..." << std::endl;

}
