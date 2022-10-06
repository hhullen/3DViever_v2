#include "screencap.h"

#include "ui_screencap.h"

ScreenCap::ScreenCap(QWidget *parent) : QWidget(parent), ui(new Ui::ScreenCap) {
  ui->setupUi(this);

  name_pattern.setPattern("[^\\/]*$");
  ui->BtnFolderPath->setText(files_path);

  connect(ui->BtnFolderPath, SIGNAL(clicked()), this, SLOT(choose_dir()));
  connect(ui->BtnOpenFolder, SIGNAL(clicked()), this, SLOT(open_folder()));
  connect(ui->CBFileType, SIGNAL(currentIndexChanged(int)), this,
          SLOT(change_screen_type(int)));
  connect(ui->BtnScreenShot, SIGNAL(clicked()), this, SLOT(screenshot()));
  connect(ui->BtnREC, SIGNAL(clicked()), this, SLOT(gif()));
}

ScreenCap::~ScreenCap() { delete ui; }

void ScreenCap::set_path_button() {
  match = name_pattern.match(files_path);
  ui->BtnFolderPath->setText(match.captured());
}

void ScreenCap::choose_dir() {
  files_path = QFileDialog::getExistingDirectory(
      this, "Choose folder to save screen", "/Users",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  set_path_button();
}

void ScreenCap::open_folder() {
  if (!files_path.isEmpty()) {
    QDesktopServices::openUrl(QUrl::fromLocalFile(files_path));
  }
}

void ScreenCap::change_screen_type(int index) { file_type = index; }

void ScreenCap::screenshot() { emit take_screenshot(); }

void ScreenCap::gif() { emit record_gif(); }
