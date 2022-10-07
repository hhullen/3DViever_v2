#ifndef VIEWSETUP_H
#define VIEWSETUP_H

#include <QColorDialog>
#include <QLabel>
#include <QStyle>
#include <QWidget>
#include "enum_parameters.h"

namespace Ui {
class ViewSetup;
}

namespace S21 {

class ViewSetup : public QWidget {
  Q_OBJECT

 public:
  explicit ViewSetup(QWidget *parent = nullptr);
  ~ViewSetup();

 signals:
    void DataUpdatedSignal();

 private slots:
    void GetProjectionStyleSlot(int index);
    void GetEdgeStyleSlot(int index);
    void GetVertexStyleSlot(int index);
    void ChooseEdgeColorSlot();
    void ChooseVertexColorSlot();
    void ChooseBackgroundColorSlot();
    void ResetSlot();

 private:
  Ui::ViewSetup *ui_;

  QColor vertex_color_;
  QColor backg_color_;
  QColor edge_color_;
  ProjectionType projection_type_;
  VertexStyle vertex_style_;
  EdgeStyle edge_style_;
//  int vertex_size_;
//  int edge_size_;

  void ShowChosenColorInfo(QPushButton *btn, QLabel *txt, QColor col);
  void ConnectSignalSlot();
};

}

#endif  // VIEWSETUP_H
