#include "raylib.h"
#include "raymath.h" // usado para calcular movimento da camera
#include <stdio.h>

#define LARGURA 1600
#define ALTURA 840
#define VELOCIDADE 0.25f // em segundos por passo
#define SUAVIDADE_CAMERA 1.5f // arbitrario, por tentativa e erro

typedef enum {
    cima,
    baixo,
    esquerda,
    direita
} sentido;

typedef struct
{
    Vector3 posicao;
    Color cor;
    sentido sentido;
} Entidade;


int main() {
    // Inicializacao
    InitWindow(LARGURA, ALTURA, "Come come");
    SetTargetFPS(60);

    
    // Camera
    //----------------------------------------------------------------------------------
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 12.5f, 8.5f };   // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 10.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 70.0f;                               // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Entidades -----------------------------------------------------------------------

    // pacman visível
    Entidade pacman;
    pacman.posicao = (Vector3) { 0.5f, 0.5f, 0.5f };
    pacman.cor = YELLOW;
    pacman.sentido = direita;
    float raioPacman = 0.5f;

    DisableCursor();

    float cronometro = 0.0f;

    while (!WindowShouldClose())
    {

        // Atualizar ----------------------------------------------------------------------------

        float tempoDelta = GetFrameTime();
        cronometro += tempoDelta;

        // Interpolacao linear para movimento suave da camera -------------------

        Vector3 diferenca = Vector3Subtract(pacman.posicao, camera.target);
        camera.target.x += diferenca.x * tempoDelta * SUAVIDADE_CAMERA;
        camera.target.z += diferenca.z * tempoDelta * SUAVIDADE_CAMERA;

        // Mover Pacman discretamente -------------------------------------------

        if (IsKeyDown(KEY_D)) pacman.sentido = direita;
        else if (IsKeyDown(KEY_A)) pacman.sentido = esquerda;
        else if (IsKeyDown(KEY_S)) pacman.sentido = baixo;
        else if (IsKeyDown(KEY_W)) pacman.sentido = cima;

        if (cronometro >= VELOCIDADE){
            switch (pacman.sentido)
            {
            case direita:
                pacman.posicao.x += 1.0f;
                break;
            
            case esquerda:
                pacman.posicao.x -= 1.0f;
                break;

            case baixo:
                pacman.posicao.z += 1.0f;
                break;

            case cima:
                pacman.posicao.z -= 1.0f;
                break;
            }

            cronometro -= VELOCIDADE;
            printf("x:%f y:%f z:%f", camera.position.x, camera.position.y, camera.position.z);
        } 

        // Desenhar -----------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
            
            DrawSphere(pacman.posicao, raioPacman, pacman.cor);
            DrawCube((Vector3){0.5f, 0.5f, 0.5f}, 1.0f, 1.0f, 1.0f, DARKBLUE);

            DrawGrid(20, 1.0f);

        EndMode3D();

    EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}
