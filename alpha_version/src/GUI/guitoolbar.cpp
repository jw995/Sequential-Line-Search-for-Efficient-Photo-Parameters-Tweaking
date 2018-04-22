#include "guitoolbar.h"

#include <ysglfontdata.h>

GUIToolbar::GUIToolbar()
{
    CleanUp();
}

void GUIToolbar::CleanUp(void) {
    this->buttons.clear();
    this->width = 1200;
    this->height = 40;
    this->x0 = 0;
    this->y0 = 0;
}

void GUIToolbar::SetWidth(int width) 
{
    this->width = width;
}

void GUIToolbar::SetHeight(int height)
{
    this->height = height;
}

void GUIToolbar::SetPosition(int x0, int y0) 
{
    this->x0 = x0;
    this->y0 = y0;
}

void GUIToolbar::Draw(void) const 
{
    glBegin(GL_QUADS);
    glColor3ub(211, 211, 211);
    glVertex2i(this->x0, this->y0);
    glVertex2i(this->x0 + this->width, this->y0);
    glVertex2i(this->x0 + this->width, this->y0 + this->height);
    glVertex2i(this->x0, this->y0 + this->height);
    glEnd();
}

void GUIToolbar::addButton(char text[]) {
    int x, y, width;
    if (this->buttons.size() > 0) {
        x = this->buttons[this->buttons.size()-1].getX();
        y = this->buttons[this->buttons.size()-1].getY();
        width = this->buttons[buttons.size()-1].getWidth();
    } else {
        x = 0;
        y = 0;
        width = 0;
    }
    auto newButton = new ToolbarButton(x + width, y, text);
    this->buttons.push_back(*newButton);
}

std::vector <ToolbarButton> GUIToolbar::GetButtons(void) {
    return this->buttons;
}

bool GUIToolbar::hover(int mx, int my) {
    for (auto &btn: this->buttons) {
        if (mx >= btn.getX() && my >= btn.getY() && mx <= (btn.getX() + btn.getWidth()) && my < (btn.getY() + btn.getHeight())) {
            btn.setFontColor(255,255,255);
            btn.setBackgroundColor(0,0,255);
        }
        else
        {
            btn.setFontColor(0,0,0);
            btn.setBackgroundColor(211,211,211);
        }
    }
    return false;
}

ToolbarButton GUIToolbar::getButton(int index) {
    int btnIdx = 0;
    for (auto &btn: this->buttons) {
        if (index == btnIdx) {
            return btn;
        }
        btnIdx++;
    }
    return this->NullButton;
}
//
//FILE GUIToolbar::OpenFile(char str) const 
//{
//
//}
//
//void GUIToolbar::Finish(char str) const 
//{
//
//}
//
//void GUIToolbar::ExportImage(char str) const 
//{
//
//}
    
    