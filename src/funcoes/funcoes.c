#include "funcoes.h"

void desenha(int textoPosX, int textoPosY, int larguraJanela, int alturaJanela, const char * texto){
    int tamanhoFonte = 20;
    int tamanhoTriangulo = 18;
    float raio = 50;
    int bolaX = GetRandomValue((int)raio, larguraJanela);
    int bolaY = GetRandomValue((int)raio, alturaJanela);
    int velocidade = 2;
    bool mostrarFPS = false;
    bool inverteBolaX = false;
    int direcaoX = 1;
    int direcaoY = 1;

    Vector2 v1 = {textoPosX, textoPosY - tamanhoTriangulo};                    // {400,200};   v1
    Vector2 v2 = {textoPosX - tamanhoTriangulo, textoPosY + tamanhoTriangulo}; // {300,400}; v2  v3
    Vector2 v3 = {textoPosX + tamanhoTriangulo, textoPosY + tamanhoTriangulo}; // {500,400};

    SetTargetFPS(400);
   
    while (!WindowShouldClose()){
        int FPS = GetFPS();         // Obtém o FPS atual
        char fps[12];
        sprintf(fps, "FPS: %d", FPS);

        if (IsKeyDown(KEY_LEFT) && v2.x > 0){
            // textoPosX--;
            v1.x -= velocidade;
            v2.x -= velocidade;
            v3.x -= velocidade;
        }

        if (IsKeyDown(KEY_RIGHT) && v3.x < larguraJanela) {
            // textoPosX++;
            v1.x += velocidade;
            v2.x += velocidade;
            v3.x += velocidade;
        }

        if (IsKeyDown(KEY_UP) && v1.y > 0) {
            // textoPosY--;
            v1.y -= velocidade;
            v2.y -= velocidade;
            v3.y -= velocidade;
        }

        if (IsKeyDown(KEY_DOWN) && v3.y < alturaJanela){
            // textoPosY++;
            v1.y += velocidade;
            v2.y += velocidade;
            v3.y += velocidade;
        }
        
        if (IsKeyPressed(KEY_COMMA) || IsKeyPressed(KEY_MINUS)) tamanhoFonte -= 2;
        if (IsKeyPressed(KEY_PERIOD)|| IsKeyPressed(KEY_KP_ADD)) tamanhoFonte += 2;
        if (IsKeyPressed(KEY_F)) mostrarFPS = !mostrarFPS;

        printf("DirX: %d, DirY: %d, bolaX = %d, bolaY = %d, larguraJanela = %d\r", direcaoX, direcaoY, bolaX, bolaY, larguraJanela);

        // Faz a bola andar horizontalmente
        if (bolaX < raio) {
            direcaoX = 1;
        } else if (bolaX > larguraJanela - raio) {
            direcaoX = -1;
        }
        bolaX += direcaoX;

        // Faz a bola andar verticalmente
        if (bolaY < raio) {
           direcaoY = 1; 
        } else if (bolaY > alturaJanela - raio) {
           direcaoY = -1; 
        }
        bolaY += direcaoY;

        //Desenhos na tela ↓
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTriangle(v1, v2, v3, BLUE); // Desenhando o triangulo // Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2); 
            DrawCircle(bolaX, bolaY, raio, BLUE);
            DrawText(texto, 30, 20, tamanhoFonte, WHITE); // Nome do Player

            if (mostrarFPS) DrawText(fps, 0, alturaJanela - tamanhoFonte, tamanhoFonte, WHITE);
        EndDrawing();
    }
    CloseWindow();
}
