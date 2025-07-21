#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "config.h"

#define MAX_SCORE_RECORDS 5
#define MAX_NAME_LENGTH 50

// Estrutura para um registro de pontuação
typedef struct ScoreRecord {
    char name[MAX_NAME_LENGTH];
    double score;
} ScoreRecord;

typedef enum GameScreen {
    TITLE = 0,
    GAMEPLAY,
    END_GAME,
    OPTIONS,
    CREDITS,
    HIGHSCORES
} GameScreen;

// Declarações das funções
void InitGame(GameConfig *config, Player *player, Enemy enemies[], const char *playerName);
bool UpdateGame(Player *player, Enemy enemies[], int numEnemies, int screenWidth, int screenHeight, double *elapsedTime);
void DrawGame(const Player *player, const Enemy enemies[], int numEnemies, int screenWidth, int screenHeight, const char *playerName, double elapsedTime, bool showFPS);

// Funções para gerenciar pontuações
void LoadHighScores(ScoreRecord highScores[], int *numRecords);
void SaveHighScore(const char *playerName, double score);
void DrawHighScores(const ScoreRecord highScores[], int numRecords);

#endif