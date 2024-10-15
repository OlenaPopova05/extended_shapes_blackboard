#include "FileHandler.h"
#include <fstream>
#include "Board.h"
#include "Figure.h"
#include "iostream"
#include <sstream>

void FileHandler::save(Board& board, const std::string& file_path) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << file_path << std::endl;
    }
    if (!board.getBoard().empty()) {
        for (const auto& figure : board.getBoard()) {
            file << figure.first << " " << board.getType(figure.first) << " " << figure.second->getParameters() << std::endl;
        }
    }else {
        file << "No figures on the board" << std::endl;
    }
    file.close();
}

void FileHandler::load(Board& board, const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << file_path << std::endl;
        return;
    }
    board.clearBoard();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
        std::istringstream iss(line);
        int id;
        std::string type, filledOrFrame, color;
        if (!(iss >> id >> type >> filledOrFrame >> color)) {
            std::cout << "Invalid line format: " << line << std::endl;
            break;
        }
        if (type == "line") {
            int x1, y1, x2, y2;
            if (!(iss >> x1 >> y1 >> x2 >> y2)) {
                std::cout << "Invalid line coordinates: " << line << std::endl;
                break;
            }
            board.addFigureFromFile(id, std::make_unique<Line>(filledOrFrame, color, x1, y1, x2, y2));
        }
        else if (type == "triangle") {
            int x, y, height;
            if (!(iss >> x >> y >> height)) {
                std::cout << "Invalid triangle parameters: " << line << std::endl;
                break;
            }
            board.addFigureFromFile(id, std::make_unique<Triangle>(filledOrFrame, color, x, y, height));
        }
        else if (type == "circle") {
            int x, y, radius;
            if (!(iss >> x >> y >> radius)) {
                std::cout << "Invalid circle parameters: " << line << std::endl;
                break;
            }
            board.addFigureFromFile(id, std::make_unique<Circle>(filledOrFrame, color, x, y, radius));
        }
        else if (type == "rectangle") {
            int x, y, width, height;
            if (!(iss >> x >> y >> width >> height)) {
                std::cout << "Invalid rectangle parameters: " << line << std::endl;
                break;
            }
            board.addFigureFromFile(id, std::make_unique<Rectangle>(filledOrFrame, color, x, y, width, height));
        }
        else {
            std::cout << "Unsupported figure type: " << type << std::endl;
        }
    }
    file.close();
}
