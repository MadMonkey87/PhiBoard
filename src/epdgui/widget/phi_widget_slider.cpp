#include "phi_widget_slider.h"

PHI_Widget_Slider::PHI_Widget_Slider(int16_t x, int16_t y, int16_t w, int16_t h) : PHI_Widget_Graphic_Base(x, y, w, h, true, false)
{
}

void PHI_Widget_Slider::Render(JsonVariant data)
{
    PHI_Widget_Graphic_Base::Render(data);

    this->Render();

    String description = data["description"];
    RenderDescriptionLabel(description.c_str());
}

void PHI_Widget_Slider::Init(JsonVariant data)
{
    Render(data);
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

    bool is_in_area = isInBox(x, y);

    if (is_in_area)
    {
        if (_state == EVENT_NONE)
        {
            _state = EVENT_PRESSED;
        }
    }
    else
    {
        if (_state != EVENT_NONE)
        {
            _state = EVENT_NONE;
            if (x == -1 && y == -1)
            {
                _value = !_value;
                this->Render();
                Draw();
            }
        }
    }
}

void PHI_Widget_Slider::Render()
{
    
}