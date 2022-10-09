#ifndef SCREENRECORDER_H
#define SCREENRECORDER_H

#include <QObject>
#include <QMainWindow>
#include <QTimer>
#include "View_module/gifimage/qgifimage.h"
#include "View_module/oglview.h"

namespace S21 {

class ScreenRecorder : public QObject
{
    Q_OBJECT
public:
    explicit ScreenRecorder(OGLview *screen, QString file_name, QObject *parent = nullptr);
    void Record();

signals:
    void FinishedSignal();

private slots:
    void AddGifFrameSlot();

private:
    OGLview *screen_;
    QString file_name_;
    QTimer *time_;
    QImage *frame_;
    QGifImage *gif_;
    unsigned int miliseconds_;
};

}

#endif // SCREENRECORDER_H
