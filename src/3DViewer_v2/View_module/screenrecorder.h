#ifndef SCREENRECORDER_H
#define SCREENRECORDER_H

#include <QObject>

class ScreenRecorder : public QObject
{
    Q_OBJECT
public:
    explicit ScreenRecorder(QObject *parent = nullptr);

signals:

};

#endif // SCREENRECORDER_H
