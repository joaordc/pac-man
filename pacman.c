#include "raylib.h"
#include "raymath.h" // usado para calcular o movimento da camera (trabalhando com Vector3)
#include <stdio.h>

#define LARGURA 1600
#define ALTURA 840  
#define VELOCIDADE 0.25f // em segundos por passo
#define SUAVIDADE_CAMERA 0.8f // arbitrario, por tentativa e erro

typedef enum {
    cima,
    baixo,
    esquerda,
    direita
} Sentido;

typedef struct
{
    Vector3 posicao;
    Color cor;
    Sentido sentido;
} Entidade;

// Prototipos de funcao ----------------------------------------------------------------------

float funcSegGrauSuave(float); // funcao do segundo grau para movimento suave da camera

int main() {
    // Inicializacao -------------------------------------------------------------------------
    InitWindow(LARGURA, ALTURA, "Come-Come Coxinha 3D");
    SetTargetFPS(60);

    // Camera -----------------------------------------------------------------
    Vector3 cameraPosicaoInicial = (Vector3) { 0.0f, 12.5f, 12.5f }; 

    Camera3D camera = { 0 };
    camera.position = cameraPosicaoInicial;
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

    // Mapa (variaveis temporarias, ajustar quando tiver o vetor dinamico)

    int larguraMapa = 40;
    int alturaMapa = 20;

    float cronometro = 0.0f;

    while (!WindowShouldClose())
    {

        // Atualizar -------------------------------------------------------------------------

        float tempoDelta = GetFrameTime();
        cronometro += tempoDelta;

        // Interpolacao linear para movimento suave da camera -----------------

        // Target 
        Vector3 diffPacCam = Vector3Subtract(pacman.posicao, camera.target);
        camera.target.x += diffPacCam.x * tempoDelta * SUAVIDADE_CAMERA;
        camera.target.z += (diffPacCam.z) * tempoDelta * SUAVIDADE_CAMERA;

        // Eixos z e y
        Vector3 diffCamOrig = Vector3Subtract(camera.position, cameraPosicaoInicial);

        float limiteZonaAtivaZ = alturaMapa/2.0f - ((1.0f/3.0f) * alturaMapa);
        
        if (pacman.posicao.z > limiteZonaAtivaZ || pacman.posicao.z < -limiteZonaAtivaZ) {
            float diffPacZona = pacman.posicao.z - limiteZonaAtivaZ;
            float z = (diffPacZona) - (diffCamOrig.z);             
            float y = (funcSegGrauSuave(diffPacZona)) - (diffCamOrig.y); 

            camera.position.z += z * tempoDelta * SUAVIDADE_CAMERA * 3;      
            camera.position.y += y * tempoDelta * SUAVIDADE_CAMERA * 3;
        } else {
            camera.position.z -= diffCamOrig.z * tempoDelta * SUAVIDADE_CAMERA * 3; 
            camera.position.y -= diffCamOrig.y * tempoDelta * SUAVIDADE_CAMERA * 3;
        }

        // Eixo x

        float x = (pacman.posicao.x/1.2f - diffCamOrig.x);
        camera.position.x += x * tempoDelta * SUAVIDADE_CAMERA;      

        // Mover Pacman discretamente -----------------------------------------

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) pacman.sentido = direita;
        else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) pacman.sentido = esquerda;
        else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) pacman.sentido = baixo;
        else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) pacman.sentido = cima;

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
        } 

        // Desenhar ----------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
            
            // pacman de teste
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

float funcSegGrauSuave(float z) {
    return ((-1.0f/32.0f) * (z * z) - (2.0f/5.0f) * z);
}