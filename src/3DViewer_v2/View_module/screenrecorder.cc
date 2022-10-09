#include "screenrecorder.h"

namespace S21 {

ScreenRecorder::ScreenRecorder(OGLview *screen, QString file_name, QObject *parent)
    : screen_(screen), file_name_(file_name), QObject(parent) {

    connect(time_, &QTimer::timeout, this, &ScreenRecorder::AddGifFrameSlot);
}

void ScreenRecorder::Record() {
        miliseconds_ = 0;
        gif_ = new QGifImage;
        frame_ = new QImage();
        time_ = new QTimer();
        time_->start(100);
        screen_->ShowEventMessage("Recording in progress...", 1500);
}

void ScreenRecorder::AddGifFrameSlot() {
      *frame_ = screen_->grabFramebuffer();
      *frame_ = frame_->scaled(640, 480);
      gif_->addFrame(*frame_, 100);
      miliseconds_ += 100;
      if (miliseconds_ >= 5000) {
        time_->stop();
        gif_->save(file_name_);
        screen_->ShowEventMessage("Gif file saved", 2000);
        emit FinishedSignal();
    }
}

}
