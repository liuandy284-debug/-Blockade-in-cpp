#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>



constexpr int kW = 28;
constexpr int kL = 60;

const int kDx[4] = {0, 1, 0, -1};
const int kDy[4] = {-1, 0, 1, 0};

enum BlockType{

     EMPTY = 0,
     FOOD = 1,
     SNAKE = 2,
     HEAD = 3,
};

struct Map {
    BlockType map[kW][kL];
    bool isFoodEaten;
};

struct Position{
    int x;
    int y;
};
struct Snake{
    Position snake[kW * kL];
    int length;
    int direction;
};

void initSnake(Snake* snake){
    snake->length = 1;
    snake->direction = 1;
    snake->snake[0] = {kW / 2, kL / 2};
}

void initMap(Map* map){
    for(int i = 0; i < kW; i ++){
        for(int j = 0; j < kL; j ++){
            map->map[i][j] = BlockType::EMPTY;
        }
    }
    map->isFoodEaten = false;
}

bool generateFood(Map* map){
    int emptyCound = 0;
    for(int i = 0; i < kW; i  ++){
        for(int j = 0; j < kL; j ++){
            if(map -> map[i][j] == BlockType::EMPTY){
                emptyCound ++;
            }
        }
    
    }
    if(emptyCound == 0){
        return false;
    }
    int k = rand() % emptyCound;
    for(int i = 0; i < kW; i ++){
        for(int j = 0; j < kL; j ++){
            if(map -> map[i][j] == BlockType::EMPTY){
                if(k == 0){
                    map -> map[i][j] = BlockType::FOOD;
                    return true;
                }
                k --;
            }
        }
    }
    return false;
}

int readDirection(const Snake* snake){
    int next  = snake->direction;
    while(_kbhit()){
        int key = _getch();
        int want = -1;
        if(key == 0 || key == 224){
            key = _getch();
            if(key == 72){
                want = 0;
            }
            else if(key == 80){
                want = 2;
            }
            else if(key == 75){
                want = 3;
            }
            else if(key == 77){
                want = 1;
            }
        } else{
            if(key == 'w' || key == 'W'){
                want = 0;
            }
            else if(key == 's' || key == 'S'){
                want = 2;
            }
            else if(key == 'a' || key == 'A'){
                want = 3;
            }
            else if(key == 'd' || key == 'D'){
                want = 1;
            }
        }
        if(want != -1 && want != (snake->direction + 2) % 4){
            next = want;
        }
    }
    return next;
}

bool moveSnake(Snake* snake, Map* map){
    Position head = snake -> snake[0];
    Position next = {head.x + kDx[snake->direction], head.y + kDy[snake->direction]};
    if(next.x < 0 || next.x >= kW || next.y < 0 || next.y >= kL){
        return false;
    }
    bool ate = (map->map[next.x][next.y] == BlockType::FOOD);
    if(!ate){
        Position tail = snake->snake[snake->length - 1];
        map->map[tail.x][tail.y] = BlockType::EMPTY;
    }
    if(map->map[next.x][next.y] == BlockType::SNAKE){
        return false;
    }
    int length = ate ? snake->length + 1 : snake->length;
    for(int i = length - 1; i > 0; i --){
        snake->snake[i] = snake->snake[i - 1];
    }
    snake->snake[0] = next;
    snake->length = length;
    if(snake->length > 1){
        map->map[head.x][head.y] = BlockType::SNAKE;
    }
    map->map[next.x][next.y] = BlockType::HEAD;
    if(ate){
        map->isFoodEaten = true;
    }
    return true;
}

void drawMap(Map* map){
    system("cls");
    std::cout << "+";
    for(int i = 0; i < kL; i ++){
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
    for(int i = 0; i < kW; i ++){
        std::cout << "|";
        for(int j = 0; j < kL; j ++){
            if(map->map[i][j] == BlockType::EMPTY){
                std::cout << " ";
            }
            else if(map->map[i][j] == BlockType::FOOD){
                std::cout << "F";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+";
    for(int i = 0; i < kL; i ++){
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}


int main(){

    Map map;
    Snake snake;
    initMap(&map);
    drawMap(&map);
    initSnake(&snake);
    generateFood(&map);
    drawMap(&map);

    bool win = false;


    while(1){
         int delay = 150 - (snake.length - 1) * 3;
         if(delay < 60){
             delay = 60;
         }
         Sleep(delay);
         snake.direction = readDirection(&snake);
         if(!moveSnake(&snake, &map)){
             break;
         }
         if(map.isFoodEaten && !generateFood(&map)){
             win = true;
         }
         drawMap(&map, snake.length - 1);
         if(win){
            break;
         }
    }



    return 0;
}
