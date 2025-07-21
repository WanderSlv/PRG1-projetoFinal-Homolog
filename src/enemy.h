#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

// Estrutura para representar um inimigo (bola)
typedef struct Enemy {
    Vector2 position;
    float radius;
    Vector2 direction;
    int speed;
} Enemy;

// Inicializa um inimigo
void InitEnemy(Enemy *enemy, int screenWidth, int screenHeight, float radius, int speed);

// Atualiza a posição de um inimigo
void UpdateEnemy(Enemy *enemy, int screenWidth, int screenHeight);

// Desenha um inimigo
void DrawEnemy(const Enemy *enemy, Color color);

#endif