
#include "node.h"
#include "camera.h"

#include "shader.h"
#include "buffer.h"
#include "texture.h"

#include "font.h"

#include "render.h"

#include "resource_manager.h"

#include "ui.h"

namespace ui {

UI::~UI()
{
    delete _render;
}

UI::UI()
{
    _render = new Render();
    _render->load_resources_all();

    menu.add_line("ПУНКТ1\n");
    menu.add_line("ПУНКТ2\n");
    menu.add_line("ПУНКТ3\n");

    menu.set_rect(-50.0, 50, 200, 200);
}

void UI::draw()
{
    _render->set_viewport( _window_width, _window_height);

    _render->clear();

    menu.draw();
}

UI* instance()
{
    static UI* _InstanceUI = nullptr;

    if (_InstanceUI == nullptr)
    {
        _InstanceUI = new UI();
    }

    return _InstanceUI;
}


}
