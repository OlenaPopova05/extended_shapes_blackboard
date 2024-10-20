#include "Board.h"
#include "Figure.h"
#include "FileHandler.h"
#include "iostream"
#include "sstream"

int main() {
    Board board;
    while (true) {
        std::cout << "> ";
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
            if (parameters.size() < 5) {
                std::cout << "Invalid parameters" << std::endl;
                continue;
            }
            std::string shape = parameters[0];
            std::string filledOrFrame = parameters[1];
            std::string color = parameters[2];
            int x = std::stoi(parameters[3]);
            int y = std::stoi(parameters[4]);
            if (shape == "circle") {
                if (parameters.size() < 6) {
                    std::cout << "Invalid parameters" << std::endl;
                    continue;
                }
                int radius = std::stoi(parameters[5]);
                board.addFigure(std::make_unique<Circle>(filledOrFrame, color, x, y, radius));
            } else if (shape == "triangle") {
                if (parameters.size() < 6) {
                    std::cout << "Invalid parameters" << std::endl;
                    continue;
                }
                int height = std::stoi(parameters[5]);
                board.addFigure(std::make_unique<Triangle>(filledOrFrame, color, x, y, height));
            } else if (shape == "rectangle") {
                if (parameters.size() < 7) {
                    std::cout << "Invalid parameters" << std::endl;
                    continue;
                }
                int width = std::stoi(parameters[5]);
                int height = std::stoi(parameters[6]);
                board.addFigure(std::make_unique<Rectangle>(filledOrFrame, color, x, y, width, height));
            } else if (shape == "line") {
                if (parameters.size() < 7) {
                    std::cout << "Invalid parameters" << std::endl;
                    continue;
                }
                if (filledOrFrame != "frame") {
                    std::cout << "Line can be frame only" << std::endl;
                    continue;
                }
                int x2 = std::stoi(parameters[5]);
                int y2 = std::stoi(parameters[6]);
                board.addFigure(std::make_unique<Line>(filledOrFrame, color, x, y, x2, y2));
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
        }
        else if (command == "select") {
            if (parameters.size() < 1) {
                std::cout << "Invalid parameters" << std::endl;
                continue;
            }
            if (parameters.size() == 1) {
                int id = std::stoi(parameters[0]);
                Figure* figure = board.selectByID(id);
                if (figure != nullptr) {
                    std::cout << "< " << figure->getType() << figure->getParameters() << std::endl;
                }
            } else if (parameters.size() == 2) {
                int x = std::stoi(parameters[0]);
                int y = std::stoi(parameters[1]);
                Figure* figure = board.selectByCoordinates(x, y);
                if (figure != nullptr) {
                    std::cout << "< " << figure->getType() << figure->getParameters() << std::endl;
                }
            } else {
                std::cout << "Invalid parameters" << std::endl;
            }
        } else if (command == "remove") {
            if (parameters.size() > 0) {
                std::cout << "Invalid parameters" << std::endl;
                continue;
            }
            board.removeSelectedFigure();
        } else if (command == "edit") {
            board.editSelectedFigure(parameters);
        } else if (command == "paint") {
            if (parameters.size() < 1) {
                std::cout << "Invalid parameters" << std::endl;
                continue;
            }
            std::string color = parameters[0];
            board.paintSelectedFigure(color);
        }else {
             std::cout << "Invalid command" << std::endl;
        }
    }
}