#include "phi_widget_spinner.h"
#include "Free_Fonts.h"

PHI_Widget_Spinner::PHI_Widget_Spinner(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Spinner_Definition *definition) : PHI_Widget_Base(x, y, w, h)
{
    this->_definition = definition;

    this->_centralButton = new EPDGUI_Button(_x, _y, _w, (_h - BUTTON_HEIGHT));

    int16_t button_width = _w / 2;
    this->_leftButton = new EPDGUI_Button(_x, _y + _h - BUTTON_HEIGHT, button_width, BUTTON_HEIGHT);
    this->_rightButton = new EPDGUI_Button(_x + button_width - 2, _y + _h - BUTTON_HEIGHT, button_width, BUTTON_HEIGHT);
}

void PHI_Widget_Spinner::Render()
{
    RenderCenterButton(this->_centralButton->CanvasNormal(), false, this->_definition->Description, this->_definition->Value);
    RenderCenterButton(this->_centralButton->CanvasPressed(), true, this->_definition->Description, this->_definition->Value);

    RenderLeftButton(this->_leftButton->CanvasNormal(), false, this->_definition->DownIcon->Path);
    RenderLeftButton(this->_leftButton->CanvasPressed(), true, this->_definition->DownIcon->Path);

    RenderRightButton(this->_rightButton->CanvasNormal(), false, this->_definition->UpIcon->Path);
    RenderRightButton(this->_rightButton->CanvasPressed(), true, this->_definition->UpIcon->Path);
}

void PHI_Widget_Spinner::BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
}

void PHI_Widget_Spinner::UpdateTouchState(int16_t x, int16_t y)
{
    if (!_enabled || _hidden)
    {
        return;
    }

    this->_centralButton->UpdateTouchState(x, y);
    this->_leftButton->UpdateTouchState(x, y);
    this->_rightButton->UpdateTouchState(x, y);
}

void PHI_Widget_Spinner::Draw(m5epd_update_mode_t mode)
{
    if (_hidden)
    {
        return;
    }

    this->_centralButton->Draw(mode);
    this->_leftButton->Draw(mode);
    this->_rightButton->Draw(mode);
}

void PHI_Widget_Spinner::Draw(M5EPD_Canvas *canvas)
{
    if (_hidden)
    {
        return;
    }

    this->_centralButton->Draw(canvas);
    this->_leftButton->Draw(canvas);
    this->_rightButton->Draw(canvas);
}

void PHI_Widget_Spinner::RenderCenterButton(M5EPD_Canvas *canvas, bool pressed, String description, String value)
{
    PHI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_FULL_WITHOUT_BOTTOM, canvas, pressed);

    canvas->setTextSize(TEXT_SIZE);
    canvas->setTextColor(FONT_COLOR);
    canvas->setTextDatum(MC_DATUM);
    canvas->drawString(description, canvas->width() / 2, 35);

    canvas->setFreeFont(FF24);
    canvas->setTextColor(FONT_COLOR);
    canvas->setTextDatum(MC_DATUM);
    canvas->drawString(value, canvas->width() / 2, canvas->height() / 2 + 20);
    canvas->setFreeFont(NULL);

    if (pressed)
    {
        canvas->ReverseColor();
    }
}

void PHI_Widget_Spinner::RenderLeftButton(M5EPD_Canvas *canvas, bool pressed, String icon)
{
    PHI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_BOTTOM_LEFT, canvas, pressed);

    int16_t halfBoarderWith = BORDER_WIDTH % 2 == 0 ? BORDER_WIDTH / 2 : (BORDER_WIDTH / 2 - 1);

    if (!pressed)
    {
        for (int i = 0; i < BORDER_WIDTH; i++)
        {
            canvas->drawFastHLine(BORDER_WIDTH, i, canvas->width() - BORDER_WIDTH, BORDER_COLOR);
        }
        for (int i = 0; i < halfBoarderWith; i++)
        {
            canvas->drawFastVLine(canvas->width() - i - 1, BORDER_WIDTH, canvas->height() - BORDER_WIDTH, BORDER_COLOR);
        }
    }

    canvas->drawJpgFile(SD, icon.c_str(), canvas->width() / 2 - 30, canvas->height() / 2 - 30, 60, 60);

    if (pressed)
    {
        canvas->ReverseColor();
    }
}

void PHI_Widget_Spinner::RenderRightButton(M5EPD_Canvas *canvas, bool pressed, String icon)
{
    PHI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_BOTTOM_RIGHT, canvas, pressed);

    int16_t halfBoarderWith = BORDER_WIDTH % 2 == 0 ? BORDER_WIDTH / 2 : (BORDER_WIDTH / 2 + 1);

    if (!pressed)
    {
        for (int i = 0; i < BORDER_WIDTH; i++)
        {
            canvas->drawFastHLine(0, i, canvas->width() - BORDER_WIDTH, BORDER_COLOR);
        }
        for (int i = 0; i < halfBoarderWith; i++)
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