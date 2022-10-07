#include "viewsetup.h"

#include "ui_viewsetup.h"

namespace S21 {

ViewSetup::ViewSetup(QWidget *parent) : QWidget(parent), ui_(new Ui::ViewSetup) {
  ui_->setupUi(this);
  ConnectSignalSlot();
}

ViewSetup::~ViewSetup() { delete ui_; }

void ViewSetup::GetProjectionStyleSlot(int index) {
    if (index == 0) {
        projection_type_ = ProjectionType::ORTHOGONAL;
    } else if (index == 1) {
        projection_type_ = ProjectionType::PERSPECTIVE;
    }
    emit DataUpdatedSignal();
}

void ViewSetup::GetEdgeStyleSlot(int index) {
    if (index == 0) {
        edge_style_ = EdgeStyle::SOLID;
    } else if (index == 1) {
        edge_style_ = EdgeStyle::STIPPLE;
    }
    emit DataUpdatedSignal();
}

void ViewSetup::GetVertexStyleSlot(int index) {
    if (index == 0) {
        vertex_style_ = VertexStyle::ROUND;
    } else if (index == 1) {
        vertex_style_ = VertexStyle::SQUARE;
    } else if (index == 2) {
        vertex_style_ = VertexStyle::NONE;
    }
    emit DataUpdatedSignal();
}

void ViewSetup::ChooseEdgeColorSlot() {
    edge_color_ = GetNewColor();
    QColor temp = QColorDialog::getColor(edge_color_, this, "Select edges color", QColorDialog::ColorDialogOption::ShowAlphaChannel);
    if (temp.isValid()) {
        edge_color_ = temp;
        ui_->palette_edge->setStyleSheet(
                    "QPushButton {"
                        "border: 2px solid rgba(90, 90, 90, 0.6);"
                        "border-radius: 10px;"
                        "background-color:" + edge_color_.name(QColor::NameFormat::HexArgb) + ";"
                        "color: rgba(0, 0, 0, 0);"
                    "}");
    }
}

void ViewSetup::ChooseVertexColorSlot() {

}

void ViewSetup::ChooseBackgroundColorSlot() {

}

void ViewSetup::ResetSlot() {

}

void ViewSetup::ShowChosenColorInfo(QPushButton *btn, QLabel *txt,
                                       QColor col) {
  btn->setStyleSheet(
      "border: 2px solid grey;"
      "color: " +
      col.name());
  txt->setText("R: " + QString::number(col.red()) +
               " G: " + QString::number(col.green()) +
               " B: " + QString::number(col.blue()));
}

void ViewSetup::ConnectSignalSlot() {
      connect(ui_->cb_projection_style, &QComboBox::activated, this,
              &ViewSetup::GetProjectionStyleSlot);
      connect(ui_->cb_edge_style, &QComboBox::activated, this,
              &ViewSetup::GetEdgeStyleSlot);
      connect(ui_->cb_vertex_style, &QComboBox::activated, this,
              &ViewSetup::GetVertexStyleSlot);
      connect(ui_->palette_edge, &QPushButton::clicked, this, &ViewSetup::ChooseEdgeColorSlot);
      connect(ui_->palette_vertex, &QPushButton::clicked, this, &ViewSetup::ChooseVertexColorSlot);
      connect(ui_->palette_background, &QPushButton::clicked, this,
              &ViewSetup::ChooseBackgroundColorSlot);
      connect(ui_->hs_edge_size, &QSlider::sliderMoved, this,
              &ViewSetup::DataUpdatedSignal);
      connect(ui_->hs_vertex_size, &QSlider::sliderMoved, this,
              &ViewSetup::DataUpdatedSignal);
      connect(ui_->btn_reset, &QPushButton::clicked, this, &ViewSetup::ResetSlot);
}

}
