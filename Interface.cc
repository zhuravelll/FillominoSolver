
#include "Interface.h"
void Grid::show() {
    std::cout << "     "; 
    for (int x = 0; x < width; x++) {
        std::cout << std::setw(3) << x << " ";
    }
    std::cout << std::endl;
    std::cout << "    ╔";
    for (int i = 0; i < width * 4 + 1; i++) std::cout << "═";
    std::cout << "╗" << std::endl;

    for (int x = 0; x < height; x++) {
        std::cout << std::setw(2) << x << "  ║ "; 
        for (int y = 0; y < width; y++) {
            int val = cells[x * width + y];
            if (val == -1) {
                std::cout << " .  "; 
            } else {
                std::cout << std::setw(2) << val << "  ";
            }
        }
        std::cout << "║" << std::endl;
    }
    std::cout << "    ╚";
    for (int i = 0; i < width * 4 + 1; i++) std::cout << "═";
    std::cout << "╝" << std::endl;
}
void init(){
    SetConsoleOutputCP(CP_UTF8);
    std::cout<<"The programe solve Fillomino-puzzle.The main rules of this puzzle:\n1.If a cell contains the number 5, it must be part of a group of 5 cells.\n2.The cells in a group are connected only by their sides (not by their corners).\n3.Two different groups of the same size cannot touch at the sides, but they can touch at the corners.\n4.Any cells that contain 1 cannot see each other horizontally, diagonally, or vertically.\n\n";
    std::cout<<"Initial state of Fillomino-puzzle\n";
    Grid grid = initGrid();
    grid.show();

    while(true){
        std::cout<<"\nMenu:\n1.Solve Fillomino-puzzle.\n2.Finish program\n";
        int option;
        std::cin>>option;
        std::cin.ignore();

        if(option == 1){
            std::cout<<"Solved Fillomino-puzzle\n";
        }
        else if (option == 2){
            exit(0);
        }
        else {
            std::cout << "Chose correct option!" ;
        }
    }
}