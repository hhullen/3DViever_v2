#include "viewsetup.h"

#include "ui_viewsetup.h"

ViewSetup::ViewSetup(QWidget *parent) : QWidget(parent), ui(new Ui::ViewSetup) {
  ui->setupUi(this);

  connect(ui->CBProjStyle, SIGNAL(currentIndexChanged(int)), this,
          SLOT(projection_style_ch(int)));
  connect(ui->CBEdgeStyle, SIGNAL(currentIndexChanged(int)), this,
          SLOT(edge_style_ch(int)));
  connect(ui->CBVertexStyle, SIGNAL(currentIndexChanged(int)), this,
          SLOT(vertex_style_ch(int)));
  connect(ui->PaletteEdge, SIGNAL(clicked()), this, SLOT(set_edge_color()));
  connect(ui->PaletteVertex, SIGNAL(clicked()), this, SLOT(set_vertex_color()));
  connect(ui->PaletteBackground, SIGNAL(clicked()), this,
          SLOT(set_background_color()));
  connect(ui->HSEdgeSize, SIGNAL(sliderMoved(int)), this,
          SLOT(edge_size_ch(int)));
  connect(ui->HSVertexSize, SIGNAL(sliderMoved(int)), this,
          SLOT(vertex_size_ch(int)));
  connect(ui->BtnResetView, SIGNAL(clicked()), this, SLOT(reset_setup()));
}

ViewSetup::~ViewSetup() { delete ui; }

void ViewSetup::init_launch_setup() {
  show_chosen_color_info(ui->PaletteEdge, ui->labelEdgeRGB, edge_color);
  show_chosen_color_info(ui->PaletteVertex, ui->labelVertexRGB, vertex_color);
  show_chosen_color_info(ui->PaletteBackground, ui->labelBackgroundRGB,
                         backg_color);
  ui->HSVertexSize->setValue(vertex_size);
  ui->HSEdgeSize->setValue(edge_size);
  ui->CBProjStyle->setCurrentIndex(projection_type);
  ui->CBVertexStyle->setCurrentIndex(vertex_style);
  ui->CBEdgeStyle->setCurrentIndex(edge_style);
}

void ViewSetup::projection_style_ch(int index) {
  has_changed = true;
  emit data_updated(index, PROJ_STYLE);
}

void ViewSetup::edge_style_ch(int index) {
  has_changed = true;
  emit data_updated(index, EDGE_STYLE);
}

void ViewSetup::vertex_style_ch(int index) {
  has_changed = true;
  if (index == NO_VERTX) {
    ui->HSVertexSize->setDisabled(true);
  } else {
    ui->HSVertexSize->setDisabled(false);
  }
  emit data_updated(index, VERT_STYLE);
}

void ViewSetup::set_edge_color() {
  has_changed = true;
  edge_color = QColorDialog::getColor(edge_color, this, "Select edges color");
  show_chosen_color_info(ui->PaletteEdge, ui->labelEdgeRGB, edge_color);
  emit data_updated(0, EDGE_COLOR);
}

void ViewSetup::set_vertex_color() {
  has_changed = true;
  vertex_color =
      QColorDialog::getColor(vertex_color, this, "Select vertexes color");
  show_chosen_color_info(ui->PaletteVertex, ui->labelVertexRGB, vertex_color);
  emit data_updated(0, VERT_COLOR);
}

void ViewSetup::set_background_color() {
  has_changed = true;
  backg_color =
      QColorDialog::getColor(backg_color, this, "Select background color");
  show_chosen_color_info(ui->PaletteBackground, ui->labelBackgroundRGB,
                         backg_color);
  emit data_updated(0, BACK_COLOR);
}

void ViewSetup::edge_size_ch(int pos) {
  has_changed = true;
  edge_size = pos;
  emit data_updated(0, EDGE_SIZE);
}

void ViewSetup::vertex_size_ch(int pos) {
  has_changed = true;
  vertex_size = pos;
  emit data_updated(0, VERT_SIZE);
}

void ViewSetup::reset_setup() {
  ui->CBProjStyle->setCurrentIndex(0);
  ui->CBEdgeStyle->setCurrentIndex(0);
  ui->CBVertexStyle->setCurrentIndex(0);
  ui->HSVertexSize->setDisabled(false);
  ui->HSVertexSize->setValue(2);
  ui->HSEdgeSize->setValue(2);
  edge_color = Qt::gray;
  vertex_color = Qt::black;
  backg_color = Qt::white;
  edge_size = 2;
  vertex_size = 2;
  show_chosen_color_info(ui->PaletteEdge, ui->labelEdgeRGB, edge_color);
  show_chosen_color_info(ui->PaletteVertex, ui->labelVertexRGB, vertex_color);
  show_chosen_color_info(ui->PaletteBackground, ui->labelBackgroundRGB,
                         backg_color);

  emit data_updated(0, RESET_VIEW);
}

void ViewSetup::show_chosen_color_info(QPushButton *btn, QLabel *txt,
                                       QColor col) {
  btn->setStyleSheet(
      "border: 2px solid grey;"
      "color: " +
      col.name());
  txt->setText("R: " + QString::number(col.red()) +
               " G: " + QString::number(col.green()) +
               " B: " + QString::number(col.blue()));
}
