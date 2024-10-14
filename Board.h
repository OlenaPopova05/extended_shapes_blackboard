#pragma once
#include <vector>
#include "Figure.h"

class Board {
private:
    static constexpr int BOARD_WIDTH = 80;
    static constexpr int BOARD_HEIGHT = 25;
    int figureID;
    std::vector<std::pair<int, std::unique_ptr<Figure>>> figures;
    std::vector<std::vector<char>> grid;
public:
    Board();

    void addFigure(std::unique_ptr<Figure> figure);

    void addFigureFromFile(int id, std::unique_ptr<Figure> figure);

    void removeLastFigure();

    void clearBoard();

    void drawBoard() const;

    void listFigures() const;

    std::vector<std::pair<int, std::unique_ptr<Figure>>>& getBoard();

    std::string getType(int figureID) const;
};