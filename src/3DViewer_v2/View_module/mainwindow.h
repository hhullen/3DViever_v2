#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QRegularExpression>
#include <QScrollArea>
#include <QSettings>

#include "ptransform.h"
#include "viewsetup.h"
#include "Controller_module/viewer_controller.h"
#include "Model_module/model_frame.h"
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
  void SteerPanelClosedSlot(bool state);
  void ManageSteerPanelSlot(bool state);
  void CloseAppSlot(bool state);
  void OpenNewFileSlot();
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void ManageTransformPanelSlot(bool state);
  void ManageViewSetupPanelSlot(bool state);
  void ManageScreenCapturePanelSlot(bool state);
  void GetScreenShot();
  void GetGif();
  void AddGifFrame();
  void UpdateTransformationSlot();
  void UpdateViewSlot();

 private:
  Ui::MainWindow *ui_;
  ViewerController *controller_;
  PTransform *transform_panel_;
  ViewSetup *view_panel_;

  QString file_path_;
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

}  // namespace S21

#endif  // MAINWINDOW_H
