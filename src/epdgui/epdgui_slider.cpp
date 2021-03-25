#include "epdgui_slider.h"

EPDGUI_Slider::EPDGUI_Slider(int16_t x, int16_t y, int16_t w, int16_t h) : EPDGUI_Base(x, y, w, h)
{
    this->_Canvas = new M5EPD_Canvas(&M5.EPD);
    this->_Canvas->createCanvas(_w, _h);

    _min_x = BORDER_WIDTH + MARGIN;
    _max_x = _w - BORDER_WIDTH - MARGIN;

    _value = 50;

    Render();
}

EPDGUI_Slider::~EPDGUI_Slider()
{
    delete this->_Canvas;
}

void EPDGUI_Slider::Render()
{
    int16_t CORNER_RADIUS = _h / 2;
    int16_t KNOB_HEIGHT = _h - 2 * BORDER_WIDTH;
    int16_t KNOB_WIDTH = KNOB_HEIGHT;
    int16_t KNOB_CORNER_RADIUS = KNOB_HEIGHT / 2;
    int16_t usableWidth = _max_x - _min_x;
    int16_t offset = (float)GetValue() / (float)(_maxValue - _minValue) * (float)(usableWidth);
    int16_t maxOffset = _w - 2 * BORDER_WIDTH - 2 * MARGIN - KNOB_WIDTH;
    if (offset < 0) // this can actually happen as the touch are is intentionally larger than the slider itself
    {
        offset = 0;
    }
    else if (offset > maxOffset)
    {
        offset = maxOffset;
    }

    this->_Canvas->fillCanvas(GROUND_COLOR);
    this->_Canvas->fillRoundRect(MARGIN, 0, _w - MARGIN * 2, _h, CORNER_RADIUS, BORDER_COLOR);
    this->_Canvas->fillRoundRect(MARGIN + BORDER_WIDTH, BORDER_WIDTH, _w - BORDER_WIDTH * 2 - MARGIN * 2, _h - 2 * BORDER_WIDTH, CORNER_RADIUS - BORDER_WIDTH, BACKGROUND_COLOR);
    this->_Canvas->fillRoundRect(MARGIN + BORDER_WIDTH + offset, BORDER_WIDTH, KNOB_WIDTH, KNOB_HEIGHT, KNOB_CORNER_RADIUS, KNOB_COLOR);
}

void EPDGUI_Slider::SetValue(int16_t value)
{
    if (this->_value != value)
    {
        this->_value = value;
        Render();
        Draw(UPDATE_MODE_A2);
        //Draw(UPDATE_MODE_GLD16);
    }
}

M5EPD_Canvas *EPDGUI_Slider::Canvas()
{
    return this->_Canvas;
}

void EPDGUI_Slider::Draw(m5epd_update_mode_t mode)
{
    if (_hidden)
    {
        return;
    }

    this->_Canvas->pushCanvas(_x, _y, mode);
}

void EPDGUI_Slider::Draw(M5EPD_Canvas *canvas)
{
    if (_hidden)
    {
        return;
    }

    _Canvas->pushToCanvas(_x, _y, canvas);
}

void EPDGUI_Slider::BindValueChangedEvent(void (*func_cb)(epdgui_args_vector_t &))
{
    _released_cb = func_cb;
}

void EPDGUI_Slider::BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
    // todo: remove this from the base?
}

void EPDGUI_Slider::UpdateTouchState(int16_t x, int16_t y)
{
    if (!_enabled || _hidden)
    {
        return;
    }

    bool is_in_area = isInBox(x, y);

    if (is_in_area)
    {
        //if (_state == EVENT_NONE)
        {
            _state = EVENT_PRESSED;

            if (x < _min_x)
            {
                x = _min_x;
            }
            else if (x > _max_x)
            {
                x = _max_x;
            }
            float relative_x = (x - _min_x - _x) / (float)(_max_x - _min_x);
            int16_t target_value = relative_x * (_maxValue - _minValue);
            SetValue(target_value);

            Serial.println(relative_x);
            /*if (_pressed_cb != NULL)
            {
                _pressed_cb(_pressed_cb_args);
            }*/
            //Draw();
        }
    }
    else
    {
        if (_state == EVENT_PRESSED)
        {
            _state = EVENT_NONE;

            if (_released_cb != NULL)
            {
                _released_cb(_released_cb_args);
            }
            //
            //Draw();
            Draw(UPDATE_MODE_GLD16);

            /*if (x < _min_x)
            {
                x = _min_x;
            }
            else if (x > _max_x)
            {
                x = _max_x;
            }
            int16_t relative_x = (x - _min_x) / (_max_x - _min_x);
            int16_t target_value = relative_x * (_maxValue - _minValue);
            SetValue(target_value);*/
        }
    }
}

void EPDGUI_Slider::AddValueChangedEventArgs(uint16_t n, void *arg)
{

    if (_released_cb_args.size() > n)
    {
        _released_cb_args[n] = arg;
    }
    else
    {
        _released_cb_args.push_back(arg);
    }
}
