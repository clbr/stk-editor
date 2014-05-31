#include "editor.hpp"

#include "toolbar.hpp"
#include "toolbox.hpp"
#include "track.hpp"

#include <iostream>

Editor* Editor::m_editor = 0;

// ----------------------------------------------------------------------------
bool Editor::init()
{
	m_device = createDevice(EDT_OPENGL,
            m_screen_size, 16,
		    false, false, true, this);

	if (!m_device) return false;
	m_device->setResizable(true);

	m_device->setWindowCaption(L"SuperTuxKart Track Editor");

	m_video_driver  = m_device->getVideoDriver();
	m_scene_manager = m_device->getSceneManager();
	m_gui_env       = m_device->getGUIEnvironment();

	m_scene_manager->addCameraSceneNode(0,
		vector3df(0, 0, -50),
		vector3df(0, 0, 50)
		);

    m_toolbar = ToolBar::getToolBar();
    m_toolbox = ToolBox::getToolBox();
    m_track   = Track::getTrack();

    return true;
} // init


// ----------------------------------------------------------------------------
Editor* Editor::getEditor(dimension2du screen_size)
{
	if (m_editor != 0) return m_editor;

	m_editor = new Editor();
    m_editor->m_screen_size = screen_size;
	if (!m_editor->init()) return 0;
	return m_editor;
} // getEditor

// ----------------------------------------------------------------------------
bool Editor::run()
{
	if (!m_device) return 0;

	while (m_device->run())
    {
		// drawing
		m_video_driver->beginScene(true, true, SColor(255, 80, 0, 170));

		m_scene_manager->drawAll();
		m_gui_env->drawAll();
		
		m_video_driver->endScene();

        if (m_video_driver->getScreenSize() != m_screen_size)
        {
            m_screen_size = m_video_driver->getScreenSize();
            m_toolbar->reallocate();
            m_toolbox->reallocate();
        }

    }
	return 1;
} // run

// ----------------------------------------------------------------------------
bool Editor::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
        {
            switch (id)
            {
            case ToolBar::TBI_EXIT:
                m_device->closeDevice();
                break;
            case ToolBar::TBI_SELECT:
                m_track->setState(Track::SELECT);
                break;
            case ToolBar::TBI_MOVE:
                m_track->setState(Track::SELECT);
                break;
            case ToolBar::TBI_ROTATE:
                m_track->setState(Track::ROTATE);
                break;
            case ToolBar::TBI_GRID_ON_OFF:
                m_track->setGrid(!m_track->isGridOn());
                break;
            case ToolBar::TBI_GRID_INC:
                m_track->changeGridDensity(1);
                break;
            case ToolBar::TBI_GRID_DEC:
                m_track->changeGridDensity(-1);
                break;
            default:
                std::cerr << "Button click isn't handled!" << std::endl;
            }
        } // EventType == EGET_BUTTON_CLICKED
    } // EventType == EET_GUI_EVENT


	return false;
} // OnEvent