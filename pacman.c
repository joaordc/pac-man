#include "raylib.h"

#define LARGURA 800
#define ALTURA 1600

int main() {
    // Inicializacao
    InitWindow(LARGURA, ALTURA, "Come come");
    SetTargetFPS(60);

    // Loop do jogo
    while (!WindowShouldClose())
    {

    }
    
    CloseWindow();
    
    return 0;
}
