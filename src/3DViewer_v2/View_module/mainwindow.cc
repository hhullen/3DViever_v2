#include "mainwindow.h"

#include "./ui_mainwindow.h"

namespace S21 {

MainWindow::MainWindow(ViewerController *controller, QWidget *parent)
    : controller_(controller), QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  transform_panel_ = new PTransform();
  view_panel_ = new ViewSetup();
  screen_cap_ = new ScreenCap();

  view_panel_->setVisible(false);
  screen_cap_->setVisible(false);

  name_pattern_.setPattern("[^\\/]*$");

  ui_->dock_widget->hide();
  ui_->statusbar->setToolTip("HELLO MF!");

  SetSteerPanelComponentsAvailability(false);

  AddSteeringWidgetsToDockPanel();
  ConnectSignalSlot();
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::GetScreenShotSlot() {
    qDebug() << screen_cap_->get_screenshot_type();
    qDebug() << "SCREEN" << screen_cap_->get_media_path();
  //  if (!screenCap->files_path.isEmpty()) {
  //    QImage img = glview->grabFramebuffer();
  //    get_media_name(&file_name);
  //    if (screenCap->file_type == JPEG) {
  //      file_name.append(".jpeg");
  //      img.save(file_name, "JPEG");
  //    } else if (screenCap->file_type == BMP) {
  //      file_name.append(".bmp");
  //      img.save(file_name, "BMP");
  //    }
  //    glview->show_message("Screenshot sved to: " + screenCap->files_path,
  //    3000);
  //  }
}

void MainWindow::GetGifSlot() {
    qDebug() << "GIF" << screen_cap_->get_media_path();
  //  if (!screenCap->files_path.isEmpty() && !recording) {
  //    recording = true;
  //    miliseconds = 0;
  //    gif = new QGifImage;
  //    frame = new QImage();
  //    time = new QTimer();
  //    get_media_name(&file_name);
  //    file_name.append(".gif");
  //    connect(time, SIGNAL(timeout()), this, SLOT(add_gif_frame()));
  //    time->start(100);
  //    glview->show_message("Recording in progress...", 1000);
  //  }
}

void MainWindow::AddGifFrame() {
  //  *frame = glview->grabFramebuffer();
  //  *frame = frame->scaled(640, 480);
  //  gif->addFrame(*frame, 100);
  //  miliseconds += 100;
  //  if (miliseconds >= 5000) {
  //    time->stop();
  //    gif->save(file_name);
  //    glview->show_message("Gif file saved to: " + screenCap->files_path,
  //    3000); recording = false;
    //  }
}

void MainWindow::UpdateViewSlot() {
    qDebug() << "bgc" << view_panel_->get_background_color();
    qDebug() << "eco" << view_panel_->get_edges_color();
    qDebug() << "esi" << view_panel_->get_edges_size();
    qDebug() << "est" << view_panel_->get_edges_style();
    qDebug() << "vco" << view_panel_->get_vertex_color();
    qDebug() << "vsi" << view_panel_->get_vertex_size();
    qDebug() << "vst" << view_panel_->get_vertex_style();
    qDebug() << "prj" << view_panel_->get_projection_type();
}

void MainWindow::UpdateTransformationSlot() {
    double x, y, z;
    transform_panel_->get_position(&x, &y, &z);
    qDebug() << "pos" << x << " " << y << " " << z;
    transform_panel_->get_angle(&x, &y, &z);
    qDebug() << "ang" << x << " " << y << " " << z;
    qDebug() << "scl" << transform_panel_->get_scale();
}

void MainWindow::GetMediaName(QString *name) {
  //  name->clear();
  //  name->append(screenCap->files_path);
  //  name->append("/screen" +
  //               date_time->currentDateTime().toString("yyyy_MM_dd_hh_mm_ss"));
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  //  if (event->key() == Qt::Key_Space) {
  //    glview->key_space = true;
  //  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  //  if (event->key() == Qt::Key_Space) glview->key_space = false;
}

void MainWindow::ManageTransformPanelSlot(bool state) {
    transform_panel_->setVisible(state);
}

void MainWindow::ManageViewSetupPanelSlot(bool state) {
    view_panel_->setVisible(state);
}

void MainWindow::ManageScreenCapturePanelSlot(bool state) {
    screen_cap_->setVisible(state);
}

void MainWindow::SteerPanelClosedSlot(bool state) {
  ui_->actionSteer_panel->setChecked(state);
}

void MainWindow::ManageSteerPanelSlot(bool state) {
  ui_->dock_widget->setVisible(state);
  ui_->dock_widget->setFloating(false);
}

void MainWindow::CloseAppSlot(bool state) { QApplication::quit(); }

void MainWindow::OpenNewFileSlot() {
  file_path_ = QFileDialog::getOpenFileName(this, "Open .obj file", "/Users",
                                            "obj (*.obj);;");
  qDebug() << file_path_;
  if (!file_path_.isEmpty()) {
    bool is_loaded = controller_->UploadNewModel(file_path_.toStdString());
    if (is_loaded) {
      SetModelInfo();
      SetSteerPanelComponentsAvailability(true);
      //      emit model_uploaded(model);
    } else {
      //      glview->show_message("Can not upload file", 3000);
      SetSteerPanelComponentsAvailability(false);
    }
  }
}

void MainWindow::SetSteerPanelComponentsAvailability(bool state) {
    transform_panel_->setDisabled(!state);
    view_panel_->setDisabled(!state);
    screen_cap_->setDisabled(!state);
}

void MainWindow::SetModelInfo() {
  QString status_bar_info;
  QRegularExpressionMatch match_ = name_pattern_.match(file_path_);

  status_bar_info.append("  File name: ");
  status_bar_info.append(match_.captured());
  status_bar_info.append("  Vertexes: ");
  status_bar_info.append(QString::number(controller_->get_vertexes_amount()));
  status_bar_info.append("  Edges: ");
  status_bar_info.append(QString::number(controller_->get_facets_amount()));
  ui_->statusbar->showMessage(status_bar_info);
}

void MainWindow::AddSteeringWidgetsToDockPanel() {
  ui_->scroll_area_contents->layout()->setAlignment(Qt::AlignTop |
                                                    Qt::AlignLeft);
  ui_->scroll_area_contents->layout()->setSpacing(0);
    ui_->scroll_area_contents->layout()->addWidget(transform_panel_);
    ui_->scroll_area_contents->layout()->addWidget(view_panel_);
    ui_->scroll_area_contents->layout()->addWidget(screen_cap_);
}

void MainWindow::ConnectSignalSlot() {
  connect(ui_->dock_widget, &QDockWidget::visibilityChanged, this,
          &MainWindow::SteerPanelClosedSlot);
  connect(ui_->actionSteer_panel, &QAction::triggered, this,
          &MainWindow::ManageSteerPanelSlot);
  connect(ui_->action_close, &QAction::triggered, this,
          &MainWindow::CloseAppSlot);
  connect(ui_->action_transform, &QAction::triggered, this,
          &MainWindow::ManageTransformPanelSlot);
  connect(ui_->action_setup_view, &QAction::triggered, this,
          &MainWindow::ManageViewSetupPanelSlot);
  connect(ui_->action_screen_capture, &QAction::triggered, this,
          &MainWindow::ManageScreenCapturePanelSlot);
  connect(ui_->action_open_new, &QAction::triggered, this,
          &MainWindow::OpenNewFileSlot);
  //  connect(this, SIGNAL(model_uploaded(model_t *)), glview,
  //          SLOT(draw_model(model_t *)));
    connect(transform_panel_, &PTransform::DataUpdatedSignal, this,
          &MainWindow::UpdateTransformationSlot);
    connect(view_panel_, &ViewSetup::DataUpdatedSignal, this,
            &MainWindow::UpdateViewSlot);
  //  connect(this, SIGNAL(redraw()), glview, SLOT(update_frame()));
    connect(screen_cap_, &ScreenCap::TakeScreenshotSignal, this,
    &MainWindow::GetScreenShotSlot);
    connect(screen_cap_, &ScreenCap::RecordGifSignal, this, &MainWindow::GetGifSlot);
}

}  // namespace S21
