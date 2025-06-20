#include "funcoes.h"

void desenha(int textoPosX, int textoPosY, int larguraJanela, int alturaJanela, const char * texto){
    int tamanhoFonte = 20;
    int tamanhoTriangulo = 18;
    float raio = 50;
    int velocidade = 5;
    bool mostrarFPS = false;
    bool inverteBolaX = false;
    int velocidadeBola = 5;
    int quantBola = 3;
    int direcaoX[quantBola];
    int direcaoY[quantBola];
    Vector2 bola[quantBola];
    bool bolaColidiu = false;

    for (int b = 0; b < quantBola; b++) {
        direcaoX[b] = 5;
        direcaoY[b] = 5;
    }

    Vector2 v1 = {textoPosX, textoPosY - tamanhoTriangulo};                    // {400,200};   v1
    Vector2 v2 = {textoPosX - tamanhoTriangulo, textoPosY + tamanhoTriangulo}; // {300,400}; v2  v3
    Vector2 v3 = {textoPosX + tamanhoTriangulo, textoPosY + tamanhoTriangulo}; // {500,400};

    // Círculo de colisão
    int raioCircColisaoPlayer = (v3.x - v2.x)/1.5;
    Vector2 circColisaoPlayer = {v2.x + raioCircColisaoPlayer, v2.y*1.1};

    SetTargetFPS(200);

    for (int b = 0; b < quantBola; b++) {
        bola[b] = (Vector2){
            GetRandomValue((int)raio, larguraJanela), GetRandomValue((int)raio, alturaJanela)
        };
    }

    clock_t tempoInicio = clock();
    clock_t tempoFim = clock();
    double tempoGasto = (double)(tempoFim - tempoInicio) / CLOCKS_PER_SEC;
    while (!WindowShouldClose()){
        int FPS = GetFPS();         // Obtém o FPS atual
        char fps[12];
        sprintf(fps, "FPS: %d", FPS);

        char tempoTotal[10];
        tempoFim = clock();
        tempoGasto = (double)(tempoFim - tempoInicio) / CLOCKS_PER_SEC;
        sprintf(tempoTotal,"%.2f", tempoGasto*10);

        // Atualiza as posições X e Y do círculo de de colisão
        circColisaoPlayer.x = v2.x + raioCircColisaoPlayer*0.8;
        circColisaoPlayer.y = v2.y - raioCircColisaoPlayer*0.7;

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

        // printf("DirX: %d, DirY: %d, bolaX = %f, bolaY = %f, larguraJanela = %d\r", direcaoX, direcaoY, bola.x, bola.y, larguraJanela);

        if ((v2.x <= 0) || (v3.x >= larguraJanela) || (v1.y <= 0) || (v3.y >= alturaJanela)) {
            tempoGasto = 0;
            printf("Você durou: %.2f, BANANÃO!\r", tempoGasto*10);
            break;
        }

        // Faz a bola andar horizontalmente
        for (int b = 0; b < quantBola; b++) {
            if (bola[b].x < raio) {
                direcaoX[b] = velocidadeBola;
            } else if (bola[b].x > larguraJanela - raio) {
                direcaoX[b] = -velocidadeBola;
            }
            bola[b].x += direcaoX[b];

            // Faz a bola andar verticalmente
            if (bola[b].y < raio) {
               direcaoY[b] = velocidadeBola;
            } else if (bola[b].y > alturaJanela - raio) {
               direcaoY[b] = -velocidadeBola;
            }
            bola[b].y += direcaoY[b];

            if (CheckCollisionCircles(circColisaoPlayer, raioCircColisaoPlayer, bola[b], raioCircColisaoPlayer)) {
                printf("COLIDIU, CACETE!!!!!!!!\n");
                printf("Pontuação: %.2f.\r", tempoGasto*10);
                bolaColidiu = true;
            }
            // printf("DirX: %d, DirY: %d, bolaX = %f, bolaY = %f, larguraJanela = %d\r", direcaoX[0], direcaoY[0], bola[0].x, bola[0].y, larguraJanela);
        }

        if (bolaColidiu) break; // Se colidiu, sai do loop

        //Desenhos na tela ↓
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(tempoTotal, larguraJanela - MeasureText(tempoTotal, tamanhoFonte*5), alturaJanela - tamanhoFonte*5, tamanhoFonte*5, WHITE); // Nome do Player

            DrawCircle(circColisaoPlayer.x, circColisaoPlayer.y, raioCircColisaoPlayer, RED);

            DrawTriangle(v1, v2, v3, BLUE); // Desenhando o triangulo // Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);

            for (int b = 0; b < quantBola; b++) {
                DrawCircle(bola[b].x, bola[b].y, raio, BLUE);
            }
            DrawText(texto, 30, 20, tamanhoFonte, WHITE); // Nome do Player

            if (mostrarFPS) DrawText(fps, 0, alturaJanela - tamanhoFonte, tamanhoFonte, WHITE);
        EndDrawing();
        printf("Você durou: %.2f, BANANÃO!\r", tempoGasto*10);
    }

    CloseWindow();
}
