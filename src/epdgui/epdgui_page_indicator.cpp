#include "epdgui_page_indicator.h"

EPDGUI_Page_Indicator::EPDGUI_Page_Indicator(int16_t x, int16_t y, int16_t w, int16_t h, int16_t size) : EPDGUI_Base(x, y, w, h)
{
    this->_size = size;
    this->_index = 0;

    this->_Canvas = new M5EPD_Canvas(&M5.EPD);
    this->_Canvas->createCanvas(_w, _h);

    Render();
}

EPDGUI_Page_Indicator::~EPDGUI_Page_Indicator()
{
    delete this->_Canvas;
}

M5EPD_Canvas *EPDGUI_Page_Indicator::Canvas()
{
    return this->_Canvas;
}

void EPDGUI_Page_Indicator::Draw(m5epd_update_mode_t mode)
{
    if (_ishide)
    {
        return;
    }

    this->_Canvas->pushCanvas(_x, _y, mode);
}

void EPDGUI_Page_Indicator::Draw(M5EPD_Canvas *canvas)
{
    if (_ishide)
    {
        return;
    }

    _Canvas->pushToCanvas(_x, _y, canvas);
}

void EPDGUI_Page_Indicator::Bind(int16_t state, void (*func_cb)(epdgui_args_vector_t &))
{
}

void EPDGUI_Page_Indicator::UpdateState(int16_t x, int16_t y)
{
    if (!_isenable)
    {
        return;
    }
}

void EPDGUI_Page_Indicator::SetPageIndex(int16_t pageIndex){
    _index = pageIndex;
    Render();
    Draw();
}

void EPDGUI_Page_Indicator::Render()
{
    this->_Canvas->fillCanvas(GROUND_COLOR);

    if(_size<=1){
        return;
    }

    int16_t x = _w / 2 - (_size * INDICATOR_RADIUS * 2 + (_size - 1) * INDICATOR_SPACING) / 2 + INDICATOR_RADIUS;
    int16_t y = _h / 2 - INDICATOR_RADIUS / 2;

    for (int i = 0; i < _size; i++)
    {
        if (i == _index)
        {
            this->_Canvas->fillCircle(x, y, INDICATOR_SELECTED_RADIUS, INDICATOR_SELECTED_BORDER_COLOR);
            this->_Canvas->fillCircle(x, y, INDICATOR_SELECTED_RADIUS - INDICATOR_SELECTED_BORDER_WIDTH, INDICATOR_SELECTED_BACKGROUND_COLOR);
        }
        else
        {
            this->_Canvas->fillCircle(x, y, INDICATOR_RADIUS, INDICATOR_BORDER_COLOR);
            this->_Canvas->fillCircle(x, y, INDICATOR_RADIUS - INDICATOR_BORDER_WIDTH, INDICATOR_BACKGROUND_COLOR);
        }

        x += INDICATOR_RADIUS * 2 + INDICATOR_SPACING;
    }
}