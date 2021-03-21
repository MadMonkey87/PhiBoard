#include "epdgui_widget_multi_button.h"

EPDGUI_Widget_Multi_Button::EPDGUI_Widget_Multi_Button(int16_t x, int16_t y, int16_t w, int16_t h, int16_t items) : EPDGUI_Widget_Base(x, y, w, h)
{
    int16_t element_height = h / items;

    for (int i = 0; i < items; i++)
    {
        EPDGUI_Button *button = new EPDGUI_Button(_x, _y + element_height * i, _w, element_height);
        _buttons.push_back(button);
    }
}

EPDGUI_Widget_Multi_Button::~EPDGUI_Widget_Multi_Button()
{
    for (std::list<EPDGUI_Button *>::iterator p = _buttons.begin(); p != _buttons.end(); p++)
    {
        delete (*p);
    }
}

void EPDGUI_Widget_Multi_Button::Render(JsonVariant data)
{
    //EPDGUI_Widget_Graphic_Base::Render(data);

    int index = 0;
    int last = _buttons.size() - 1;
    for (std::list<EPDGUI_Button *>::iterator p = _buttons.begin(); p != _buttons.end(); p++)
    {
        RenderButtonContent((*p)->_CanvasNormal, false, "Test", "/Icons/play-2-small.jpg", index == 0, index == last);
        RenderButtonContent((*p)->_CanvasPressed, true, "Test", "/Icons/play-2-small.jpg", index == 0, index == last);
        index++;
    }
}

void EPDGUI_Widget_Multi_Button::Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
}

void EPDGUI_Widget_Multi_Button::UpdateState(int16_t x, int16_t y)
{
    if (!_isenable || _ishide)
    {
        return;
    }

    for (std::list<EPDGUI_Button *>::iterator p = _buttons.begin(); p != _buttons.end(); p++)
    {
        (*p)->UpdateState(x, y);
    }
}

void EPDGUI_Widget_Multi_Button::Draw(m5epd_update_mode_t mode)
{
    if (_ishide)
    {
        return;
    }

    for (std::list<EPDGUI_Button *>::iterator p = _buttons.begin(); p != _buttons.end(); p++)
    {
        (*p)->Draw(mode);
    }
}

void EPDGUI_Widget_Multi_Button::Draw(M5EPD_Canvas *canvas)
{
    if (_ishide)
    {
        return;
    }

    for (std::list<EPDGUI_Button *>::iterator p = _buttons.begin(); p != _buttons.end(); p++)
    {
        (*p)->Draw(canvas);
    }
}

void EPDGUI_Widget_Multi_Button::RenderButtonContent(M5EPD_Canvas *canvas, bool pressed, String description, String icon, bool first, bool last)
{
    if (first)
    {
        EPDGUI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_FULL_WITHOUT_BOTTOM, canvas, pressed);
    }
    else if (last)
    {
        EPDGUI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_FULL_WITHOUT_TOP, canvas, pressed);
    }
    else
    {
        EPDGUI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_MIDDLE_HORIZONTAL, canvas, pressed);
    }

    if (!first)
    {
        canvas->fillRect(SEPARATOR_HORIZONTAL_MARGIN, 0, canvas->width() - (SEPARATOR_HORIZONTAL_MARGIN * 2), SEPARATOR_HEIGHT / 2, SEPARATOR_COLOR);
    }
    if (!last)
    {
        canvas->fillRect(SEPARATOR_HORIZONTAL_MARGIN, canvas->height() - SEPARATOR_HEIGHT / 2, canvas->width() - (SEPARATOR_HORIZONTAL_MARGIN * 2), SEPARATOR_HEIGHT / 2, SEPARATOR_COLOR);
    }

    canvas->drawJpgFile(SD, icon.c_str(), canvas->width() - 60 - 10, 10, 60, 60);

    canvas->setTextSize(TEXT_SIZE);
    canvas->setTextColor(FONT_COLOR);
    canvas->setTextDatum(MC_DATUM);
    canvas->drawString(description.c_str(), _x + 30, canvas->height() / 2);

    if (pressed)
    {
        canvas->ReverseColor();
    }
}