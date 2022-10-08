#ifndef OGLVIEW_H
#define OGLVIEW_H

#define GL_SILENCE_DEPRECATION

#include <QLabel>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <vector>
#include "View_module/enum_parameters.h"
using std::vector;

namespace Ui {
class OGLview;
}

namespace S21 {

class OGLview : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit OGLview(QWidget *parent = nullptr);
  ~OGLview();
    void DrawModel();
  void ShowEventMessage(QString message, int delay);
  void set_key_spcace_state(bool state);

  void set_edges_color(QColor color);
  void set_vertexes_color(QColor color);
  void set_background_color(QColor color);
  void set_projection_type(ProjectionType type);
  void set_edges_style(EdgeStyle style);
  void set_vertexes_style(VertexStyle style);
  void set_edges_size(int size);
  void set_vertexes_size(int size);

  void set_position(double x, double y, double z);
  void set_angle(double x, double y, double z);
  void set_scale(double scale);

  void set_model_vertexes_vector(const vector<double> *vector);
  void set_model_indices_vector(const vector<unsigned int> *vector);
  void set_model_facets_amount(unsigned int facets);

 private slots:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
//  void UpdateFrameSlot();
  void ClearMessageSlot();

 private:
    Ui::OGLview *ui_;
    QCursor new_cursor_;
    QPoint mouse_now_;
    QColor edges_color_;
    QColor vertexes_color_;
    QColor background_color_;
    ProjectionType projection_type_;
    EdgeStyle edges_style_;
    VertexStyle vertexes_style_;
    int edges_size_;
    int vertexes_size_;
    double start_z_position_ = 0;
    double axis_scale_ = 2;

    const vector<double> *vertexes_;
    const vector<unsigned int> *indices_;
    unsigned int facets_n_;

    bool key_space_ = false;
    bool left_mouse_button_ = false;
    bool new_model_loaded_ = false;
    bool projection_type_changed_ = false;

    double position_x_;
    double position_y_;
    double position_z_;
    double angle_x_;
    double angle_y_;
    double angle_z_;
    double scale_;


  QTimer *timer;
  float screenRatio;
  int window_W;
  int window_H;
  double fov = 45;
  double dxMove = 0;
  double dyMove = 0;
  double dxRotate = 0;
  double dyRotate = 0;
//  double posX = 0;
//  double posY = 0;
//  double posZ = 0;
//  double angleX = 0;
//  double angleY = 0;
//  double scale = 1;
  double far_dist = 10;
  unsigned int vertexes_values = 0;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void SetProjectionType();
  void GetVertexesBuffer();
  void SetModelPosition();
  void DrawPoints();
  void DrawLines();
  void MoveModelByMouse(QPoint pos);
  void MoveModelByWheel(int dz);
  void ScaleModelByWheel(int ds);
  void IncreaseAngle(double *angle, double dr);
};

}

#endif  // OGLVIEW_H
