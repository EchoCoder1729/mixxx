#ifndef WAVEFORMWIDGETFACTORY_H
#define WAVEFORMWIDGETFACTORY_H

#include <singleton.h>

#include "waveform/waveformwidgettype.h"

#include <QObject>
#include <QVector>

class WWaveformViewer;
class WaveformWidgetAbstract;
class QTimer;
class QTime;

class WaveformWidgetAbstractHandle
{
public:
    WaveformWidgetType::Type getType() const { return m_type;}
    QString getDisplayName() const { return m_displayString;}
private:
    WaveformWidgetType::Type m_type;
    QString m_displayString;
    friend class WaveformWidgetFactory;
};

//########################################

class WaveformWidgetFactory : public QObject, public Singleton<WaveformWidgetFactory>
{
    Q_OBJECT

public:
    //creates the waveform widget and bind it to the viewer
    //clean-up every thing if needed
    bool setWaveformWidget( WWaveformViewer* viewer);

    void setFrameRate( int frameRate);
    int getFrameRate() const { return m_frameRate;}
    double getActualFrameRate() const { return m_actualFrameRate;}

    bool setWidgetType( int handleIndex);
    WaveformWidgetType::Type getType() const { return m_type;}
    const QVector<WaveformWidgetAbstractHandle> getAvailableTypes() const { return m_waveformWidgetHandles;}
    void destroyWidgets();

public slots:
    void start();
    void stop();

protected:
    WaveformWidgetFactory();
    virtual ~WaveformWidgetFactory();

    friend class Singleton<WaveformWidgetFactory>;

private slots:
    void refresh();

private:
    void evaluateWidgets();
    WaveformWidgetAbstract* createWaveformWidget( WaveformWidgetType::Type type, WWaveformViewer* viewer);

private:
    QVector<WaveformWidgetAbstractHandle> m_waveformWidgetHandles;
    QVector<WaveformWidgetAbstract*> m_waveformWidgets;

    WaveformWidgetType::Type m_type;

    int m_frameRate;
    QTimer* m_timer;

    //Debug
    QTime* m_time;
    int m_lastFrameTime;
    double m_actualFrameRate;
};

#endif // WAVEFORMWIDGETFACTORY_H
