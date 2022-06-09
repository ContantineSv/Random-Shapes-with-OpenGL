#include <utility>


enum class Type
{
    triangle,
    rectangle,
    circle
};


struct Point
{
    Point() = default;
    Point(const float& X, const float& Y)
        : x(X), y(Y)
    {}
    Point(const Point& p)
        : x(p.x), y(p.y)
    {}
    Point(Point&& p)
        : x(std::exchange(p.x, 0)), y(std::exchange(p.y, 0))
    {}
    Point& operator=(const Point& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    Point& operator=(Point&& p)
    {
        if (this != &p)
        {
            x = std::exchange(p.x, 0);
            y = std::exchange(p.y, 0);
        }
        return *this;
    }

    float x;
    float y;

};


class Shape
{
public:
    virtual void Draw(int width_scale, int height_scale, int step) const = 0;
};


class Triangle:public Shape
{
public:
    Triangle() = default;

    Triangle(const float& x1, const float& y1, const float& x2,
            const float& y2, const float& x3, const float& y3)
        : _p1(x1, y1), _p2(x2, y2), _p3(x3, y3) 
    {}

    Triangle (const Point& p1, const Point& p2, const Point& p3)
        : _p1(p1), _p2(p2), _p3(p3)
    {}

    Triangle (Point&& p1, Point&& p2, Point&& p3)
        : _p1(std::move(p1)), _p2(std::move(p2)), _p3(std::move(p3))
    {}

    Triangle(const Triangle& triangle)
        : _p1(triangle._p1), _p2(triangle._p2), _p3(triangle._p3)
    {}

    Triangle(Triangle&& triangle)
        : _p1(std::move(triangle._p1)), _p2(std::move(triangle._p2)),
        _p3(std::move(triangle._p3))
    {}

    Triangle& operator=(const Triangle& triangle)
    {
        _p1 = triangle._p1;
        _p2 = triangle._p2;
        _p3 = triangle._p3;
        return *this;
    }

    Triangle& operator=(Triangle&& triangle)
    {   
        if (this != &triangle)
        {
            _p1 = std::move(triangle._p1);
            _p2 = std::move(triangle._p2);
            _p3 = std::move(triangle._p3);
        }
        return *this;
    }

    void Draw(int, int, int) const override;

private:
    Point _p1;
    Point _p2;
    Point _p3;
};


class Rectangle:public Shape
{
public:
    Rectangle() = default;

    Rectangle(const float& x1, const float& y1,
                const float& x2, const float& y2)
        : _top_left(x1, y1), _bottom_right(x2, y2)
    {}

    Rectangle(const Point& top_left, const Point& bottom_right)
        : _top_left(top_left), _bottom_right(bottom_right)
    {}

    Rectangle (Point&& top_left, Point&& bottom_right)
        : _top_left(std::move(top_left)),
         _bottom_right(std::move(bottom_right))
    {}

    Rectangle(const Rectangle& rectangle)
        : _top_left(rectangle._top_left),
         _bottom_right(rectangle._bottom_right)
    {}

    Rectangle(Rectangle&& rectangle)
        : _top_left(std::move(rectangle._top_left)),
         _bottom_right(std::move(rectangle._bottom_right))
    {}

    Rectangle& operator=(const Rectangle& rectangle)
    {
        _top_left = rectangle._top_left;
        _bottom_right = rectangle._bottom_right;
        return *this;
    }

    Rectangle& operator=(Rectangle&& rectangle)
    {   
        if (this != &rectangle)
        {
            _top_left = std::move(rectangle._top_left);
            _bottom_right = std::move(rectangle._bottom_right);
        }
        return *this;
    }

    void Draw(int, int, int) const override;
private:
    Point _top_left;
    Point _bottom_right;
};


class Circle:public Shape
{
public:
    Circle() = default;

    Circle(const float& x, const float& y,
                const float r)
        : _centre(x, y), _radius(r)
    {}

    Circle(const Point& centre, const float& r)
        : _centre(centre), _radius(r)
    {}

    Circle (Point&& centre, float&& r)
        : _centre(std::move(centre)),
         _radius(std::move(r))
    {}
    
    Circle(const Circle& circle)
        : _centre(circle._centre),
         _radius(circle._radius)
    {}

    Circle(Circle&& circle)
        : _centre(std::move(circle._centre)),
         _radius(std::exchange(circle._radius, 0))
    {}

    Circle& operator=(const Circle& circle)
    {
        _centre = circle._centre;
        _radius = circle._radius;
        return *this;
    }

    Circle& operator=(Circle&& circle)
    {   
        if (this != &circle)
        {
            _centre = std::move(circle._centre);
            _radius = std::exchange(circle._radius, 0);
        }
        return *this;
    }

    void Draw(int, int, int) const override;
private:
    Point _centre;
    float _radius;
};