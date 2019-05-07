#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  bool eventFilter(QObject *obj, QEvent *event);
 private slots:
  void mousePressEvent(QMouseEvent *event);
  void updateCountdown();

  void mouseMoveEvent(QMouseEvent *event);

 private:
  int m_nMouseClick_X_Coordinate;
  int m_nMouseClick_Y_Coordinate;
  int durationInSec = 15 * 60;
  int participantsLeft = 11;
  QTime totalTimeLeft = {0, durationInSec / 60, durationInSec % 60};
  QTime participantTimeLeft = {0, durationInSec / participantsLeft / 60,
                               durationInSec / participantsLeft % 60};
  QTimer timer;
  QVBoxLayout layout;
  QLabel totalTimeLeftLabel;
  QLabel participantsLeftLabel;
  QLabel participantTimeLeftLabel;
};

#endif  // MAINWINDOW_H
