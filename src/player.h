#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

// Estrutura para representar o jogador
typedef struct Player {
    Vector2 v1; // Vértice superior do triângulo
    Vector2 v2; // Vértice inferior esquerdo
    Vector2 v3; // Vértice inferior direito
    Vector2 collisionCircleCenter; // Centro do círculo de colisão do player
    float collisionCircleRadius;   // Raio do círculo de colisão
    int speed;
    int size;
} Player;

// Inicializa o jogador
void InitPlayer(Player *player, int startX, int startY, int size, int speed);

// Atualiza a posição do jogador com base nas entradas do usuário
void UpdatePlayer(Player *player, int screenWidth, int screenHeight);

// Desenha o jogador na tela
void DrawPlayer(const Player *player, Color color);

// Verifica se o jogador colidiu com as bordas da tela
bool CheckPlayerBorderCollision(const Player *player, int screenWidth, int screenHeight);

#endif