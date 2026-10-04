#include "raylib.h"
#include <stdbool.h>

int main(void){
    
    // INIT
    const int screenWidth = 800;
    const int screenHeight = 600;
    float timer = 0.0f;

    InitWindow(screenWidth, screenHeight, "Space Invaders");
    
    // player vars
    int speed = 300;
    Rectangle player = { 
        screenWidth / 2 - 100, // x
        500, // y
        50, // w
        50 // h
    };
    
    // bullet
    bool Shoot = false;
    int B_speed = speed + 100 ;
    Rectangle bullet = { 
        player.x + 25/2, // x
        player.y - 40, // y
        10, // w
        40 // h
    };
    
    // enemy
    bool enemyDead = false;
    int E_speed = speed - 100;
    bool TouchRightWall = false;
    float respawnInterval = 1.0f;
    Rectangle enemy = { 
        100, // x
        100, // y
        50,  // w
        50  // h
    };
    
    int score = 0;
    
    while(!WindowShouldClose()){
        
        if (IsKeyDown(KEY_RIGHT)) player.x += speed * GetFrameTime();
        else if (IsKeyDown(KEY_LEFT)) player.x -= speed * GetFrameTime();
        
        // border collision
        if (player.x + player.width > screenWidth) player.x  = screenWidth - player.width;
        if (player.x <= 0) player.x = 0;
        
        // enemy collision
        if (enemy.x + enemy.width > screenWidth){ 
            enemy.x  = screenWidth - enemy.width;
            TouchRightWall = true;
        }else if (enemy.x <= 0){ 
            enemy.x = 0;
            TouchRightWall = false;
        }
        if (TouchRightWall) { // bouncing
            enemy.x -= E_speed * GetFrameTime();
        }else if (TouchRightWall == false){
            enemy.x += E_speed * GetFrameTime();
        }
        
        // bullet
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE)) Shoot = true; // bullet input
        if (bullet.y + bullet.height  < 0 || bullet.y > screenHeight || bullet.x - bullet.width <= 0 || bullet.x > screenWidth ) Shoot = false; // out of bound logic
        if (Shoot == false){ // reseting the pos
            bullet.x = player.x + 25/2;
            bullet.y = player.y - 40;
        }
        if (CheckCollisionRecs(bullet, enemy)) enemyDead = true; // if enemy is dead
        
        BeginDrawing();
            ClearBackground(RAYWHITE);

        
            if (Shoot){
                bullet.y -= B_speed * GetFrameTime();
                
                DrawRectangleRec(bullet, YELLOW); // bullet
            }
        
            
            DrawRectangleRec(player, BLUE); // player
            
            if (!enemyDead){
                DrawRectangleRec(enemy, RED); // enemy
            }else if (enemyDead){ // reset logic
                timer += GetFrameTime();
                if (timer >= respawnInterval){
                    score += 1;
                    enemyDead = false;
                    timer -= respawnInterval;
                }
            }
            
            DrawText(TextFormat("Score: %d", score), 2, 2, 30, BLACK); // score
            
        EndDrawing();
    }    
    
    
    CloseWindow();
}