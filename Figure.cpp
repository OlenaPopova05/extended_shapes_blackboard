#include "iostream"
#include "Figure.h"

Circle::Circle(int x, int y, int radius) : x(x), y(y), radius(radius) {}

void Circle::draw(std::vector<std::vector<char>>& board) const {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius) {
                if ((i - x) * (i - x) + (j - y) * (j - y) >= (radius - 1) * (radius - 1)) {
                    board[i][j] = '*';
                }
            }
        }
    }
}

bool Circle::checkDimensions(int boardWidth, int boardHeight) const {
    return (x - radius >= 0 && x + radius < boardWidth &&
            y - radius >= 0 && y + radius < boardHeight);
}

std::string Circle::getParameters() const {
    return " (" + std::to_string(x) + ", " + std::to_string(y) + ") radius " + std::to_string(radius);
}

Triangle::Triangle(int x, int y, int height) : x(x), y(y), height(height) {}

void Triangle::draw(std::vector<std::vector<char>>& board) const {
    for (int i = 0; i < height; ++i) {
        int leftMost = x - i;
        int rightMost = x + i;
        int posY = y + i;
        if (posY < board.size()) {
            if (leftMost >= 0 && leftMost < board[0].size())
                board[posY][leftMost] = '*';
            if (rightMost >= 0 && rightMost < board[0].size() && leftMost != rightMost)
                board[posY][rightMost] = '*';
        }
    }
    for (int j = 0; j < 2 * height - 1; ++j) {
        int baseX = x - height + 1 + j;
        int baseY = y + height - 1;
        if (baseX >= 0 && baseX < board[0].size() && baseY < board.size())
            board[baseY][baseX] = '*';
    }
}

bool Triangle::checkDimensions(int boardWidth, int boardHeight) const {
    return (x >= 0 && x < boardWidth && y >= 0 && y + height < boardHeight);
}

std::string Triangle::getParameters() const {
    return " (" + std::to_string(x) + ", " + std::to_string(y) + ") height " + std::to_string(height);
}

Rectangle::Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

void Rectangle::draw(std::vector<std::vector<char>>& board) const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int posX = x + j;
            int posY = y + i;
            if (posX >= 0 && posX < board[0].size() && posY >= 0 && posY < board.size()) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    board[posY][posX] = '*';
                }
            }
        }
    }
}

bool Rectangle::checkDimensions(int boardWidth, int boardHeight) const {
    return (x >= 0 && x + width <= boardWidth && y >= 0 && y + height <= boardHeight);
}

std::string Rectangle::getParameters() const {
    return " (" + std::to_string(x) + ", " + std::to_string(y) + ") width " + std::to_string(width) + " height " + std::to_string(height);
}

Line::Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

void Line::draw(std::vector<std::vector<char>>& board) const {
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (dx == 0) {
        for (int i = std::min(y1, y2); i <= std::max(y1, y2); ++i) {
            if (i >= 0 && i < board.size() && x1 >= 0 && x1 < board[0].size()) {
                board[i][x1] = '*';
            }
        }
    } else {
        for (int i = std::min(x1, x2); i <= std::max(x1, x2); ++i) {
            int j = y1 + dy * (i - x1) / dx;
            if (i >= 0 && i < board[0].size() && j >= 0 && j < board.size()) {
                board[j][i] = '*';
            }
        }
    }
}

bool Line::checkDimensions(int boardWidth, int boardHeight) const {
    return (x1 >= 0 && x1 < boardWidth && y1 >= 0 && y1 < boardHeight &&
            x2 >= 0 && x2 < boardWidth && y2 >= 0 && y2 < boardHeight);
}

std::string Line::getParameters() const {
    return " from (" + std::to_string(x1) + ", " + std::to_string(y1) + ") to (" + std::to_string(x2) + ", " + std::to_string(y2) + ")";
}
