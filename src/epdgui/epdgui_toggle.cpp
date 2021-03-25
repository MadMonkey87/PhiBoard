#include "epdgui_toggle.h"

EPDGUI_Toggle::EPDGUI_Toggle(int16_t x, int16_t y, int16_t w, int16_t h) : EPDGUI_Base(x, y, w, h)
{
    this->_CanvasNormal = new M5EPD_Canvas(&M5.EPD);
    this->_CanvasPressed = new M5EPD_Canvas(&M5.EPD);
    this->_CanvasNormal->createCanvas(_w, _h);
    this->_CanvasPressed->createCanvas(_w, _h);

    Render();
}

EPDGUI_Toggle::~EPDGUI_Toggle()
{
    delete this->_CanvasNormal;
    delete this->_CanvasPressed;
}

void EPDGUI_Toggle::Render()
{
    int16_t CORNER_RADIUS = _h / 2;
    int16_t KNOB_HEIGHT = _h - 2 * BORDER_WIDTH;
    int16_t KNOB_WIDTH = KNOB_HEIGHT;
    int16_t KNOB_CORNER_RADIUS = KNOB_HEIGHT / 2;
    int16_t offset = GetValue() ? _w - KNOB_WIDTH - 2 * BORDER_WIDTH : 0;

    this->_CanvasNormal->fillCanvas(GROUND_COLOR);
    this->_CanvasNormal->fillRoundRect(0, 0, _w, _h, CORNER_RADIUS, BORDER_COLOR);
    this->_CanvasNormal->fillRoundRect(BORDER_WIDTH, BORDER_WIDTH, _w - 2 * BORDER_WIDTH, _h - 2 * BORDER_WIDTH, CORNER_RADIUS - BORDER_WIDTH, BACKGROUND_COLOR);
    this->_CanvasNormal->fillRoundRect(BORDER_WIDTH + offset, BORDER_WIDTH, KNOB_WIDTH, KNOB_HEIGHT, KNOB_CORNER_RADIUS, KNOB_COLOR);

    this->_CanvasPressed->fillCanvas(15 - GROUND_COLOR);
    this->_CanvasPressed->fillRoundRect(0, 0, _w, _h, CORNER_RADIUS, 15 - BORDER_COLOR);
    this->_CanvasPressed->fillRoundRect(BORDER_WIDTH, BORDER_WIDTH, _w - 2 * BORDER_WIDTH, _h - 2 * BORDER_WIDTH, CORNER_RADIUS - BORDER_WIDTH, BACKGROUND_COLOR);
    this->_CanvasPressed->fillRoundRect(BORDER_WIDTH + offset, BORDER_WIDTH, KNOB_WIDTH, KNOB_HEIGHT, KNOB_CORNER_RADIUS, KNOB_COLOR);
    this->_CanvasPressed->ReverseColor();
}

void EPDGUI_Toggle::SetValue(int8_t value)
{
    if (this->_value != value)
    {
        this->_value = value;
        Render();
        Draw(UPDATE_MODE_GLD16);
    }
}

M5EPD_Canvas *EPDGUI_Toggle::CanvasNormal()
{
    return this->_CanvasNormal;
}

M5EPD_Canvas *EPDGUI_Toggle::CanvasPressed()
{
    return this->_CanvasPressed;
}

void EPDGUI_Toggle::Draw(m5epd_update_mode_t mode)
{
    if (_hidden)
    {
        return;
    }

    if (_state == EVENT_NONE || _state == EVENT_RELEASED)
    {
        this->_CanvasNormal->pushCanvas(_x, _y, mode);
    }
    else if (_state == EVENT_PRESSED)
    {
        this->_CanvasPressed->pushCanvas(_x, _y, mode);
    }
}

void EPDGUI_Toggle::Draw(M5EPD_Canvas *canvas)
{
    if (_hidden)
    {
        return;
    }

    if (_state == EVENT_NONE || _state == EVENT_RELEASED)
    {
        _CanvasNormal->pushToCanvas(_x, _y, canvas);
    }
    else if (_state == EVENT_PRESSED)
    {
        _CanvasPressed->pushToCanvas(_x, _y, canvas);
    }
}

void EPDGUI_Toggle::BindValueChangedEvent(void (*func_cb)(epdgui_args_vector_t &))
{
    _released_cb = func_cb;
}

void EPDGUI_Toggle::BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
    // todo: remove this from the base?
}

void EPDGUI_Toggle::UpdateTouchState(int16_t x, int16_t y)
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

            /*if (_pressed_cb != NULL)
            {
                _pressed_cb(_pressed_cb_args);
            }*/
            Draw();
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
            SetValue(!_value);
        }
    }
}

void EPDGUI_Toggle::AddValueChangedEventArgs(uint16_t n, void *arg)
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
