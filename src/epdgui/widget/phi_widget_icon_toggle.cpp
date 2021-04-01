#include "phi_widget_icon_toggle.h"

void released_cb(epdgui_args_vector_t &args)
{
    Serial.println("pressed");
    /*_index++;
    if (_index >= _items.size())
    {
        _index = 0;
    }*/
}

PHI_Widget_Icon_Toggle::PHI_Widget_Icon_Toggle(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Icon_Toggle_Definition *definition) : PHI_Widget_Graphic_Base(x, y, w, h, true, true)
{
    this->_definition = definition;

    BindEvent(PHI_Widget_Base::EVENT_RELEASED, &released_cb);
}

void PHI_Widget_Icon_Toggle::Render()
{
    PHI_Widget_Graphic_Base::Render();
    RenderInternal();
}

void PHI_Widget_Icon_Toggle::Init()
{
    PHI_Widget_Graphic_Base::Init();
}

void PHI_Widget_Icon_Toggle::RenderInternal()
{
    /*String icon = _items[_index]["icon"];
    String description = _items[_index]["description"];

    this->_Canvas->drawJpgFile(SD, icon.c_str(), _w / 2 - 70, _h / 2 - 70 - 25, 140, 140);
    this->_CanvasPressed->drawJpgFile(SD, icon.c_str(), _w / 2 - 70, _h / 2 - 70 - 25, 140, 140);

    RenderDescriptionLabel(description.c_str());*/
}

PhiAction_Definition *PHI_Widget_Icon_Toggle::GetPhiAction()
{
    return NULL;
}