#ifndef SCREENRECORDER_H
#define SCREENRECORDER_H

#include <QObject>
#include <QMainWindow>
#include <QTimer>
#include "gifimage/qgifimage.h"
#include "View_module/oglview.h"

namespace S21 {

class ScreenRecorder : public QObject
{
    Q_OBJECT
public:
    explicit ScreenRecorder(QObject *parent = nullptr);
    void Record();

    void set_file_name(QString file_name);
    void set_screen_to_record(OGLview *screen);

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
