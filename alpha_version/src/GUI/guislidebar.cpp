#include "guislidebar.h"

GuiSlideBar::GuiSlideBar()
{
    CleanUp();
}

void GuiSlideBar::CleanUp(void)
{
    lengthInPixel = 0;
    heightInPixel = 0;
    x0 = 300;
    y0 = 700;
    percent = 0.5;
}

void GuiSlideBar::SetLength(int lengthInPixel)
{
    this -> lengthInPixel = lengthInPixel;
}

void GuiSlideBar::SetHeight(int heightInPixel)
{
    this -> heightInPixel = heightInPixel;
}

void GuiSlideBar::SetPosition(double x0, double y0)
{
    this -> x0 = x0;
    this -> y0 = y0;
}

void GuiSlideBar::SetDragging(bool isDragging)
{
    this -> isDragging = isDragging;
}

bool GuiSlideBar::GetDragging(void) const
{
    return this -> isDragging;
}

void GuiSlideBar::Show(void) const
{
    double color = 0.0;
    double colorSpan = 0.0005;
    double posX = x0 + lengthInPixel * percent;
    double posY = y0 - recHeightOffset;

    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(x0, y0);
    glVertex2f(x0 + lengthInPixel, y0);
    glVertex2f(x0 + lengthInPixel, y0);
    glVertex2f(x0 + lengthInPixel, y0 + heightInPixel);
    glVertex2f(x0 + lengthInPixel, y0 + heightInPixel);
    glVertex2f(x0, y0 + heightInPixel);
    glVertex2f(x0, y0 + heightInPixel);
    glVertex2f(x0, y0);
    glEnd();
    glBegin(GL_POINTS);
    for (double x = x0; x <= x0 + lengthInPixel; x += 0.4)
    {
        color += colorSpan;
        glColor3f(color, color, color);
        for (double y = y0; y <= y0 + heightInPixel; y += 0.4)
        {
            glVertex2f(x, y); 
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(131, 139, 139);
    glVertex2f(posX - recWidth / 2, posY);
    glVertex2f(posX + recWidth / 2, posY);
    glVertex2f(posX + recWidth / 2, posY + heightInPixel + 2 * recHeightOffset);
    glVertex2f(posX - recWidth / 2, posY + heightInPixel + 2 * recHeightOffset);
    glEnd();
}

bool GuiSlideBar::IsInside(int mx, int my) const
{
    double posX = x0 + lengthInPixel * percent;
    double posY = y0 - recHeightOffset;
    if (mx >= posX - recWidth / 2 && mx <= posX + recWidth / 2
        && my >= posY && my <= posY + heightInPixel + 2 * recHeightOffset)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GuiSlideBar::Move(int mx, int my)
{
    if (mx < x0)
    {
        mx = x0;
    }
    if (mx > x0 + lengthInPixel)
    {
        mx = x0 + lengthInPixel;
    }
    this -> percent = ((double)mx - x0) / lengthInPixel;
}

double GuiSlideBar::GetPercent(void) const
{
    return percent;
}
