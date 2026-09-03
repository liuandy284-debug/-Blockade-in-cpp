#include <iostream>


constexpr int kW = 28;
constexpr int kL = 60;

enum BlockType{

     EMPTY = 0,
     FOOD = 1,
};

struct Map {
    BlockType map[kW][kL];
    bool isFoodEaten;
};

void initMap(Map* map){
    for(int i = 0; i < kW; i ++){
        for(int j = 0; j < kL; j ++){
            map->map[i][j] = BlockType::EMPTY;
        }
    }
    map->isFoodEaten = false;
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
    initMap(&map);
    drawMap(&map);


    //Creating a main loop 
    while(1){

    }



    return 0;
}
