#include "epdgui_widget_spinner.h"

EPDGUI_Widget_Spinner::EPDGUI_Widget_Spinner(int16_t x, int16_t y, int16_t w, int16_t h) : EPDGUI_Widget_Base(x, y, w, h)
{
    this->_centralButton = new EPDGUI_Button(_x, _y, _w, (_h - BUTTON_HEIGHT));
    this->_leftButton = new EPDGUI_Button(_x, _y + _h - BUTTON_HEIGHT, _w / 2 - BORDER_WIDTH / 2, BUTTON_HEIGHT);
    this->_rightButton = new EPDGUI_Button(_x + _w / 2 - BORDER_WIDTH / 2, _y + _h - BUTTON_HEIGHT, _w / 2 - BORDER_WIDTH / 2, BUTTON_HEIGHT);
}

void EPDGUI_Widget_Spinner::Render(JsonVariant data)
{
    String upIcon = data["upicon"];
    String downIcon = data["downicon"];
    String description = data["description"];
    String value = data["value"];

    RenderCenterButton(this->_centralButton->CanvasNormal(), false, description, value);
    RenderCenterButton(this->_centralButton->CanvasPressed(), true, description, value);

    RenderLeftButton(this->_leftButton->CanvasNormal(), false, downIcon);
    RenderLeftButton(this->_leftButton->CanvasPressed(), true, downIcon);

    RenderRightButton(this->_rightButton->CanvasNormal(), false, upIcon);
    RenderRightButton(this->_rightButton->CanvasPressed(), true, upIcon);
}

void EPDGUI_Widget_Spinner::Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
}

void EPDGUI_Widget_Spinner::UpdateState(int16_t x, int16_t y)
{
    if (!_isenable || _ishide)
    {
        return;
    }

    this->_centralButton->UpdateState(x, y);
    this->_leftButton->UpdateState(x, y);
    this->_rightButton->UpdateState(x, y);
}

void EPDGUI_Widget_Spinner::Draw(m5epd_update_mode_t mode)
{
    if (_ishide)
    {
        return;
    }

    this->_centralButton->Draw(mode);
    this->_leftButton->Draw(mode);
    this->_rightButton->Draw(mode);
}

void EPDGUI_Widget_Spinner::Draw(M5EPD_Canvas *canvas)
{
    if (_ishide)
    {
        return;
    }

    this->_centralButton->Draw(canvas);
    this->_leftButton->Draw(canvas);
    this->_rightButton->Draw(canvas);
}

void EPDGUI_Widget_Spinner::RenderCenterButton(M5EPD_Canvas *canvas, bool pressed, String description, String value)
{
    EPDGUI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_FULL_WITHOUT_BOTTOM, canvas, pressed);

    canvas->setTextSize(TEXT_SIZE);
    canvas->setTextColor(FONT_COLOR);
    canvas->setTextDatum(MC_DATUM);
    canvas->drawString(description, canvas->width() / 2, 35);

    canvas->setTextSize(TEXT_SIZE);
    canvas->setTextColor(FONT_COLOR);
    canvas->setTextDatum(MC_DATUM);
    canvas->drawString(value, canvas->width() / 2, canvas->height() / 2);

    if (pressed)
    {
        canvas->ReverseColor();
    }
}

void EPDGUI_Widget_Spinner::RenderLeftButton(M5EPD_Canvas *canvas, bool pressed, String icon)
{
    EPDGUI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_BOTTOM_LEFT, canvas, pressed);

    if (!pressed)
    {
        for (int i = 0; i < BORDER_WIDTH; i++)
        {
            canvas->drawFastHLine(BORDER_WIDTH, i, canvas->width() - BORDER_WIDTH, BORDER_COLOR);
        }
        for (int i = 0; i < BORDER_WIDTH / 2; i++)
        {
            canvas->drawFastVLine(canvas->width() - 1 - i, BORDER_WIDTH, canvas->height() - BORDER_WIDTH, BORDER_COLOR);
        }
    }

    canvas->drawJpgFile(SD, icon.c_str(), canvas->width() / 2 - 30, canvas->height() / 2 - 30, 60, 60);

    if (pressed)
    {
        canvas->ReverseColor();
    }
}

void EPDGUI_Widget_Spinner::RenderRightButton(M5EPD_Canvas *canvas, bool pressed, String icon)
{
    EPDGUI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_BOTTOM_RIGHT, canvas, pressed);

    if (!pressed)
    {
        for (int i = 0; i < BORDER_WIDTH; i++)
        {
            canvas->drawFastHLine(0, i, canvas->width() - BORDER_WIDTH, BORDER_COLOR);
        }
        for (int i = 0; i < BORDER_WIDTH / 2; i++)
        {
            canvas->drawFastVLine(i, BORDER_WIDTH, canvas->height() - BORDER_WIDTH, BORDER_COLOR);
        }
    }

    canvas->drawJpgFile(SD, icon.c_str(), canvas->width() / 2 - 30, canvas->height() / 2 - 30, 60, 60);

    if (pressed)
    {
        canvas->ReverseColor();
    }
}