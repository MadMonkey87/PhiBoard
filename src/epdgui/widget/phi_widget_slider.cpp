#include "phi_widget_slider.h"

PHI_Widget_Slider::PHI_Widget_Slider(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Slider_Definition *definition) : PHI_Widget_Graphic_Base(x, y, w, h, true, false)
{
    this->_definition = definition;

    this->_slider = new EPDGUI_Slider(_x + BORDER_WIDTH, _y + (_h - 60) / 2, _w - 2 * BORDER_WIDTH, SLIDER_HEIGHT);
}

void PHI_Widget_Slider::Render()
{
    PHI_Widget_Graphic_Base::Render();

    RenderDescriptionLabel(this->_definition->Description.c_str());
}

void PHI_Widget_Slider::Draw(m5epd_update_mode_t mode)
{
    PHI_Widget_Graphic_Base::Draw(mode);

    if (_hidden)
    {
        return;
    }

    this->_slider->Draw(mode);
}

void PHI_Widget_Slider::Draw(M5EPD_Canvas *canvas)
{
    PHI_Widget_Graphic_Base::Draw(canvas);

    if (_hidden)
    {
        return;
    }

    this->_slider->Draw(canvas);
}

void PHI_Widget_Slider::BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
}

void PHI_Widget_Slider::UpdateTouchState(int16_t x, int16_t y)
{
    if (!_enabled || _hidden)
    {
        return;
    }

    this->_slider->UpdateTouchState(x, y);
}

PhiAction_Definition *PHI_Widget_Slider::GetPhiAction()
{
    return NULL;
}