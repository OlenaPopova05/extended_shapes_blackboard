#pragma once
#include <string>
#include <vector>

class Figure {
protected:
    std::string filledOrFrame;
    std::string color;
public:
    Figure(std::string  filledOrFrame, std::string  color)
        : filledOrFrame(std::move(filledOrFrame)), color(std::move(color)) {}

    virtual ~Figure() = default;

    const std::string& getFillType() const { return filledOrFrame; }

    virtual void draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) = 0;

    virtual void drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) = 0;

    virtual bool checkDimensions(int boardWidth, int boardHeight) const = 0;

    virtual std::string getParameters() const = 0;

    virtual void setParameters(const std::vector<std::string>& parameters) = 0;

    virtual int getParametersCount() const = 0;

    virtual std::string getType() const = 0;

    void setColor(const std::string& newColor) { color = newColor; }
};


class Circle : public Figure {
private:
    int x, y;
    int radius;
public:
    Circle(const std::string& filledOrFrame, const std::string& color, int x, int y, int radius)
        : Figure(filledOrFrame, color), x(x), y(y), radius(radius) {}

    void draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) override;

    void drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) override;

    bool checkDimensions(int boardWidth, int boardHeight) const override;

    std::string getParameters() const override;

    void setParameters(const std::vector<std::string> &parameters) override;

    int getParametersCount() const override { return 5; }

    std::string getType() const override;
};

class Triangle : public Figure {
private:
    int x, y;
    int height;
public:
    Triangle(const std::string& filledOrFrame, const std::string& color, int x, int y, int height)
        : Figure(filledOrFrame, color), x(x), y(y), height(height) {}

    void draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) override;

    void drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) override;

    bool checkDimensions(int boardWidth, int boardHeight) const override;

    std::string getParameters() const override;

    void setParameters(const std::vector<std::string> &parameters) override;

    int getParametersCount() const override { return 5; }

    std::string getType() const override;
};

class Rectangle : public Figure {
private:
    int x, y;
    int width, height;
public:
    Rectangle(const std::string& filledOrFrame, const std::string& color, int x, int y, int width, int height)
        : Figure(filledOrFrame, color), x(x), y(y), width(width), height(height) {}

    void draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) override;

    void drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) override;

    bool checkDimensions(int boardWidth, int boardHeight) const override;

    std::string getParameters() const override;

    void setParameters(const std::vector<std::string> &parameters) override;

    int getParametersCount() const override { return 6; }

    std::string getType() const override;
};

class Line : public Figure {
private:
    int x1, y1;
    int x2, y2;
public:
    Line(const std::string& filledOrFrame, const std::string& color, int x1, int y1, int x2, int y2)
        : Figure(filledOrFrame, color), x1(x1), y1(y1), x2(x2), y2(y2) {}

    void draw(std::vector<std::vector<std::pair<char, Figure*>>>& grid) override;

    void drawFilled(std::vector<std::vector<std::pair<char, Figure*>>>& grid) override;

    bool checkDimensions(int boardWidth, int boardHeight) const override;

    std::string getParameters() const override;

    void setParameters(const std::vector<std::string> &parameters) override;

    int getParametersCount() const override { return 6; }

    std::string getType() const override;
};