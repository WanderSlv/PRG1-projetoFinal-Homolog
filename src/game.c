#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static clock_t gameStartTime;
#define HIGHSCORE_FILE "highscores.txt" // Pontuação

void InitGame(GameConfig *config, Player *player, Enemy enemies[], const char *playerName) {
    InitWindow(config->screenWidth, config->screenHeight, "Projeto Final - A FUJA DAS BOLAS!");
    SetTargetFPS(200);
    SetTraceLogLevel(LOG_NONE); // Remove mensagens da raylib

    InitPlayer(player, 50, 50, config->playerSize, config->playerSpeed);

    for (int i = 0; i < config->numEnemies; i++) {
        InitEnemy(&enemies[i], config->screenWidth, config->screenHeight, config->enemyRadius, config->enemySpeed);
    }
    gameStartTime = clock(); // Contador de tempo do jogo
}

bool UpdateGame(Player *player, Enemy enemies[], int numEnemies, int screenWidth, int screenHeight, double *elapsedTime) {
    UpdatePlayer(player, screenWidth, screenHeight);

    for (int i = 0; i < numEnemies; i++) {
        UpdateEnemy(&enemies[i], screenWidth, screenHeight);
        // Verifica colisão do player com cada inimigo
        if (CheckCollisionCircles(player->collisionCircleCenter, player->collisionCircleRadius, enemies[i].position, enemies[i].radius)) {
            printf("COLIDIU, CACETE!!\n");
            *elapsedTime = (double)(clock() - gameStartTime) / CLOCKS_PER_SEC; // Calcula o tempo final
            printf("Pontuação: %.2f.\n", *elapsedTime * 10);
            return false; // Game over
        }
    }

    // Verifica colisão do player com as bordas da tela
    if (CheckPlayerBorderCollision(player, screenWidth, screenHeight)) {
        printf("Você durou: %.2f, BANANÃO (bateu na borda)!\n", *elapsedTime * 10);
        return false;
    }

    *elapsedTime = (double)(clock() - gameStartTime) / CLOCKS_PER_SEC; // Atualiza o tempo a cada frame
    return true; // Jogo continua
}

void DrawGame(const Player *player, const Enemy enemies[], int numEnemies, int screenWidth, int screenHeight, const char *playerName, double elapsedTime, bool showFPS) {
    BeginDrawing();
        ClearBackground(BLACK);

        // Desenha a tempo "pontuação"
        char timeText[20];
        sprintf(timeText, "Pontos: %.2f", elapsedTime * 10);
        DrawText(timeText, screenWidth - MeasureText(timeText, 30) - 20, 20, 30, WHITE); // AGORA ESTÁ CERTO!

        // Desenha o nome do jogador
        DrawText(playerName, 30, 20, 20, WHITE);

        DrawPlayer(player, BLUE);

        for (int i = 0; i < numEnemies; i++) {
            DrawEnemy(&enemies[i], BLUE);
        }

        if (showFPS) {
            char fpsText[15];
            sprintf(fpsText, "FPS: %d", GetFPS());
            DrawText(fpsText, 10, screenHeight - 30, 20, WHITE);
        }
    EndDrawing();
}

// Funções de pontuação (carregar, salvar, desenhar)
void LoadHighScores(ScoreRecord highScores[], int *numRecords) {
    FILE *file = fopen(HIGHSCORE_FILE, "r");
    if (file == NULL) {
        *numRecords = 0;
        return;
    }

    int i = 0;
    while (i < MAX_SCORE_RECORDS && fscanf(file, "%49s %lf", highScores[i].name, &highScores[i].score) == 2) {
        i++;
    }
    *numRecords = i;
    fclose(file);

    // Ordenar os recordes do maior para o menor
    for (int j = 0; j < *numRecords - 1; j++) {
        for (int k = j + 1; k < *numRecords; k++) {
            if (highScores[j].score < highScores[k].score) {
                ScoreRecord temp = highScores[j];
                highScores[j] = highScores[k];
                highScores[k] = temp;
            }
        }
    }
}

void SaveHighScore(const char *playerName, double score) {
    ScoreRecord highScores[MAX_SCORE_RECORDS];
    int numRecords = 0;

    LoadHighScores(highScores, &numRecords); // Carrega os recordes existentes

    // Verifica se a nova pontuação é alta o suficiente para entrar na lista
    if (numRecords < MAX_SCORE_RECORDS || (numRecords > 0 && score > highScores[numRecords - 1].score)) {
        // Adiciona o novo recorde
        if (numRecords < MAX_SCORE_RECORDS) {
            numRecords++;
        }
        strcpy(highScores[numRecords - 1].name, playerName);
        highScores[numRecords - 1].score = score;

        // Reordena a lista (do maior para o menor)
        for (int j = 0; j < numRecords - 1; j++) {
            for (int k = j + 1; k < numRecords; k++) {
                if (highScores[j].score < highScores[k].score) {
                    ScoreRecord temp = highScores[j];
                    highScores[j] = highScores[k];
                    highScores[k] = temp;
                }
            }
        }
        if (numRecords > MAX_SCORE_RECORDS) {
            numRecords = MAX_SCORE_RECORDS;
        }

        // Salva a lista atualizada no arquivo
        FILE *file = fopen(HIGHSCORE_FILE, "w");
        if (file != NULL) {
            for (int i = 0; i < numRecords; i++) {
                fprintf(file, "%s %.2f\n", highScores[i].name, highScores[i].score);
            }
            fclose(file);
        } else {
            printf("Erro: Não foi possível abrir o arquivo de recordes para escrita.\n");
        }
    }
}

void DrawHighScores(const ScoreRecord highScores[], int numRecords) {
    ClearBackground(BLACK);
    DrawText("MELHORES PONTUAÇÕES", GetScreenWidth()/2 - MeasureText("MELHORES PONTUAÇÕES", 40)/2, 50, 40, YELLOW);

    for (int i = 0; i < numRecords; i++) {
        char scoreText[100];
        sprintf(scoreText, "%d. %s: %.2f", i + 1, highScores[i].name, highScores[i].score);
        DrawText(scoreText, GetScreenWidth()/2 - MeasureText(scoreText, 30)/2, 150 + i * 40, 30, RAYWHITE);
    }

    DrawText("Pressione ESC para voltar ao menu", GetScreenWidth()/2 - MeasureText("Pressione ESC para voltar ao menu", 20)/2, GetScreenHeight() - 50, 20, GRAY);
}