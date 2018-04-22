#ifndef GUITOOLBAR_IS_INCLUDED
#define GUITOOLBAR_IS_INCLUDED

#include <ysglfontdata.h>
#include "fsguibase.h"
#include "fslazywindow.h"
class ToolbarButton
{
private:
    int x0, y0;
    const int width;
    const int height;
    int fontColor[3];
    int backgroundColor[3];
    char text[256];
    bool isHovered;

public:
    ToolbarButton(int x0, int y0, char text[]): width(120), height(40)
    {
        CleanUp();
        this->x0 = x0;
        this->y0 = y0;
        this->isHovered = false;
        setFontColor(0,0,0);
        setBackgroundColor(211,211,211);
        strncpy(this->text, text, sizeof(this->text));
        this->text[sizeof(text)] = '\0';
    }

    inline void CleanUp(void)
    {
        this->x0 = 0;
        this->y0 = 0;
        this->text[0] = '\0';
    }

    inline bool isClicked(int x, int y, int lb) const {
        if (isInside(x, y) && lb == 1) {
            return true;
        } else {
            return false;
        }
    }

    void draw(void) const {
        glBegin(GL_QUADS);
        glColor3ub(this->backgroundColor[0], this->backgroundColor[1], this->backgroundColor[2]);
        glVertex2i(this->x0, this->y0);
        glVertex2i(this->x0 + this->width, this->y0);
        glVertex2i(this->x0 + this->width, this->y0 + this->height);
        glVertex2i(this->x0, this->y0 + this->height);
        glEnd();

        glColor3ub(this->fontColor[0], this->fontColor[1], this->fontColor[2]);
        glRasterPos2i(this->x0 + this->width/5, this->y0 + this->height*1.5/2);
        YsGlDrawFontBitmap12x16(this->text);
    }

    bool isInside(int x, int y) const {
        if (x >= this->x0 && y >= this->y0 && x <= (this->x0 + this->width) && (y <= this->y0 + this->height)) {
            return true;
        } else {
            return false;
        }
    }

    void setFontColor(int r, int g, int b) {
        this->fontColor[0] = r;
        this->fontColor[1] = g;
        this->fontColor[2] = b;
    }

    bool setX(int mx) {
        this->x0 = mx;
        return true;
    }

    void setBackgroundColor(int r, int g, int b) {
        this->backgroundColor[0] = r;
        this->backgroundColor[1] = g;
        this->backgroundColor[2] = b;
    }

    int getX(void) {
        return this->x0;
    }

    int getY(void) {
        return this->y0;
    }

    int getWidth(void) {
        return this->width;
    }

    int getHeight(void) {
        return this->height;
    }
};

class GUIToolbar
{
private:
    int width;
    int height;
    int x0, y0;
    std::vector <ToolbarButton> buttons;
    ToolbarButton NullButton = *new ToolbarButton(-100, -100, (char *)"");;
public:
    GUIToolbar();

    void CleanUp(void);

    void SetWidth (int width);

    void SetHeight(int height);

    void SetPosition(int x0, int y0);
    
    std::vector <ToolbarButton> GetButtons(void);

    void Draw(void) const;
    
    void addButton(char text[]);
    
    bool hover(int mx, int my);
    
    ToolbarButton getButton(int index);
    
//    FILE OpenFile(char str) const;
//    
//    void Finish(char str) const;
//    
//    void ExportImage(char str) const;
    
};
#endif