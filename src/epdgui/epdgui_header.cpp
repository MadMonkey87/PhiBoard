#include "epdgui_header.h"

EPDGUI_Header::EPDGUI_Header(int16_t x, int16_t y, int16_t w, int16_t h, String title, boolean backButton) : EPDGUI_Base(x, y, w, h)
{
    this->_Canvas = new M5EPD_Canvas(&M5.EPD);
    this->_Canvas->createCanvas(_w, _h);

    Render();
}

EPDGUI_Header::~EPDGUI_Header()
{
    delete this->_Canvas;
}

M5EPD_Canvas *EPDGUI_Header::Canvas()
{
    return this->_Canvas;
}

void EPDGUI_Header::Draw(m5epd_update_mode_t mode)
{
    if (_hidden)
    {
        return;
    }

    this->_Canvas->pushCanvas(_x, _y, mode);
}

void EPDGUI_Header::Draw(M5EPD_Canvas *canvas)
{
    if (_hidden)
    {
        return;
    }

    _Canvas->pushToCanvas(_x, _y, canvas);
}

void EPDGUI_Header::BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
    if (event == EVENT_PRESSED)
    {
        _pressed_cb = func_cb;
    }
    else if (event == EVENT_RELEASED)
    {
        _released_cb = func_cb;
    }
}

void EPDGUI_Header::UpdateTouchState(int16_t x, int16_t y)
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
            Draw();
            if (_pressed_cb != NULL)
            {
                _pressed_cb(_pressed_cb_args);
            }
        }
    }
    else
    {
        if (_state == EVENT_PRESSED)
        {
            _state = EVENT_NONE;
            Draw();
            if (_released_cb != NULL)
            {
                _released_cb(_released_cb_args);
            }
        }
    }
}

void EPDGUI_Header::AddArgs(int16_t event, uint16_t n, void *arg)
{
    if (event == EVENT_PRESSED)
    {
        if (_pressed_cb_args.size() > n)
        {
            _pressed_cb_args[n] = arg;
        }
        else
        {
            _pressed_cb_args.push_back(arg);
        }
    }
    else if (event == EVENT_RELEASED)
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
}

void EPDGUI_Header::SetTitle(String title)
{
    this->_title = title;
    Render();
    Draw();
}

void EPDGUI_Header::Render()
{
    this->_Canvas->fillCanvas(GROUND_COLOR);

    this->_Canvas->fillRect(0, 0, _w, STATUSBAR_HEIGHT, STATUSBAR_BACKGROUND_COLOR);

    //this->_Canvas->fillRect(0, 40, 80, 80, 15);
    String icon = "/Icons/70x70/back-2.jpg";
    this->_Canvas->drawJpgFile(SD, icon.c_str(), 5, 45, 70, 70);

    for (int i = 0; i < SEPARATOR_HEIGHT; i++)
    {
        this->_Canvas->drawFastHLine(SEPARATOR_HORIZONTAL_MARGIN, _h - i - 1, _w - 2 * SEPARATOR_HORIZONTAL_MARGIN, SEPARATOR_COLOR);
    }

    for (int i = 0; i < SEPARATOR_HEIGHT; i++)
    {
        this->_Canvas->drawFastVLine(85 + i, 40 + SEPARATOR_HORIZONTAL_MARGIN, 80 - SEPARATOR_HORIZONTAL_MARGIN * 2, SEPARATOR_COLOR);
    }

    this->_Canvas->setTextSize(26);
    this->_Canvas->setTextDatum(ML_DATUM);
    this->_Canvas->drawString(_title, 85 + SEPARATOR_HEIGHT + 5, (_h - STATUSBAR_HEIGHT) / 2 + STATUSBAR_HEIGHT);
}