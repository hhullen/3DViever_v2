#ifndef SCREENCAP_H
#define SCREENCAP_H

#include <QDesktopServices>
#include <QFileDialog>
#include <QRegularExpression>
#include <QWidget>

#define JPEG 0
#define BMP 1

namespace Ui {
class ScreenCap;
}

class ScreenCap : public QWidget {
  Q_OBJECT

 public:
  explicit ScreenCap(QWidget *parent = nullptr);
  ~ScreenCap();
  QString files_path;
  int file_type = JPEG;
  QPixmap *screen;
  QPushButton *path_btn;
  void set_path_button();

 signals:
  void take_screenshot();
  void record_gif();

 private slots:
  void choose_dir();
  void open_folder();
  void change_screen_type(int index);
  void screenshot();
  void gif();

 private:
  Ui::ScreenCap *ui;
  QRegularExpression name_pattern;
  QRegularExpressionMatch match;
};

#endif  // SCREENCAP_H
