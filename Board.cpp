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

Figure* Board::selectByCoordinates(int x, int y) {
    if (checkCoordinates(x, y)) {
        selectedFigure = grid[y][x].second;
        return selectedFigure;
    }
    return nullptr;
}

bool Board::checkCoordinates(int x, int y) {
    return (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT);
}

Figure* Board::selectByID(int id) {
    for (const auto& [figureID, figure] : figures) {
        if (figureID == id) {
            selectedFigure = figure.get();
            return selectedFigure;
        }
    }
    return nullptr;
}

void Board::removeSelectedFigure() {
    if (!selectedFigure) {
        std::cout << "No figure selected to remove" << std::endl;
        return;
    }
    for (int i = 0; i < figures.size(); ++i) {
        if (figures[i].second.get() == selectedFigure) {
            std::string type = selectedFigure->getType();
            std::string parameters = selectedFigure->getParameters();
            figures.erase(figures.begin() + i);
            std::cout << "< " << type << parameters << " removed" << std::endl;
            selectedFigure = nullptr;
            updateGrid();
            return;
        }
    }
}

void Board::editSelectedFigure(const std::vector<std::string>& parameters) {
    if (!selectedFigure) {
        std::cout << "No figure selected to edit" << std::endl;
        return;
    }
    if (parameters.size() < selectedFigure->getParametersCount()) {
        std::cout << "Invalid parameters count" << std::endl;
        return;
    }
    selectedFigure->setParameters(parameters);
    updateGrid();
}

void Board::paintSelectedFigure(const std::string& color) {
    if (!selectedFigure) {
        std::cout << "No figure selected to paint" << std::endl;
        return;
    }
    selectedFigure->setColor(color);
    updateGrid();
}

void Board::moveSelectedFigure(int x, int y) {
    if (!selectedFigure) {
        std::cout << "No figure selected to move" << std::endl;
        return;
    }
    if (!checkCoordinates(x, y)) {
        std::cout << "Invalid coordinates" << std::endl;
        return;
    }
    int selectedIndex = -1;
    for (int i = 0; i < figures.size(); ++i) {
        if (figures[i].second.get() == selectedFigure) {
            selectedIndex = i;
            break;
        }
    }
    if (selectedIndex != -1) {
        int selectedID = figures[selectedIndex].first;
        std::unique_ptr<Figure> movedFigure = std::move(figures[selectedIndex].second);
        figures.erase(figures.begin() + selectedIndex);
        movedFigure->setNewCoordinates(x, y);
        figures.emplace_back(selectedID, std::move(movedFigure));
        std::cout << "< " << figures.back().second->getType() << figures.back().second->getParameters() << " moved" << std::endl;
    } else {
        std::cout << "Selected figure not found in the list" << std::endl;
    }
    selectedFigure = nullptr;
    updateGrid();
}

