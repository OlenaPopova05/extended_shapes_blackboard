#include "Board.h"
#include <iostream>
#include <sstream>

Board::Board()
    : figureID(0),
      grid(BOARD_HEIGHT, std::vector<std::pair<char, Figure*>>(BOARD_WIDTH, {'~', nullptr})) {}

void Board::addFigure(std::unique_ptr<Figure> figure) {
    if (!figure->checkDimensions(BOARD_WIDTH, BOARD_HEIGHT)) {
        std::cout << "Invalid dimensions" << std::endl;
        return;
    }
    figures.emplace_back(figureID++, std::move(figure));
    updateGrid();
}

void Board::addFigureFromFile(int id, std::unique_ptr<Figure> figure) {
    figures.emplace_back(id, std::move(figure));
    updateGrid();
}

void Board::removeLastFigure() {
    if (!figures.empty()) {
        figures.pop_back();
        updateGrid();
    }
}

void Board::clearBoard() {
    figures.clear();
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), std::make_pair('~', nullptr));
    }
}

void Board::drawBoard() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell.first;
        }
        std::cout << '\n';
    }
}

void Board::listFigures() const {
    for (const auto& [id, figure] : figures) {
        std::cout << id << " " << figure->getType()
                  << " " << figure->getParameters() << std::endl;
    }
}

std::vector<std::pair<int, std::unique_ptr<Figure>>>& Board::getBoard() {
    return figures;
}

std::string Board::getType(int figureID) const {
    for (const auto& [id, figure] : figures) {
        if (id == figureID) {
            return figure->getType();
        }
    }
    return "unknown";
}

void Board::updateGrid() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), std::make_pair('~', nullptr));
    }
    for (const auto& [id, figure] : figures) {
        if (figure->getFillType() == "fill") {
            figure->drawFilled(grid);
        } else {
            figure->draw(grid);
        }
    }
}

Figure* Board::selectByCoordinates(int x, int y) const {
    if (checkCoordinates(x, y)) {
        return grid[y][x].second;
    }
    return nullptr;
}

bool Board::checkCoordinates(int x, int y) const {
    return (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT);
}

Figure* Board::selectByID(int id) const {
    for (const auto& [figureID, figure] : figures) {
        if (figureID == id) {
            return figure.get();
        }
    }
    return nullptr;
}
