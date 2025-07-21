#include "enemy.h"

void InitEnemy(Enemy *enemy, int screenWidth, int screenHeight, float radius, int speed) {
    enemy->radius = radius;
    enemy->speed = speed;
    enemy->position = (Vector2){
        (float)GetRandomValue((int)radius, screenWidth - (int)radius),
        (float)GetRandomValue((int)radius, screenHeight - (int)radius)
    };
    // Direção inicial aleatória
    enemy->direction = (Vector2){(float)(GetRandomValue(0, 1) * 2 - 1) * speed, (float)(GetRandomValue(0, 1) * 2 - 1) * speed};
}

void UpdateEnemy(Enemy *enemy, int screenWidth, int screenHeight) {
    // Inverte a direção horizontal se colidir com as bordas
    if (enemy->position.x - enemy->radius < 0) {
        enemy->position.x = enemy->radius;
        enemy->direction.x *= -1;
    } else if (enemy->position.x + enemy->radius > screenWidth) {
        enemy->position.x = screenWidth - enemy->radius;
        enemy->direction.x *= -1;
    }
    // Inverte a direção vertical se colidir com as bordas
    if (enemy->position.y - enemy->radius < 0) {
        enemy->position.y = enemy->radius;
        enemy->direction.y *= -1;
    } else if (enemy->position.y + enemy->radius > screenHeight) {
        enemy->position.y = screenHeight - enemy->radius;
        enemy->direction.y *= -1;
    }

    enemy->position.x += enemy->direction.x;
    enemy->position.y += enemy->direction.y;
}

void DrawEnemy(const Enemy *enemy, Color color) {
    DrawCircleV(enemy->position, enemy->radius, color);
}