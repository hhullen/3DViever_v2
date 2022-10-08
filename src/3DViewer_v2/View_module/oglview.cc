#include "oglview.h"

#include "ui_oglview.h"

namespace S21 {

OGLview::OGLview(QWidget *parent) : QOpenGLWidget(parent), ui_(new Ui::OGLview) {
  ui_->setupUi(this);
  new_cursor_.setShape(Qt::OpenHandCursor);
  setCursor(new_cursor_);

  background_color_ = Qt::white;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(clear_message()));
}

OGLview::~OGLview() { delete ui_; }

void OGLview::set_key_spcace_state(bool state) {
    key_space_ = state;
}

void OGLview::DrawModel() {
    if (vertexes && indices) {
        GetVertexesBuffer();
        update();
    }
}

void OGLview::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  start_z_position_ = axis_scale_ / qTan(fov * M_PI / 180) + 1;
}

void OGLview::resizeGL(int w, int h) {
  window_W = w;
  window_H = h;
  screenRatio = w / float(h);

  glViewport(0, 0, w, h);
  SetProjectionType();
}

void OGLview::paintGL() {
  glClearColor(background_color_.redF(), background_color_.greenF(),
               background_color_.blueF(), 1.0f);
  if (vertexes && indices) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (projection_type_changed_) {
        SetProjectionType();
    }
    SetModelPosition();
//    get_vertexes_buffer();
    glEnableClientState(GL_VERTEX_ARRAY);
    DrawPoints();
    DrawLines();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void OGLview::GetVertexesBuffer() {
  glVertexPointer(3, GL_DOUBLE, 0, vertexes->data());
}

void OGLview::SetModelPosition() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0, 0, -start_z_position_);
  glTranslated(posX, posY, posZ - 5);
  glRotatef(angleX, -1, 0, 0);
  glRotatef(angleY, 0, 1, 0);
  glScalef(scale, scale, scale);
}

void OGLview::DrawPoints() {
  if (vertexes_style_ == VertexStyle::ROUND) {
    glEnable(GL_POINT_SMOOTH);
  } else if (vertexes_style_ == VertexStyle::SQUARE) {
    glDisable(GL_POINT_SMOOTH);
  }
  glPointSize(vertexes_size_);
  glColor3d(vertexes_color_.redF(), vertexes_color_.greenF(),
            vertexes_color_.blueF());
  if (vertexes_style_ != VertexStyle::NONE) {
      glDrawArrays(GL_POINTS, 0, vertexes->size());
  }
}

void OGLview::DrawLines() {
  if (edges_style_ == EdgeStyle::STIPPLE) {
    glLineStipple(2, 0x00F0);
    glEnable(GL_LINE_STIPPLE);
  } else if (edges_style_ == EdgeStyle::SOLID) {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineWidth(edges_size_);
  glColor3d(edges_color_.redF(), edges_color_.greenF(), edges_color_.blueF());
  glDrawElements(GL_LINES, indices->size(), GL_UNSIGNED_INT,
                 indices->data());
}

void OGLview::SetProjectionType() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type_ == ProjectionType::PERSPECTIVE) {
    glFrustum(-axis_scale_ * screenRatio, axis_scale_ * screenRatio, -axis_scale_,
              axis_scale_, 4, far_dist + 3000);
    glTranslated(0, 0, -start_z_position_);
  } else if (projection_type_ == ProjectionType::ORTHOGONAL) {
    glOrtho(-axis_scale_ * screenRatio, axis_scale_ * screenRatio, -axis_scale_,
            axis_scale_, 4, far_dist + 3000);
    glTranslated(0, 0, -start_z_position_);
  }
    projection_type_changed_ = false;
}

void OGLview::ShowEventMessage(QString message, int delay) {
  ui_->label_message->setText(message);
  timer->start(delay);
}

void OGLview::ClearMessageSlot() { ui_->label_message->clear(); }

void OGLview::mousePressEvent(QMouseEvent *event) {
  mouse_now_ = event->pos();
  new_cursor_.setShape(Qt::ClosedHandCursor);
  setCursor(new_cursor_);
  left_mouse_button_ = event->button() == Qt::LeftButton;
}

void OGLview::mouseReleaseEvent(QMouseEvent *event) {
  new_cursor_.setShape(Qt::OpenHandCursor);
  setCursor(new_cursor_);
  left_mouse_button_ = false;
}

void OGLview::mouseMoveEvent(QMouseEvent *event) {
  mouse_now_ = event->pos() - mouse_now_;
  if ((mouse_now_.x() != 0 || mouse_now_.y() != 0) && left_mouse_button_)
    move_model_by_mouse(mouse_now_);
  mouse_now_ = event->pos();
}

void OGLview::wheelEvent(QWheelEvent *event) {
  if (event->pixelDelta().y() != 0 && key_space_)
    move_model_by_wheel(event->pixelDelta().y());
  else if (event->pixelDelta().y() != 0 && !key_space_)
    scale_model_by_wheel(event->pixelDelta().y());
}

void OGLview::move_model_by_wheel(int dz) {
  if (dz > 0) {
    posZ += 1;
  } else if (dz < 0) {
    posZ -= 1;
  }
  update();
}

void OGLview::scale_model_by_wheel(int ds) {
  if (ds < 0) {
    scale *= 0.9;
  } else if (ds > 0) {
    scale *= 1.1111111;
  }
  update();
}

void OGLview::move_model_by_mouse(QPoint pos) {
  if (key_space_) {
    dxMove = axis_scale_ * 2 * pos.x() / window_W;
    dyMove = axis_scale_ * 2 * -pos.y() / window_H;

    posX += dxMove;
    posY += dyMove;
  } else {
    dxRotate = axis_scale_ * 100 * pos.x() / window_W;
    dyRotate = axis_scale_ * 100 * -pos.y() / window_H;

    increase_angle(&angleX, dyRotate);
    increase_angle(&angleY, dxRotate);
  }
  update();
}

void OGLview::increase_angle(double *angle, double dr) {
  *angle += dr;
  if (*angle >= 360) {
    *angle -= 360;
  } else if (*angle <= -360) {
    *angle += 360;
  }
}

}

