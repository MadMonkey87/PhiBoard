#include "phi_widget_toggle.h"

PHI_Widget_Toggle::PHI_Widget_Toggle(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Toggle_Definition *definition) : PHI_Widget_Graphic_Base(x, y, w, h, true, false)
{
    this->_definition = definition;

    this->_toggle = new EPDGUI_Toggle(_x + (_w - TOGGLE_WIDTH) / 2, _y + (_h - TOGGLE_HEIGHT) / 2, TOGGLE_WIDTH, TOGGLE_HEIGHT);
}

void PHI_Widget_Toggle::Render()
{
    PHI_Widget_Graphic_Base::Render();

    RenderDescriptionLabel(this->_definition->Description.c_str());
}

void PHI_Widget_Toggle::Draw(m5epd_update_mode_t mode)
{
    PHI_Widget_Graphic_Base::Draw(mode);

    if (_hidden)
    {
        return;
    }

    this->_toggle->Draw(mode);
}

void PHI_Widget_Toggle::Draw(M5EPD_Canvas *canvas)
{
    PHI_Widget_Graphic_Base::Draw(canvas);

    if (_hidden)
    {
        return;
    }

    this->_toggle->Draw(canvas);
}

void PHI_Widget_Toggle::BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
}

void PHI_Widget_Toggle::UpdateTouchState(int16_t x, int16_t y)
{
    if (!_enabled || _hidden)
    {
        return;
    }

    this->_toggle->UpdateTouchState(x, y);
}

PhiAction_Definition *PHI_Widget_Toggle::GetPhiAction()
{
    return this->_definition->PhiAction;
}