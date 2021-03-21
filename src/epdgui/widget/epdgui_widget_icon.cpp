#include "epdgui_widget_icon.h"

EPDGUI_Widget_Icon::EPDGUI_Widget_Icon(int16_t x, int16_t y, int16_t w, int16_t h): 
EPDGUI_Widget_Graphic_Base(x, y, w, h, true, true)
{

}

void EPDGUI_Widget_Icon::Render(JsonVariant data)
{
    EPDGUI_Widget_Graphic_Base::Render(data);

    String description = data["description"];
    String icon = data["icon"];

    this->_Canvas->drawJpgFile(SD, icon.c_str(),_w/2-70,_h/2-70-25, 140,140);
    this->_CanvasPressed->drawJpgFile(SD, icon.c_str(),_w/2-70,_h/2-70-25, 140,140);

    RenderDescriptionLabel(description.c_str());
}