#include "phi_widget_icon.h"
#include "../../launcher.h"

PHI_Widget_Icon::PHI_Widget_Icon(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Icon_Definition *definition) : PHI_Widget_Graphic_Base(x, y, w, h, true, true)
{
    this->_definition = definition;
}

void PHI_Widget_Icon::Render()
{
    PHI_Widget_Graphic_Base::Render();

    this->_Canvas->drawJpgFile(SD, this->_definition->Icon->Path.c_str(), _w / 2 - 70, _h / 2 - 70 - 25, 140, 140);
    this->_CanvasPressed->drawJpgFile(SD, this->_definition->Icon->Path.c_str(), _w / 2 - 70, _h / 2 - 70 - 25, 140, 140);

    RenderDescriptionLabel(this->_definition->Description.c_str());
}

PhiAction_Definition *PHI_Widget_Icon::GetPhiAction()
{
    return this->_definition->PhiAction;
}