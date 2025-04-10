
#ifndef POPUP_MENU_H_
#define POPUP_MENU_H_

#include <string>
#include <vector>

#include "widget.h"

namespace ui {

class PopupMenu : public Widget
{
public:

    virtual void draw();

    void add_line(const std::string& line)
    {
        _lines.push_back(line);
    }

private:

    typedef std::vector<std::string> lines_type;

    lines_type _lines;
};

}

#endif //
