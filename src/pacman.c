#include "raylib.h"
#include "raymath.h" // usado para calcular o movimento da camera (trabalhando com Vector3)
#include "camera.h"
#include "entidade.h"

#define LARGURA 1600
#define ALTURA 840  
#define VELOCIDADE 0.25f // em segundos por passo
#define SUAVIDADE_CAMERA 0.8f // arbitrario, por tentativa e erro

int main() {
    // Inicializacao -------------------------------------------------------------------------
    InitWindow(LARGURA, ALTURA, "Come-Come Coxinha 3D");
    SetTargetFPS(60);

    // Camera -----------------------------------------------------------------
    Vector3 camPosicaoInicial = (Vector3) { 0.0f, 12.5f, 12.5f }; 

    Camera3D camera = { 0 };
    camera.position = camPosicaoInicial;
    camera.target = (Vector3){ 0.0f, 0.0f, 5.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 55.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Entidades --------------------------------------------------------------

    // Pac-man  
    Entidade pacman;
    pacman.posicao = (Vector3) { 0.5f, 0.5f, 0.5f };
    pacman.cor = YELLOW;
    pacman.sentido = direita;
    float raioPacman = 0.5f;

    // Mapa (variavel temporarias, ajustar quando tiver o vetor dinamico)

    Vector2 mapa = (Vector2) {40, 20};

    // Iniciar cronometro
    float cronometro = 0.0f;

    // Loop
    while (!WindowShouldClose())
    {
        // Atualizar -------------------------------------------------------------------------

        float tempoDelta = GetFrameTime();
        cronometro += tempoDelta;

        AtualizarCam3D(&camera, camPosicaoInicial, &pacman, mapa, tempoDelta, SUAVIDADE_CAMERA);       

        MoverEntidade(&pacman, &cronometro, VELOCIDADE);

        // Desenhar ----------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
            
            // Pacman de teste
            DrawSphere(pacman.posicao, raioPacman, pacman.cor);

            // cubos de teste
            DrawCube((Vector3){8.5f, 0.5f, 0.5f}, 1.0f, 1.0f, 5.0f, DARKBLUE);
            DrawCube((Vector3){-8.5f, 0.5f, 0.5f}, 1.0f, 1.0f, 5.0f, DARKBLUE);

            DrawGrid(20, 1.0f);

        EndMode3D();

    EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}