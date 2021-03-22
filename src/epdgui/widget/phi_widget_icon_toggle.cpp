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

PHI_Widget_Icon_Toggle::PHI_Widget_Icon_Toggle(int16_t x, int16_t y, int16_t w, int16_t h) : PHI_Widget_Graphic_Base(x, y, w, h, true, true)
{
    BindEvent(PHI_Widget_Base::EVENT_RELEASED, &released_cb);
}

void PHI_Widget_Icon_Toggle::Render(JsonVariant data)
{
    PHI_Widget_Graphic_Base::Render(data);
    Render();
}

void PHI_Widget_Icon_Toggle::Init(JsonVariant data)
{
    _items = data["items"].as<JsonArray>();
    PHI_Widget_Graphic_Base::Init(data);
}

void PHI_Widget_Icon_Toggle::Render()
{
    String icon = _items[_index]["icon"];
    String description = _items[_index]["description"];

    this->_Canvas->drawJpgFile(SD, icon.c_str(), _w / 2 - 70, _h / 2 - 70 - 25, 140, 140);
    this->_CanvasPressed->drawJpgFile(SD, icon.c_str(), _w / 2 - 70, _h / 2 - 70 - 25, 140, 140);

    RenderDescriptionLabel(description.c_str());
}