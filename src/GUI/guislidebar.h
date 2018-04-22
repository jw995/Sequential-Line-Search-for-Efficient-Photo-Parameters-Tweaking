#ifndef GUISLIDEBAR_IS_INCLUDED
#define GUISLIDEBAR_IS_INCLUDED

#include "fsguibase.h"
#include "fslazywindow.h"

class GuiSlideBar : public FsGuiObject
{
private:
    int lengthInPixel;
    int heightInPixel;
    double x0, y0, percent;
    const int recHeightOffset = 7;
    const int recWidth = 20;
    bool isDragging;
public:
    GuiSlideBar();

    void CleanUp(void);

    void SetLength(int lengthInPixel);

    void SetHeight(int heightInPixel);

    void SetPosition(double x0, double y0);

    void SetDragging(bool isDragging);

    bool GetDragging(void) const;

    void Show(void) const;

    bool IsInside(int mx, int my) const;

    void Move(int mx, int my);

    double GetPercent(void) const;
};
#endif