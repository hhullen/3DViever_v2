#ifndef VIEWSETUP_H
#define VIEWSETUP_H

#include <QColorDialog>
#include <QLabel>
#include <QStyle>
#include <QWidget>

typedef enum {
  PROJ_STYLE = 9,
  EDGE_STYLE,
  VERT_STYLE,
  EDGE_COLOR,
  VERT_COLOR,
  BACK_COLOR,
  EDGE_SIZE,
  VERT_SIZE,
  NO_VERTX = 2,
  RESET_VIEW
} mode_e;

namespace Ui {
class ViewSetup;
}

class ViewSetup : public QWidget {
  Q_OBJECT

 signals:
  void data_updated(double val, int type);

 public:
  explicit ViewSetup(QWidget *parent = nullptr);
  ~ViewSetup();
  QColor edge_color;
  QColor vertex_color;
  QColor backg_color;
  bool has_changed = false;
  int edge_size;
  int vertex_size;
  int projection_type;
  int edge_style;
  int vertex_style;
  void init_launch_setup();

 private slots:
  void projection_style_ch(int index);
  void edge_style_ch(int index);
  void vertex_style_ch(int index);
  void set_edge_color();
  void set_vertex_color();
  void set_background_color();
  void edge_size_ch(int pos);
  void vertex_size_ch(int pos);
  void reset_setup();

 private:
  Ui::ViewSetup *ui;
  void show_chosen_color_info(QPushButton *btn, QLabel *txt, QColor col);
};

#endif  // VIEWSETUP_H
