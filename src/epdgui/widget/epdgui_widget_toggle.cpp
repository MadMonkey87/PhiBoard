#include "epdgui_widget_toggle.h"

EPDGUI_Widget_Toggle::EPDGUI_Widget_Toggle(int16_t x, int16_t y, int16_t w, int16_t h) : EPDGUI_Widget_Graphic_Base(x, y, w, h, true, false)
{
}

void EPDGUI_Widget_Toggle::Render(JsonVariant data)
{
    EPDGUI_Widget_Graphic_Base::Render(data);

    this->Render();

    String description = data["description"];
    RenderDescriptionLabel(description.c_str());
}

void EPDGUI_Widget_Toggle::Init(JsonVariant data)
{
    String value = data["value"];
    _value = value;

    Render(data);
}

void EPDGUI_Widget_Toggle::Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
}

void EPDGUI_Widget_Toggle::UpdateState(int16_t x, int16_t y)
{
    if (!_isenable || _ishide)
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

void EPDGUI_Widget_Toggle::Render()
{
    int16_t KNOB_MARGIN = (TOGGLE_HEIGHT - TOGGLE_KNOB_HEIGHT) / 2;
    int16_t offset = _value ? TOGGLE_WIDTH - TOGGLE_KNOB_WIDTH - KNOB_MARGIN : 0;

    this->_Canvas->fillRoundRect((_w - TOGGLE_WIDTH) / 2, (_h - TOGGLE_HEIGHT) / 2, TOGGLE_WIDTH, TOGGLE_HEIGHT, TOGGLE_CORNER_RADIUS, TOGGLE_BORDER_COLOR);
    this->_Canvas->fillRoundRect((_w - TOGGLE_WIDTH) / 2 + TOGGLE_BORDER_WIDTH, (_h - TOGGLE_HEIGHT) / 2 + TOGGLE_BORDER_WIDTH, TOGGLE_WIDTH - 2 * TOGGLE_BORDER_WIDTH, TOGGLE_HEIGHT - 2 * TOGGLE_BORDER_WIDTH, TOGGLE_CORNER_RADIUS - TOGGLE_BORDER_WIDTH, TOGGLE_BACKGROUND_COLOR);
    this->_Canvas->fillRoundRect((_w - TOGGLE_WIDTH) / 2 + KNOB_MARGIN + offset, (_h - TOGGLE_HEIGHT) / 2 + KNOB_MARGIN, TOGGLE_KNOB_WIDTH, TOGGLE_KNOB_HEIGHT, TOGGLE_KNOB_CORNER_RADIUS, TOGGLE_KNOB_COLOR);
}