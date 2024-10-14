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
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        std::string type, token;
        if (line.empty() || line == "No figures on the board") {
            std::cout << "No figures on the board" << std::endl;
            return;
        }
        if (!(iss >> id >> type)) {
            std::cout << "Invalid line format: " << line << std::endl;
            return;
        }
        if (type == "line") {
            std::string from, to;
            int x1, y1, x2, y2;
            if (!(iss >> from) || from != "from") {
                std::cout << "Invalid 'from' keyword for line: " << line << std::endl;
                return;
            }
            if (!(iss >> token) || token[0] != '(' || token.back() != ',') {
                std::cout << "Invalid line start coordinates: " << line << std::endl;
                return;
            }
            x1 = std::stoi(token.substr(1));
            if (!(iss >> y1) || iss.peek() != ')') {
                std::cout << "Invalid line start coordinates: " << line << std::endl;
                return;
            }
            iss.get();
            if (!(iss >> to) || to != "to") {
                std::cout << "Invalid 'to' keyword for line: " << line << std::endl;
                return;
            }
            if (!(iss >> token) || token[0] != '(' || token.back() != ',') {
                std::cout << "Invalid line end coordinates: " << line << std::endl;
                return;
            }
            x2 = std::stoi(token.substr(1));
            if (!(iss >> y2) || iss.peek() != ')') {
                std::cout << "Invalid line end coordinates: " << line << std::endl;
                return;
            }
            iss.get();
            board.addFigureFromFile(id,std::make_unique<Line>(x1, y1, x2, y2));
        } else if (type == "circle") {
            int x, y, radius;
            if (!(iss >> token) || token[0] != '(' || token.back() != ',') {
                std::cout << "Invalid circle coordinates: " << line << std::endl;
                return;
            }
            x = std::stoi(token.substr(1));
            if (!(iss >> y) || iss.peek() != ')') {
                std::cout << "Invalid circle coordinates: " << line << std::endl;
                return;
            }
            iss.get();
            std::string param_name;
            if (!(iss >> param_name >> radius) || param_name != "radius") {
                std::cout << "Invalid circle parameters: " << line << std::endl;
                return;
            }
            board.addFigureFromFile(id, std::make_unique<Circle>(x, y, radius));
        } else if (type == "rectangle") {
            int x, y, width, height;
            if (!(iss >> token) || token[0] != '(' || token.back() != ',') {
                std::cout << "Invalid rectangle coordinates: " << line << std::endl;
                return;
            }
            x = std::stoi(token.substr(1));
            if (!(iss >> y) || iss.peek() != ')') {
                std::cout << "Invalid rectangle coordinates: " << line << std::endl;
                return;
            }
            iss.get();
            std::string param_name1, param_name2;
            if (!(iss >> param_name1 >> width >> param_name2 >> height) ||
                param_name1 != "width" || param_name2 != "height") {
                std::cout << "Invalid rectangle parameters: " << line << std::endl;
                return;
            }
            board.addFigureFromFile(id, std::make_unique<Rectangle>(x, y, width, height));
        } else if (type == "triangle") {
            int x, y, height;
            if (!(iss >> token) || token[0] != '(' || token.back() != ',') {
                std::cout << "Invalid triangle coordinates: " << line << std::endl;
                return;
            }
            x = std::stoi(token.substr(1));
            if (!(iss >> y) || iss.peek() != ')') {
                std::cout << "Invalid triangle coordinates: " << line << std::endl;
                return;
            }
            iss.get();
            std::string param_name;
            if (!(iss >> param_name >> height) || param_name != "height") {
                std::cout << "Invalid triangle parameters: " << line << std::endl;
                return;
            }
            board.addFigureFromFile(id, std::make_unique<Triangle>(x, y, height));
        } else {
            std::cout << "Unsupported figure type: " << type << std::endl;
        }
    }
    file.close();
}
