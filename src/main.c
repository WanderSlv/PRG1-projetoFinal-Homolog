#include "raylib.h"
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "player.h"
#include "enemy.h"
#include "config.h" // Inclui a definição de GameConfig

#define MAX_ENEMIES 10
#define MAX_SCORE_RECORDS 5

// Função DrawMenu movida para main.c
void DrawMenu() { // Remove GameScreen currentScreen como parâmetro, não é mais necessário aqui
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
    int menuOption = 0; // Variável para ler a opção do menu

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

    // REMOVA: InitWindow(gameConfig.screenWidth, gameConfig.screenHeight, "Projeto Final - Menu");
    // REMOVA: SetTargetFPS(60);
    SetTraceLogLevel(LOG_NONE); // Pode manter aqui para evitar logs da Raylib desde o início, se quiser.

    while (1) { // Loop infinito, saímos com 'return 0'
        // A interação do menu será via terminal
        if (currentScreen == TITLE) {
            DrawMenu(); // Chama a função DrawMenu local, agora apenas exibe no terminal
            scanf("%d", &menuOption); // Lê a opção do usuário

            // Limpa o buffer de entrada para evitar problemas com leituras futuras
            // while (getchar() != '\n'); // Dependendo do sistema e do compilador, pode ser necessário

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
                    return 0; // Sai do programa

                case 3:
                    printf("Você escolheu Opções. Ainda em desenvolvimento...\n");
                    break;

                case 4:
                    printf("Você escolheu Créditos. Feito por você!\n");
                    break;

                case 5:
                    // Aqui você também precisa abrir uma janela para exibir os recordes
                    InitWindow(gameConfig.screenWidth, gameConfig.screenHeight, "Projeto Final - Recordes");
                    SetTargetFPS(60); // FPS para a tela de recordes

                    LoadHighScores(highScores, &numHighScores); // Carrega os recordes
                    currentScreen = HIGHSCORES;
                    break;

                default:
                    printf("Escolha inválida! Tente novamente...\n");
                    break;
            }
            printf("\n"); // Adiciona uma nova linha para melhor formatação no terminal
        }

        // Se estiver em uma tela gráfica, use o loop principal da Raylib
        if (currentScreen == GAMEPLAY || currentScreen == HIGHSCORES) {
            if (WindowShouldClose()) {
                CloseWindow(); // Fecha a janela da Raylib
                currentScreen = TITLE; // Volta para o menu do terminal
                continue; // Volta para o início do loop while (1)
            }

            switch (currentScreen) {
                case GAMEPLAY: {
                    if (IsKeyPressed(KEY_F)) showFPS = !showFPS;

                    bool gameOn = UpdateGame(&player, enemies, gameConfig.numEnemies, gameConfig.screenWidth, gameConfig.screenHeight, &elapsedTime);

                    DrawGame(&player, enemies, gameConfig.numEnemies, gameConfig.screenWidth, gameConfig.screenHeight, playerName, elapsedTime, showFPS);

                    if (!gameOn) {
                        printf("FIM DE JOGO! Sua pontuação: %.2f\n", elapsedTime * 10);
                        SaveHighScore(playerName, elapsedTime * 10);
                        CloseWindow(); // Fecha a janela do jogo
                        currentScreen = TITLE; // Volta para o menu do terminal
                        elapsedTime = 0.0; // Reseta o tempo
                    }
                } break;

                case HIGHSCORES: {
                    BeginDrawing();
                        DrawHighScores(highScores, numHighScores);
                    EndDrawing();

                    if (IsKeyPressed(KEY_ESCAPE)) {
                        CloseWindow(); // Fecha a janela de recordes
                        currentScreen = TITLE; // Volta para o menu do terminal
                    }
                } break;

                // OPTIONS e CREDITS também podem ter suas telas Raylib aqui se necessário
                default: break;
            }
        }
    }

    // Este CloseWindow() final nunca será alcançado devido ao 'return 0'
    // mas é bom mantê-lo para boas práticas, caso a estrutura mude.
    CloseWindow();
    return 0;
}