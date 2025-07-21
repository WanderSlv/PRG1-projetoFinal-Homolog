#ifndef CONFIG_H
#define CONFIG_H

typedef struct GameConfig {
    int screenWidth;
    int screenHeight;
    int playerSize;
    int playerSpeed;
    float enemyRadius;
    int enemySpeed;
    int numEnemies;
} GameConfig;

#endif