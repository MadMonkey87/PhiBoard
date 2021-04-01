#include "phi_widget_text.h"
#include "Free_Fonts.h"

PHI_Widget_Text::PHI_Widget_Text(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Text_Definition *definition) : PHI_Widget_Graphic_Base(x, y, w, h, true, true)
{
    this->_definition = definition;
}

void PHI_Widget_Text::Render()
{
    PHI_Widget_Graphic_Base::Render();

    this->_Canvas->setFreeFont(FF18);
    this->_Canvas->setTextColor(FONT_COLOR);
    this->_Canvas->setTextDatum(MC_DATUM);
    this->_Canvas->drawString(this->_definition->Hint.c_str(), _w / 2, 35);

    this->_CanvasPressed->setFreeFont(FF18);
    this->_CanvasPressed->setTextColor(FONT_COLOR);
    this->_CanvasPressed->setTextDatum(MC_DATUM);
    this->_CanvasPressed->drawString(this->_definition->Hint.c_str(), _w / 2, 35);

    this->_Canvas->setFreeFont(FF24);
    this->_Canvas->setTextColor(FONT_COLOR);
    this->_Canvas->setTextDatum(MC_DATUM);
    this->_Canvas->drawString(this->_definition->Value.c_str(), _w / 2, _h / 2);

    this->_CanvasPressed->setFreeFont(FF24);
    this->_CanvasPressed->setTextColor(FONT_COLOR);
    this->_CanvasPressed->setTextDatum(MC_DATUM);
    this->_CanvasPressed->drawString(this->_definition->Value.c_str(), _w / 2, _h / 2);

    this->_Canvas->setFreeFont(NULL);
    this->_CanvasPressed->setFreeFont(NULL);

    RenderDescriptionLabel(this->_definition->Description.c_str());
}

PhiAction_Definition *PHI_Widget_Text::GetPhiAction()
{
    return this->_definition->PhiAction;
}