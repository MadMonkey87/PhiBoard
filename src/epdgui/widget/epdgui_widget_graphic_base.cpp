#include "epdgui_widget_graphic_base.h"

EPDGUI_Widget_Graphic_Base::EPDGUI_Widget_Graphic_Base(int16_t x, int16_t y, int16_t w, int16_t h, boolean createNormalCanvas, boolean createPressedCanvas) : EPDGUI_Widget_Base(x, y, w, h)
{
    if (createNormalCanvas)
    {
        this->_Canvas = new M5EPD_Canvas(&M5.EPD);
        this->_Canvas->createCanvas(_w, _h);
    }

    if (createPressedCanvas)
    {
        this->_CanvasPressed = new M5EPD_Canvas(&M5.EPD);
        this->_CanvasPressed->createCanvas(_w, _h);
    }
}

EPDGUI_Widget_Graphic_Base::~EPDGUI_Widget_Graphic_Base()
{
    if (this->_Canvas != NULL)
    {
        delete this->_Canvas;
    }

    if (this->_CanvasPressed != NULL)
    {
        delete this->_CanvasPressed;
    }
}

void EPDGUI_Widget_Graphic_Base::Draw(m5epd_update_mode_t mode)
{
    if (_ishide)
    {
        return;
    }

    if (this->_Canvas != NULL && _state == EVENT_NONE || _state == EVENT_RELEASED)
    {
        this->_Canvas->pushCanvas(_x, _y, mode);
    }
    else if (this->_CanvasPressed != NULL && _state == EVENT_PRESSED)
    {
        this->_CanvasPressed->pushCanvas(_x, _y, mode);
    }
}

void EPDGUI_Widget_Graphic_Base::Draw(M5EPD_Canvas *canvas)
{
    if (_ishide)
    {
        return;
    }

    if (_Canvas != NULL && _state == EVENT_NONE || _state == EVENT_RELEASED)
    {
        _Canvas->pushToCanvas(_x, _y, canvas);
    }
    else if (_CanvasPressed != NULL && _state == EVENT_PRESSED)
    {
        _CanvasPressed->pushToCanvas(_x, _y, canvas);
    }
}

void EPDGUI_Widget_Graphic_Base::Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
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

void EPDGUI_Widget_Graphic_Base::UpdateState(int16_t x, int16_t y)
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
            if (_pressed_cb != NULL)
            {
                _pressed_cb(_pressed_cb_args);
            }
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
            Draw();
        }
    }
}

void EPDGUI_Widget_Graphic_Base::Init(JsonVariant data)
{
    Render(data);

    if (this->_CanvasPressed != NULL)
    {
        this->_CanvasPressed->ReverseColor();
    }
}

void EPDGUI_Widget_Graphic_Base::Render(JsonVariant data)
{
    if (this->_Canvas != NULL)
    {
        RenderBackground(RENDER_BACKGROUND_MODE_FULL, this->_Canvas, false);
    }

    if (this->_CanvasPressed != NULL)
    {
        RenderBackground(RENDER_BACKGROUND_MODE_FULL, this->_CanvasPressed, true);
    }
}

M5EPD_Canvas *EPDGUI_Widget_Graphic_Base::Canvas()
{
    return this->_Canvas;
}

M5EPD_Canvas *EPDGUI_Widget_Graphic_Base::CanvasPressed()
{
    return this->_CanvasPressed;
}

void EPDGUI_Widget_Graphic_Base::RenderDescriptionLabel(const char *string)
{
    if (this->_Canvas != NULL)
    {
        EPDGUI_Widget_Base::RenderDescriptionLabel(this->_Canvas, string);
    }

    if (this->_CanvasPressed != NULL)
    {
        EPDGUI_Widget_Base::RenderDescriptionLabel(this->_CanvasPressed, string);
    }
}