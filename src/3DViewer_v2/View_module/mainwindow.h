#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QRegularExpression>
#include <QScrollArea>
#include <QSettings>
#include "Model_module/model_frame.h"
#include "Controller_module/viewer_controller.h"
using S21::ModelFrame;
using S21::ViewerController;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace S21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(ViewerController *controller, QWidget *parent = nullptr);
  ~MainWindow();
  void SaveSettings();
  void UploadSettings();

 signals:

 private slots:
  void SteerPanelClosed(bool state);
  void ManageSteerPanel(bool state);
  void CloseApp(bool state);
  void OpenNewFile();
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void ManageTransformPanel(bool state);
  void ManageViewSetupPanel(bool state);
  void ManageScreenCapturePanel(bool state);
  void GetScreenShot();
  void GetGif();
  void AddGifFrame();

 private:
  Ui::MainWindow *ui_;
  ViewerController *controller_;
  QString file_path_;
//  QString status_bar_info_;
  QRegularExpression name_pattern_;
//  QSettings *settings_ ;
//  QString folder_path_;
//  QString file_name_;
//  QDateTime *date_time_;
//  QImage *frame_;
//  QTimer *time_;
//  bool recording_ = false;
//  int miliseconds_;

  void SetSteerPanelComponentsAvailability(bool state);
  void SetModelInfo();
//  void ResetViewSetup();


  void AddSteeringWidgetsToDockPanel();
  void ConnectSignalSlot();
  void GetMediaName(QString *name);
};

}

#endif  // MAINWINDOW_H
