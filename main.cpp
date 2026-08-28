#include <iostream>


constexpr int kW = 28;
constexpr int kL = 60;

void drawMap(){
    system("cls");
    std::cout << "+";
    for(int i = 0; i < kL; i ++){
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
    for(int i = 0; i < kW; i ++){
        std::cout << "|";
        for(int j = 0; j < kL; j ++){
            std::cout << " ";
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

    drawMap();

    while(1){

    }



    return 0;
}
