#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

#include <SDL2/SDL.h>

const static int WIDTH = 800;
const static int HEIGHT = 600;

SDL_Rect newSDL_Rect(int xs, int ys, int widths, int heights) {
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = widths;
    rectangular.h = heights;
    return rectangular;

}

int mapa[10][20] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,};

int main( int argc, char *argv[] )
{
    srand(time(NULL));


    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError( ) << endl;
    }


    SDL_Window *window = SDL_CreateWindow("The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
       cout << "SDL's window could not initialize! SDL Error: %s" << SDL_GetError( ) << endl;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
       cout << "SDL's renderer could not initialize! SDL Error: %s" << SDL_GetError( ) << endl;
    }

    //Jogador
    SDL_Rect boy = {10 + 2*21, 10 + 2*21, 20, 20};

    //Array de retângulos para renderizar
    SDL_Rect rects[10][20];

    SDL_Event event;
    bool isrunning = true;

    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 20; y++){
            if(mapa[x][y] == 0){
                mapa[x][y] = rand()%4;
            }
            if(mapa[x][y] == 1){
                rects[x][y] = newSDL_Rect(10 + y*21, 10 + x*21, 20, 20);
            } else if(mapa[x][y] == 3){
                rects[x][y] = newSDL_Rect(10 + y*21, 10 + x*21, 20, 20);
            }
        }
    }

    //Loop de jogo
    while(isrunning == true){
        while( SDL_PollEvent( &event ) != 0 ){
                    //Caso termine o programa
            if( event.type == SDL_QUIT ){
                isrunning = false;
            } else if (event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                case SDLK_w:
                    boy.y -= 21;
                    break;
                case SDLK_s:
                    boy.y += 21;
                    break;
                case SDLK_a:
                    boy.x -= 21;
                    break;
                case SDLK_d:
                    boy.x += 21;
                    break;
                default:
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //Refresh em Limpo da tela
        SDL_RenderClear(renderer );

        for (int x = 0; x < 10; x++){
            for (int y = 0; y < 20; y++){
                if(mapa[x][y] == 1){
                    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                    SDL_RenderFillRect(renderer, &rects[x][y]);
                } else if(mapa[x][y] == 3){
                    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
                    SDL_RenderFillRect(renderer, &rects[x][y]);
                }

            }
        }

        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);

        SDL_RenderFillRect(renderer, &boy);

        //Refresh de Screen
        SDL_RenderPresent(renderer);
    }

    //Finaliza os dados corretamente
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
