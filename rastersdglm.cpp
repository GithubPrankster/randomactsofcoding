#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "functions.h"

const static int WIDTH = 800;
const static int HEIGHT = 600;

struct Vertice{
    float vx;
    float vy;
} v10;

class Quad{
public:
    struct Vertex{
        glm::vec4 pos;
    };
    Vertex vertices[8];
    glm::mat4 modelMat;
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
    void Init(){
        vertices[0].pos = glm::vec4(-0.5,0.5 ,-0.5,1.0);
        vertices[1].pos = glm::vec4(0.5 ,0.5 ,-0.5,1.0);
        vertices[2].pos = glm::vec4(-0.5,-0.5,-0.5,1.0);
        vertices[3].pos = glm::vec4(0.5 ,-0.5,-0.5,1.0);

        vertices[4].pos = glm::vec4(-0.5,0.5 ,0.5,1.0);
        vertices[5].pos = glm::vec4(0.5 ,0.5 ,0.5,1.0);
        vertices[6].pos = glm::vec4(-0.5,-0.5,0.5,1.0);
        vertices[7].pos = glm::vec4(0.5 ,-0.5,0.5,1.0);

        pos = glm::vec3(0,0,0);
        rot = glm::vec3(0,0,0);
        scale = glm::vec3(1,1,1);
    }

    void Render(glm::mat4& viewprojection, SDL_Renderer* renderer){
        glm::mat4 matpos;
        glm::mat4 matrot;
        glm::mat4 matscale;

        matpos = glm::translate(pos);
        matscale = glm::scale(scale);
        matrot = glm::eulerAngleYXZ(rot.y, rot.x, rot.z);

        modelMat = matpos * matrot * matscale;

        glm::mat4 worldtoscreen = viewprojection *modelMat;
        Vertex screenVerts[8];
        for(int i = 0; i < 8; i++){
             screenVerts[i].pos = worldtoscreen * vertices[i].pos;
             screenVerts[i].pos /= screenVerts[i].pos.w;
             screenVerts[i].pos.x =  (screenVerts[i].pos.x * 0.5 + 0.5) * WIDTH;
             screenVerts[i].pos.y =  (screenVerts[i].pos.y * 0.5 + 0.5) * HEIGHT;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, screenVerts[0].pos.x,screenVerts[0].pos.y,screenVerts[1].pos.x,screenVerts[1].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[2].pos.x,screenVerts[2].pos.y,screenVerts[0].pos.x,screenVerts[0].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[1].pos.x,screenVerts[1].pos.y,screenVerts[3].pos.x,screenVerts[3].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[3].pos.x,screenVerts[3].pos.y,screenVerts[2].pos.x,screenVerts[2].pos.y);
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderDrawLine(renderer, screenVerts[0].pos.x,screenVerts[0].pos.y,screenVerts[4].pos.x,screenVerts[4].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[6].pos.x,screenVerts[6].pos.y,screenVerts[2].pos.x,screenVerts[2].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[5].pos.x,screenVerts[5].pos.y,screenVerts[1].pos.x,screenVerts[1].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[7].pos.x,screenVerts[7].pos.y,screenVerts[3].pos.x,screenVerts[3].pos.y);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, screenVerts[5].pos.x,screenVerts[5].pos.y,screenVerts[7].pos.x,screenVerts[7].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[6].pos.x,screenVerts[6].pos.y,screenVerts[7].pos.x,screenVerts[7].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[4].pos.x,screenVerts[4].pos.y,screenVerts[5].pos.x,screenVerts[5].pos.y);
        SDL_RenderDrawLine(renderer, screenVerts[6].pos.x,screenVerts[6].pos.y,screenVerts[4].pos.x,screenVerts[4].pos.y);
        
        

    }
};

class Camera{
public:
    glm::mat4 viewproj;
    glm::vec3 campos;
    glm::vec3 camtarget;
    void Init(){
        campos = glm::vec3(0,0,1);
        camtarget = glm::vec3(0,0,-1.0f);
    }

    void Update(){
        glm::mat4 proj = glm::perspective(30.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 500.0f);
        glm::mat4 view = glm::lookAt(campos, camtarget, glm::vec3(0,1,0));
        viewproj = proj * view;

    }
};

int main( int argc, char *argv[] ){
    srand(time(NULL));
    v10.vx = 50;
    v10.vy = 50;

    Quad quad;
    Camera camera;

    quad.Init();
    quad.pos = glm::vec3(0,0,10);

    camera.Init();

    float angle = 0;

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

    SDL_Event event;
    bool isrunning = true;

    //Loop de jogo
    while(isrunning == true){
        while( SDL_PollEvent( &event ) != 0 ){
            //Caso termine o programa
            if( event.type == SDL_QUIT ){
                isrunning = false;
            } else if (event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                case SDLK_w:
                    camera.campos.z += 0.05f;
                    break;
                case SDLK_s:
                    camera.campos.z -= 0.05f;
                    break;
                case SDLK_a:
                    camera.campos.x -= 0.05f;
                    break;
                case SDLK_d:
                    camera.campos.x += 0.05f;
                    break;
                case SDLK_q:
                    angle -= 0.1;
                    quad.rot.y -= 0.1;
                    break;
                case SDLK_e:
                    angle += 0.1;
                    quad.rot.y += 0.1;
                    break;
                case SDLK_z:
                    quad.rot.x -= 0.1;
                    break;
                case SDLK_c:
                    quad.rot.x += 0.1;
                    break;
                default:
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        //Refresh em Limpo da tela
        SDL_RenderClear(renderer);

        camera.Update(); // its important this goes before any other objects
        quad.Render(camera.viewproj,renderer);

        quad.rot.y += 0.001;
        quad.rot.x += 0.001;

        //Refresh de Screen
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
