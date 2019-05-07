#include "mainwindow.h"

#include <QCoreApplication>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QObject>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      totalTimeLeftLabel(totalTimeLeft.toString("mm:ss")),
      participantsLeftLabel(QString::number(participantsLeft)),
      participantTimeLeftLabel(participantTimeLeft.toString("mm:ss")) {
  this->setStyleSheet("color: #a00;background:transparent;font-size:15pt;");
  const auto qss = "background:rgba(255,255,255,180);max-width:60px;";
  totalTimeLeftLabel.setStyleSheet(qss);
  participantsLeftLabel.setStyleSheet(qss);
  participantTimeLeftLabel.setStyleSheet(qss);
  auto widget = new QWidget(this);
  this->setCentralWidget(widget);
  layout.addWidget(&totalTimeLeftLabel);
  layout.addWidget(&participantsLeftLabel);
  layout.addWidget(&participantTimeLeftLabel);
  widget->setLayout(&layout);

  connect(&timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  // this->setWindowFlags(Qt::WindowStaysOnTopHint);
  this->setAttribute(Qt::WA_TranslucentBackground);
  QCoreApplication::instance()->installEventFilter(this);
}
void MainWindow::updateCountdown() {
  if (totalTimeLeft > QTime(0, 0, 0)) totalTimeLeft = totalTimeLeft.addSecs(-1);
  if (participantTimeLeft > QTime(0, 0, 0))
    participantTimeLeft = participantTimeLeft.addSecs(-1);
  totalTimeLeftLabel.setText(totalTimeLeft.toString("mm:ss"));
  participantTimeLeftLabel.setText(participantTimeLeft.toString("mm:ss"));
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
  if (qobject_cast<QLabel *>(obj) == &totalTimeLeftLabel &&
      event->type() == QEvent::MouseButtonRelease) {
    totalTimeLeft.setHMS(0, durationInSec / 60, durationInSec % 60);
    participantTimeLeft.setHMS(0, durationInSec / participantsLeft / 60,
                               durationInSec / participantsLeft % 60);
    participantTimeLeftLabel.setText(participantTimeLeft.toString("mm:ss"));
    totalTimeLeftLabel.setText(totalTimeLeft.toString("mm:ss"));
    timer.start(1000);
  } else if (qobject_cast<QLabel *>(obj) == &participantTimeLeftLabel &&
             event->type() == QEvent::MouseButtonRelease) {
    participantsLeftLabel.setNum(participantsLeft);
    participantTimeLeft.setHMS(0, durationInSec / participantsLeft / 60,
                               durationInSec / participantsLeft % 60);
    participantTimeLeftLabel.setText(participantTimeLeft.toString("mm:ss"));
  } else if (qobject_cast<QLabel *>(obj) == &participantsLeftLabel &&
             event->type() == QEvent::Wheel) {
    QWheelEvent *w = static_cast<QWheelEvent *>(event);
    participantsLeft += (w->delta() > 0) ? 1 : -1;
    participantsLeft = participantsLeft > 0 ? participantsLeft : 1;
    participantsLeftLabel.setNum(participantsLeft);
  }
  return false;
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
  m_nMouseClick_X_Coordinate = event->x();
  m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  move(event->globalX() - m_nMouseClick_X_Coordinate,
       event->globalY() - m_nMouseClick_Y_Coordinate);
}
MainWindow::~MainWindow() {}
