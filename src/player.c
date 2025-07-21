#include "player.h"
#include <math.h>

void InitPlayer(Player *player, int startX, int startY, int size, int speed) {
    player->size = size;
    player->speed = speed;
    player->v1 = (Vector2){(float)startX, (float)startY - size};
    player->v2 = (Vector2){(float)startX - size, (float)startY + size};
    player->v3 = (Vector2){(float)startX + size, (float)startY + size};

    // colisão
    player->collisionCircleRadius = player->size * 0.8f;
    player->collisionCircleCenter = (Vector2){
        player->v2.x + player->collisionCircleRadius * 0.8f,
        player->v2.y - player->collisionCircleRadius * 0.7f
    };
}

void UpdatePlayer(Player *player, int screenWidth, int screenHeight) {
    if (IsKeyDown(KEY_LEFT) && player->v2.x > 0) {
        player->v1.x -= player->speed;
        player->v2.x -= player->speed;
        player->v3.x -= player->speed;
    }
    if (IsKeyDown(KEY_RIGHT) && player->v3.x < screenWidth) {
        player->v1.x += player->speed;
        player->v2.x += player->speed;
        player->v3.x += player->speed;
    }
    if (IsKeyDown(KEY_UP) && player->v1.y > 0) {
        player->v1.y -= player->speed;
        player->v2.y -= player->speed;
        player->v3.y -= player->speed;
    }
    if (IsKeyDown(KEY_DOWN) && player->v3.y < screenHeight) {
        player->v1.y += player->speed;
        player->v2.y += player->speed;
        player->v3.y += player->speed;
    }

    // Atualiza o centro do círculo de colisão com base na nova posição do triângulo
    player->collisionCircleCenter = (Vector2){
        player->v2.x + player->collisionCircleRadius * 0.8f,
        player->v2.y - player->collisionCircleRadius * 0.7f
    };
}

void DrawPlayer(const Player *player, Color color) {
    DrawTriangle(player->v1, player->v2, player->v3, color);
}

bool CheckPlayerBorderCollision(const Player *player, int screenWidth, int screenHeight) {
    return (player->v2.x <= 0 || player->v3.x >= screenWidth || player->v1.y <= 0 || player->v3.y >= screenHeight);
}