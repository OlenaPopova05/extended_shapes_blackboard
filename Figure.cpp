#include "iostream"
#include "Figure.h"

void Circle::draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius) {
                if ((i - x) * (i - x) + (j - y) * (j - y) >= (radius - 1) * (radius - 1)) {
                    grid[i][j] = {color[0], this};
                }
            }
        }
    }
}

void Circle::drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius) {
                grid[i][j] = {color[0], this};
            }
        }
    }
}

bool Circle::checkDimensions(int boardWidth, int boardHeight) const {
    return (x - radius >= 0 && x + radius < boardWidth &&
            y - radius >= 0 && y + radius < boardHeight);
}

std::string Circle::getParameters() const {
    return " " + filledOrFrame + " " + color + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(radius);
}

void Circle::setParameters(const std::vector<std::string>& parameters) {
    filledOrFrame = parameters[0];
    color = parameters[1];
    x = std::stoi(parameters[2]);
    y = std::stoi(parameters[3]);
    radius = std::stoi(parameters[4]);
}

std::string Circle::getType() const {
    return "circle";
}

void Triangle::draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) {
    for (int i = 0; i < height; ++i) {
        int leftMost = x - i;
        int rightMost = x + i;
        int posY = y + i;
        if (posY < grid.size()) {
            if (leftMost >= 0 && leftMost < grid[0].size())
                grid[posY][leftMost] = {color[0], this};

            if (rightMost >= 0 && rightMost < grid[0].size() && leftMost != rightMost)
                grid[posY][rightMost] = {color[0], this};
        }
    }
    for (int j = 0; j < 2 * height - 1; ++j) {
        int baseX = x - height + 1 + j;
        int baseY = y + height - 1;

        if (baseX >= 0 && baseX < grid[0].size() && baseY < grid.size())
            grid[baseY][baseX] = {color[0], this};
    }
}


void Triangle::drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) {
    for (int i = 0; i < height; ++i) {
        int leftMost = x - i;
        int rightMost = x + i;
        int posY = y + i;
        if (posY < grid.size()) {
            for (int j = leftMost; j <= rightMost; ++j) {
                if (j >= 0 && j < grid[0].size())
                    grid[posY][j] = {color[0], this};
            }
        }
    }
}

bool Triangle::checkDimensions(int boardWidth, int boardHeight) const {
    return (x >= 0 && x < boardWidth && y >= 0 && y + height < boardHeight);
}

std::string Triangle::getParameters() const {
    return " " + filledOrFrame + " " + color + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(height);
}

void Triangle::setParameters(const std::vector<std::string>& parameters) {
    filledOrFrame = parameters[0];
    color = parameters[1];
    x = std::stoi(parameters[2]);
    y = std::stoi(parameters[3]);
    height = std::stoi(parameters[4]);
}

std::string Triangle::getType() const {
    return "triangle";
}

void Rectangle::draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int posX = x + j;
            int posY = y + i;

            if (posX >= 0 && posX < grid[0].size() && posY >= 0 && posY < grid.size()) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    grid[posY][posX] = {color[0], this};
                }
            }
        }
    }
}

void Rectangle::drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int posX = x + j;
            int posY = y + i;
            if (posX >= 0 && posX < grid[0].size() && posY >= 0 && posY < grid.size()) {
                grid[posY][posX] = {color[0], this};
            }
        }
    }
}

bool Rectangle::checkDimensions(int boardWidth, int boardHeight) const {
    return (x >= 0 && x + width <= boardWidth && y >= 0 && y + height <= boardHeight);
}

std::string Rectangle::getParameters() const {
    return " " + filledOrFrame + " " + color + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height);
}

void Rectangle::setParameters(const std::vector<std::string>& parameters) {
    filledOrFrame = parameters[0];
    color = parameters[1];
    x = std::stoi(parameters[2]);
    y = std::stoi(parameters[3]);
    width = std::stoi(parameters[4]);
    height = std::stoi(parameters[5]);
}

std::string Rectangle::getType() const {
    return "rectangle";
}

void Line::draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (dx == 0) {
        for (int i = std::min(y1, y2); i <= std::max(y1, y2); ++i) {
            if (i >= 0 && i < grid.size() && x1 >= 0 && x1 < grid[0].size()) {
                grid[i][x1] = {color[0], this};
            }
        }
    } else {
        for (int i = std::min(x1, x2); i <= std::max(x1, x2); ++i) {
            int j = y1 + dy * (i - x1) / dx;
            if (i >= 0 && i < grid[0].size() && j >= 0 && j < grid.size()) {
                grid[j][i] = {color[0], this};
            }
        }
    }
}

void Line::drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) {
}

bool Line::checkDimensions(int boardWidth, int boardHeight) const {
    return (x1 >= 0 && x1 < boardWidth && y1 >= 0 && y1 < boardHeight &&
            x2 >= 0 && x2 < boardWidth && y2 >= 0 && y2 < boardHeight);
}

std::string Line::getParameters() const {
    return " " + filledOrFrame + " " + color + " " + std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(x2) + " " + std::to_string(y2);
}

void Line::setParameters(const std::vector<std::string>& parameters) {
    filledOrFrame = parameters[0];
    color = parameters[1];
    x1 = std::stoi(parameters[2]);
    y1 = std::stoi(parameters[3]);
    x2 = std::stoi(parameters[4]);
    y2 = std::stoi(parameters[5]);
}

std::string Line::getType() const {
    return "line";
}