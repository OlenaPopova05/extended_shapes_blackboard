#include "Board.h"
#include "Figure.h"
#include "FileHandler.h"
#include "iostream"
#include "sstream"

int main() {
    Board board;
    while (true) {
        std::cout << "Enter the command(draw/list/shapes/add+parameters/undo/clear/save+file path/load+file path): ";
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::string command;
        std::vector<std::string> parameters;
        iss >> command;
        std::string param;
        while (iss >> param) {
            parameters.push_back(param);
        }
        if (command == "draw") {
            board.drawBoard();
        } else if (command == "list") {
            board.listFigures();
        } else if (command == "shapes") {
            std::cout << "> circle coordinates radius" << std::endl;
            std::cout << "> triangle coordinates height" << std::endl;
            std::cout << "> rectangle coordinates width height" << std::endl;
            std::cout << "> line start coordinates end coordinates" << std::endl;
        } else if (command == "add") {
            if (parameters.size() < 3) {
                std::cout << "Invalid parameters" << std::endl;
                continue;
            }
            std::string shape = parameters[0];
            int x = std::stoi(parameters[1]);
            int y = std::stoi(parameters[2]);
            if (shape == "circle") {
                if (parameters.size() < 4) {
                    std::cout << "Invalid parameters" << std::endl;
                    continue;
                }
                int radius = std::stoi(parameters[3]);
                board.addFigure(std::make_unique<Circle>(x, y, radius));
            } else if (shape == "triangle") {
                if (parameters.size() < 4) {
                    std::cout << "Invalid parameters" << std::endl;
                    continue;
                }
                int height = std::stoi(parameters[3]);
                board.addFigure(std::make_unique<Triangle>(x, y, height));
            } else if (shape == "rectangle") {
                if (parameters.size() < 5) {
                    std::cout << "Invalid parameters" << std::endl;
                    continue;
                }
                int width = std::stoi(parameters[3]);
                int height = std::stoi(parameters[4]);
                board.addFigure(std::make_unique<Rectangle>(x, y, width, height));
            } else if (shape == "line") {
                if (parameters.size() < 5) {
                    std::cout << "Invalid parameters" << std::endl;
                    continue;
                }
                int x2 = std::stoi(parameters[3]);
                int y2 = std::stoi(parameters[4]);
                board.addFigure(std::make_unique<Line>(x, y, x2, y2));
            } else {
                std::cout << "Invalid shape" << std::endl;
            }
        } else if (command == "undo") {
            board.removeLastFigure();
        } else if (command == "clear") {
            board.clearBoard();
        } else if (command == "save") {
            if (parameters.size() < 1) {
                std::cout << "Invalid parameters" << std::endl;
                continue;
            }
            std::string filename = parameters[0];
            FileHandler fileHandler;
            fileHandler.save(board, filename);
        } else if (command == "load") {
            if (parameters.size() < 1) {
                std::cout << "Invalid parameters" << std::endl;
                continue;
            }
            std::string filename = parameters[0];
            FileHandler fileHandler;
            fileHandler.load(board, filename);
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }
}