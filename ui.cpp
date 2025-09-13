
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
    // delete _render;
}

UI::UI()
{
    //_render = new Render();
    //_render->load_resources_all();

    // menu.add_line("ПУНКТ1\n");
    // menu.add_line("ПУНКТ2\n");
    // menu.add_line("ПУНКТ3\n");

    // menu.set_rect(-50.0, 50, 200, 200);
}

void UI::mouse_move_event_up(Event *event)
{
    std::vector<Widget*>::iterator i = _widgets.begin(), e = _widgets.end();

    for (; i != e; ++i)
    {
        (*i)->on_event(event);
    }
}

void UI::mouse_click_event_up(Event *event)
{
    std::vector<Widget*>::iterator i = _widgets.begin(), e = _widgets.end();

    for (; i != e; ++i)
    {
        (*i)->on_event(event);
    }
}

void UI::draw(Render* render)
{
    render->set_viewport( _window_width, _window_height);

    render->clear();

    std::vector<Widget*>::iterator i = _widgets.begin(), e = _widgets.end();

    for (; i != e; ++i)
    {
        (*i)->draw(render);
    }

    // menu.draw(render);
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
