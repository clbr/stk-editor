#include "toolbar.hpp"

#include "editor.hpp"
#include <iostream>

ToolBar* ToolBar::m_toolbar = 0;

// ----------------------------------------------------------------------------
void ToolBar::init()
{
    m_bar = Editor::getEditor()->getGUIEnv()->addToolBar();
    m_bar->setMinSize(dimension2du(0,50));

    buttonInit(0,  TBI_NEW,         "img/new.png",      L"New");
    buttonInit(1,  TBI_OPEN,        "img/open.png",     L"Open");
    buttonInit(2,  TBI_SAVE,        "img/save.png",     L"Save");
    buttonInit(3,  TBI_SAVE_AS,     "img/save_as.png",  L"Save as");
    buttonInit(4,  TBI_UNDO,        "img/undo.png",     L"Undo");
    buttonInit(5,  TBI_REDO,        "img/redo.png",     L"Redo");
    buttonInit(6,  TBI_SELECT,      "img/select.png",   L"Select");
    buttonInit(7,  TBI_MOVE,        "img/move.png",     L"Move");
    buttonInit(8,  TBI_ROTATE,      "img/rotate.png",   L"Rotate");
    buttonInit(9,  TBI_SCALE,       "img/scale.png",    L"Scale");
    buttonInit(10, TBI_DELETE,      "img/delete.png",   L"Delete");
    buttonInit(11, TBI_CAM,         "img/cam1.png",     L"Free Camera Mode");
    buttonInit(12, TBI_GRID_ON_OFF, "img/grid.png",     L"Grid On / Off");
    buttonInit(13, TBI_GRID_INC,    "img/gridinc.png",  L"Increase grid density");
    buttonInit(14, TBI_GRID_DEC,    "img/griddec.png",  L"Decrease grid density");
    buttonInit(15, TBI_TRY,         "img/try.png",      L"Try your track");
    buttonInit(16, TBI_SETTINGS,    "img/settings.png", L"Settings");
    buttonInit(17, TBI_EXIT,        "img/exit.png",     L"Quit");

    reallocate();

} // init

void ToolBar::buttonInit(unsigned int ix, ToolboxButtonIndex TBI, 
                    const char* file_path, const wchar_t* text)
{
    ITexture* img;
    img = Editor::loadImg(file_path);
    m_buttons[ix] = m_bar->addButton(TBI, 0, text, img, 0, false, true);
    m_buttons[ix]->setMaxSize(dimension2du(40, 40));
    m_buttons[ix]->setMinSize(dimension2du(40, 40));
} // buttonInit

// ----------------------------------------------------------------------------
ToolBar* ToolBar::getToolBar()
{
    if (m_toolbar != 0) return m_toolbar;

    m_toolbar = new ToolBar();
    m_toolbar->init();
    return m_toolbar;
} // getToolBar

// ----------------------------------------------------------------------------
int min(int x, int y)
{
    if (x < y) return x;
    else return y;
} // min

// ----------------------------------------------------------------------------
void ToolBar::reallocate()
{
    unsigned int screen_x = Editor::getEditor()->getScreenSize().Width;
    int max_dist_between_blocks = 50;

    int space_between_blocks = min((screen_x - 18 * 50) / 6, max_dist_between_blocks);

    // first 4 icon - new, open, save, save as
    int block_begin = 5;
    for (int i = 0; i < 4; i++)
        m_buttons[i]->setRelativePosition(position2di(block_begin + i * 50, 5));

    // second block: 2 icon - undo, redo
    block_begin += space_between_blocks;
    for (int i = 4; i < 6; i++)
        m_buttons[i]->setRelativePosition(position2di(block_begin + i * 50, 5));

    // fourth block: 5 icon - select, move, rotate, scale, delete
    block_begin += space_between_blocks;
    for (int i = 6; i < 11; i++)
        m_buttons[i]->setRelativePosition(position2di(block_begin + i * 50, 5));

    // fifth icon: switch camera
    block_begin += space_between_blocks;
    m_buttons[11]->setRelativePosition(position2di(block_begin + 11 * 50, 5));

    // Sixth block: 3 icon - grid, grid+, grid-
    block_begin += space_between_blocks;
    for (int i = 12; i < 15; i++)
        m_buttons[i]->setRelativePosition(position2di(block_begin + i * 50, 5));

    // test
    block_begin += space_between_blocks;
    m_buttons[15]->setRelativePosition(position2di(block_begin + 15 * 50, 5));

    // last block: 2 icon - settings, quit
    m_buttons[16]->setRelativePosition(position2di(screen_x - 100, 5));
    m_buttons[17]->setRelativePosition(position2di(screen_x - 50, 5));
} // reallocate
