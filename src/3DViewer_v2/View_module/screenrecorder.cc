#include "screenrecorder.h"

namespace S21 {

ScreenRecorder::ScreenRecorder(QObject *parent)
    : QObject{parent} {
}

void ScreenRecorder::Record() {
    if (screen_) {
        miliseconds_ = 0;
        gif_ = new QGifImage();
        frame_ = new QImage();
        time_ = new QTimer();
        connect(time_, &QTimer::timeout, this, &ScreenRecorder::AddGifFrameSlot);
        time_->start(100);
        screen_->ShowEventMessage("Recording in progress...", 1500);
    }
}

void ScreenRecorder::set_file_name(QString file_name) {
    if (!file_name.isEmpty()) {
        file_name_ = file_name;
    } else {
        file_name_ = "/gif.gif";
    }
}

void ScreenRecorder::set_screen_to_record(OGLview *screen) {
    if (screen) {
        screen_ = screen;
    }
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
        delete gif_;
        delete frame_;
        delete time_;
        emit FinishedSignal();
    }
}

}
