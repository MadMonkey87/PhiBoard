#include "epdgui_container.h"

EPDGUI_Container::EPDGUI_Container(int16_t x, int16_t y, int16_t w, int16_t h): EPDGUI_Base(x,y,w,h)
{

}

EPDGUI_Container::EPDGUI_Container(): EPDGUI_Base()
{

}

EPDGUI_Container::~EPDGUI_Container()
{
    for(std::list<EPDGUI_Base*>::iterator p = _child_components.begin(); p != _child_components.end(); p++)
    {
        delete (*p);
    }
}

void EPDGUI_Container::AddComponent(EPDGUI_Base* component)
{
    _child_components.push_back(component);
}

void EPDGUI_Container::Draw(m5epd_update_mode_t mode)
{
    if(_hidden)
    {
        return;
    }

    for(std::list<EPDGUI_Base*>::iterator p = _child_components.begin(); p != _child_components.end(); p++)
    {
        (*p)->Draw(mode);
    }
}

void EPDGUI_Container::Draw(M5EPD_Canvas* canvas)
{
    if(_hidden)
    {
        return;
    }

    for(std::list<EPDGUI_Base*>::iterator p = _child_components.begin(); p != _child_components.end(); p++)
    {
        (*p)->Draw(canvas);
    }
}

void EPDGUI_Container::BindEvent(int16_t state, void (* func_cb)(epdgui_args_vector_t&))
{
    
}

void EPDGUI_Container::UpdateTouchState(int16_t x, int16_t y)
{
    if(!_enabled)
    {
        return;
    }

    for(std::list<EPDGUI_Base*>::iterator p = _child_components.begin(); p != _child_components.end(); p++)
    {
        (*p)->UpdateTouchState(x, y);
    }
}