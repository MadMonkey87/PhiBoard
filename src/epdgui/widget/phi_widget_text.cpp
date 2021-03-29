#include "phi_widget_text.h"
#include "Free_Fonts.h"

PHI_Widget_Text::PHI_Widget_Text(int16_t x, int16_t y, int16_t w, int16_t h) : PHI_Widget_Graphic_Base(x, y, w, h, true, true)
{
}

void PHI_Widget_Text::Render(JsonVariant data)
{
    PHI_Widget_Graphic_Base::Render(data);

    String description = data["description"];
    String value = data["value"];
    String hint = data["hint"];

    this->_Canvas->setFreeFont(FF18);
    this->_Canvas->setTextColor(FONT_COLOR);
    this->_Canvas->setTextDatum(MC_DATUM);
    this->_Canvas->drawString(hint.c_str(), _w / 2, 35);

    this->_CanvasPressed->setFreeFont(FF18);
    this->_CanvasPressed->setTextColor(FONT_COLOR);
    this->_CanvasPressed->setTextDatum(MC_DATUM);
    this->_CanvasPressed->drawString(hint.c_str(), _w / 2, 35);

    this->_Canvas->setFreeFont(FF24);
    this->_Canvas->setTextColor(FONT_COLOR);
    this->_Canvas->setTextDatum(MC_DATUM);
    this->_Canvas->drawString(value.c_str(), _w / 2, _h / 2);

    this->_CanvasPressed->setFreeFont(FF24);
    this->_CanvasPressed->setTextColor(FONT_COLOR);
    this->_CanvasPressed->setTextDatum(MC_DATUM);
    this->_CanvasPressed->drawString(value.c_str(), _w / 2, _h / 2);

    this->_Canvas->setFreeFont(NULL);
    this->_CanvasPressed->setFreeFont(NULL);

    RenderDescriptionLabel(description.c_str());
}