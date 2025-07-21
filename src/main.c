#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "config.h"

#define MAX_ENEMIES 10
#define MAX_SCORE_RECORDS 5

void DrawMenu() {
    printf("Bem-vindo ao meu joguinho: A FUJA DAS BOLAS!\n");
    printf("1 - Jogar\n");
    printf("2 - Sair\n");
    printf("3 - Opções\n");
    printf("4 - Créditos\n");
    printf("5 - Recordes\n");
    printf("Escolha uma opção: ");
}


int main() {
    GameScreen currentScreen = TITLE;
    char playerName[MAX_NAME_LENGTH] = "Jogador"; // Nome padrão
    ScoreRecord highScores[MAX_SCORE_RECORDS];
    int numHighScores = 0;
    int menuOption = 0;

    GameConfig gameConfig = {
        .screenWidth = 1280,
        .screenHeight = 720,
        .playerSize = 18,
        .playerSpeed = 5,
        .enemyRadius = 45.0f,
        .enemySpeed = 6,
        .numEnemies = 2
    };

    Player player;
    Enemy enemies[MAX_ENEMIES];
    double elapsedTime = 0.0;
    bool showFPS = false;

    SetTraceLogLevel(LOG_NONE); // Evitar logs da Raylib.

    while (1) {
        if (currentScreen == TITLE) {
            DrawMenu();
            scanf("%d", &menuOption); // Lê a opção do usuário

            switch (menuOption) {
                case 1:
                    printf("Você escolheu Jogar.\n");
                    printf("Digite seu nome: ");
                    scanf("%49s", playerName);
                    printf("(Para Jogar utilize as setinhas do seu computador!!!!)\n");
                    
                    // AQUI É ONDE A JANELA DA RAYLIB É INICIALIZADA!
                    InitWindow(gameConfig.screenWidth, gameConfig.screenHeight, "Projeto Final - Jogo");
                    SetTargetFPS(200);

                    InitGame(&gameConfig, &player, enemies, playerName); // Inicializa o jogo
                    currentScreen = GAMEPLAY;
                    break;

                case 2:
                    printf("Você escolheu Sair. Tchau!\n");
                    return 0; // Sai do game

                case 3:
                    printf("Você escolheu Opções. Ainda em desenvolvimento...\n");
                    break;

                case 4:
                    printf("Você escolheu Créditos. Feito por você!\n");
                    break;

                case 5:
                    //Janela para os recordes
                    InitWindow(gameConfig.screenWidth, gameConfig.screenHeight, "Projeto Final - Recordes");
                    SetTargetFPS(60); // FPS para a tela de recordes
                    printf("Você escolheu Recordes.\n");
                    printf("Carregando recordes...\n");
                    // Carrega os recordes do arquivo

                    LoadHighScores(highScores, &numHighScores); // Carrega os recordes
                    currentScreen = HIGHSCORES;
                    break;

                default:
                    printf("Escolha inválida! Tente novamente...\n");
                    break;
            }
            printf("\n"); //formatação para nova linha
        }

        if (currentScreen == GAMEPLAY || currentScreen == HIGHSCORES) {
            if (WindowShouldClose()) {
                CloseWindow();
                currentScreen = TITLE; // Volta para o menu do terminal
                continue;
            }

            switch (currentScreen) {
                case GAMEPLAY: {
                    if (IsKeyPressed(KEY_F)) showFPS = !showFPS;

                    bool gameOn = UpdateGame(&player, enemies, gameConfig.numEnemies, gameConfig.screenWidth, gameConfig.screenHeight, &elapsedTime);

                    DrawGame(&player, enemies, gameConfig.numEnemies, gameConfig.screenWidth, gameConfig.screenHeight, playerName, elapsedTime, showFPS);

                    if (!gameOn) {
                        printf("FIM DE JOGO! Sua pontuação: %.2f\n", elapsedTime * 10);
                        SaveHighScore(playerName, elapsedTime * 10);
                        CloseWindow();
                        currentScreen = TITLE; // Volta para o menu do terminal
                        elapsedTime = 0.0;
                    }
                } break;

                case HIGHSCORES: {
                    BeginDrawing();
                        DrawHighScores(highScores, numHighScores);
                    EndDrawing();

                    if (IsKeyPressed(KEY_ESCAPE)) {
                        CloseWindow(); // Fecha a janela de recordes
                        currentScreen = TITLE;
                    }
                } break;

                default: break;
            }
        }
    }

    CloseWindow(); //teoricamente nunca será alcançado, mas por boa pratica estarei encerrando a janela da Raylib aqui.
    printf("Obrigado por jogar!\n");
    return 0;
}