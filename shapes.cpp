#include <math.h>
#include "shapes.h"
#include "GLFW/glfw3.h"

using namespace std;

void DrawALine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
}

void Triangle::Draw(int width_scale, int height_scale, int step) const
{
    DrawALine(_p1.x * step / width_scale, _p1.y * step / height_scale,
             _p2.x * step / width_scale, _p2.y * step / height_scale );
    DrawALine(_p2.x * step / width_scale, _p2.y * step / height_scale,
             _p3.x * step / width_scale, _p3.y * step / height_scale );
    DrawALine(_p1.x * step / width_scale, _p1.y * step / height_scale,
             _p3.x * step / width_scale, _p3.y * step / height_scale );
}

void Rectangle::Draw(int width_scale, int height_scale, int step) const
{
    DrawALine(_top_left.x * step / width_scale, _top_left.y * step / height_scale,
             _top_left.x * step / width_scale, _bottom_right.y * step / height_scale );
    DrawALine(_top_left.x * step / width_scale, _bottom_right.y * step / height_scale,
             _bottom_right.x * step / width_scale, _bottom_right.y * step / height_scale );
    DrawALine(_bottom_right.x * step / width_scale, _bottom_right.y * step / height_scale,
             _bottom_right.x * step / width_scale, _top_left.y * step / height_scale );
    DrawALine( _bottom_right.x * step / width_scale, _top_left.y * step / height_scale,
             _top_left.x * step / width_scale, _top_left.y * step / height_scale );
}

void Circle::Draw(int width_scale, int height_scale, int step) const
{
    glBegin(GL_LINE_LOOP);
    
    float cx = static_cast<float>(_centre.x) * step  / width_scale;
    float cy = static_cast<float>(_centre.y) * step / height_scale;

    int num_segments = 100;

    for(int i = 0; i < num_segments; i++)
    {   
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / num_segments;

        float x = _radius * cosf(theta) * step / width_scale;
        float y = _radius * sinf(theta) * step / height_scale;

        glVertex2f(x + cx, y + cy);

    }
    glEnd();
}
