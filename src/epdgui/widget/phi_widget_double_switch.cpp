#include "phi_widget_double_switch.h"

PHI_Widget_Double_Switch::PHI_Widget_Double_Switch(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Double_Switch_Definition *definition) : PHI_Widget_Graphic_Base(x, y, w, h, false, false)
{
    this->_definition = definition;

    this->_Canvas = new M5EPD_Canvas(&M5.EPD);
    this->_Canvas->createCanvas(_w, MIDDLE_HEIGHT);

    int16_t buttonHeight = (_h - MIDDLE_HEIGHT) / 2;
    this->_upperButton = new EPDGUI_Button(_x, _y, _w, buttonHeight);
    this->_lowerButton = new EPDGUI_Button(_x, _y + buttonHeight + MIDDLE_HEIGHT, _w, buttonHeight);
}

PHI_Widget_Double_Switch::~PHI_Widget_Double_Switch()
{
    delete this->_upperButton;
    delete this->_lowerButton;
}

void PHI_Widget_Double_Switch::Render()
{
    this->_Canvas->fillCanvas(BORDER_COLOR);
    this->_Canvas->fillRect(BORDER_WIDTH, 0, _w - BORDER_WIDTH * 2, MIDDLE_HEIGHT, BACKGROUND_COLOR);
    this->_Canvas->fillRect(BAR_HORIZONTAL_MARGIN, MIDDLE_HEIGHT / 2 - BAR_HEIGHT / 2, _w - (BAR_HORIZONTAL_MARGIN * 2), BAR_HEIGHT, BAR_COLOR);

    RenderUpperButton(this->_upperButton->CanvasNormal(), false, this->_definition->UpIcon->Path);
    RenderUpperButton(this->_upperButton->CanvasPressed(), true, this->_definition->UpIcon->Path);

    RenderLowerButton(this->_lowerButton->CanvasNormal(), false, this->_definition->DownIcon->Path);
    RenderLowerButton(this->_lowerButton->CanvasPressed(), true, this->_definition->DownIcon->Path);
}

void PHI_Widget_Double_Switch::RenderUpperButton(M5EPD_Canvas *canvas, bool pressed, String icon)
{
    int16_t height = _upperButton->getH();
    int16_t width = _upperButton->getW();

    PHI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_FULL_WITHOUT_BOTTOM, canvas, pressed);

    canvas->drawJpgFile(SD, icon.c_str(), width / 2 - 40, height / 2 - 40, 80, 80);

    if (pressed)
    {
        canvas->ReverseColor();
    }
}

void PHI_Widget_Double_Switch::RenderLowerButton(M5EPD_Canvas *canvas, bool pressed, String icon)
{
    int16_t height = _lowerButton->getH();
    int16_t width = _lowerButton->getW();

    PHI_Widget_Base::RenderBackground(RENDER_BACKGROUND_MODE_FULL_WITHOUT_TOP, canvas, pressed);

    canvas->drawJpgFile(SD, icon.c_str(), width / 2 - 40, height / 2 - 40, 80, 80);

    if (pressed)
    {
        canvas->ReverseColor();
    }
}

void PHI_Widget_Double_Switch::BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &))
{
}

void PHI_Widget_Double_Switch::UpdateTouchState(int16_t x, int16_t y)
{
    if (!_enabled || _hidden)
    {
        return;
    }

    this->_upperButton->UpdateTouchState(x, y);
    this->_lowerButton->UpdateTouchState(x, y);
}

void PHI_Widget_Double_Switch::Draw(m5epd_update_mode_t mode)
{
    if (_hidden)
    {
        return;
    }

    this->_Canvas->pushCanvas(_x, _y + this->_upperButton->getH(), mode);

    this->_upperButton->Draw(mode);
    this->_lowerButton->Draw(mode);
}

void PHI_Widget_Double_Switch::Draw(M5EPD_Canvas *canvas)
{
    if (_hidden)
    {
        return;
    }

    _Canvas->pushToCanvas(_x, _y + this->_upperButton->getH(), canvas);

    this->_upperButton->Draw(canvas);
    this->_lowerButton->Draw(canvas);
}

PhiAction_Definition *PHI_Widget_Double_Switch::GetPhiAction()
{
    return NULL;
}