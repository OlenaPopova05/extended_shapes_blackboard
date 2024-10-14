#pragma once
#include <string>
#include <vector>

class Figure {
public:
    Figure() = default;

    virtual ~Figure() = default;

    virtual void draw(std::vector<std::vector<char>>& board) const = 0;

    virtual bool checkDimensions(int boardWidth, int boardHeight) const = 0;

    virtual std::string getParameters() const = 0;
};


class Circle : public Figure {
private:
    int x, y;
    int radius;
public:
    Circle(int x, int y, int radius);

    void draw(std::vector<std::vector<char>>& board) const override;

    bool checkDimensions(int boardWidth, int boardHeight) const override;

    std::string getParameters() const override;
};

class Triangle : public Figure {
private:
    int x, y;
    int height;
public:
    Triangle(int x, int y, int height);

    void draw(std::vector<std::vector<char>>& board) const override;

    bool checkDimensions(int boardWidth, int boardHeight) const override;

    std::string getParameters() const override;
};

class Rectangle : public Figure {
private:
    int x, y;
    int width, height;
public:
    Rectangle(int x, int y, int width, int height);

    void draw(std::vector<std::vector<char>>& board) const override;

    bool checkDimensions(int boardWidth, int boardHeight) const override;

    std::string getParameters() const override;
};

class Line : public Figure {
private:
    int x1, y1;
    int x2, y2;
public:
    Line(int x1, int y1, int x2, int y2);

    void draw(std::vector<std::vector<char>>& board) const override;

    bool checkDimensions(int boardWidth, int boardHeight) const override;

    std::string getParameters() const override;
};