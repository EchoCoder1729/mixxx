#include "waveformwidgetabstract.h"
#include "waveformwidgetrenderer.h"

#include <QWidget>

#include <QDebug>

const QString WaveformWidgetAbstract::s_openGlFlag = "(OpenGl)";

//Default constructor is only use by the factory to evaluate dynamically WaveformWidget
WaveformWidgetAbstract::WaveformWidgetAbstract()
{
    m_widget = 0;
    m_waveformWidgetRenderer = 0;
}

WaveformWidgetAbstract::WaveformWidgetAbstract( const char* group)
{
    m_widget = 0;
    m_waveformWidgetRenderer =  new WaveformWidgetRenderer(group);
}

WaveformWidgetAbstract::~WaveformWidgetAbstract()
{
    delete m_waveformWidgetRenderer;
}

void WaveformWidgetAbstract::hold()
{
    if( m_widget)
        m_widget->hide();
}

void WaveformWidgetAbstract::release()
{
    if( m_widget)
        m_widget->show();
}

void WaveformWidgetAbstract::refresh()
{
    if( m_widget)
        m_widget->update();
}

void WaveformWidgetAbstract::resize( int width, int height)
{
    if( m_widget)
    {
        m_widget->resize( width, height);
        m_waveformWidgetRenderer->resize( width, height);
    }
}

void WaveformWidgetAbstract::setup( const QDomNode& node)
{
    m_waveformWidgetRenderer->setup(node);
}
