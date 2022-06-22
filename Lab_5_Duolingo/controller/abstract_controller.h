#pragma once

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QPushButton>

class AbstractController : public QObject {
  Q_OBJECT
 public:
  virtual void ManageDifficultyMenu(QMenu* difficulty_menu) = 0;
  virtual void ManageSoundMenu(QMenu* sound_menu) = 0;
  virtual void ConnectResetProgressAction(QAction* reset_progress_action) = 0;
  virtual void ConnectExitButton(QPushButton* exit_button) = 0;

  virtual void ShowResetProgressDialog() = 0;
  virtual void ShowExitDialog() = 0;

  virtual void OnCorrect() = 0;
  virtual void OnWrong() = 0;
  virtual void OnWin() = 0;
  virtual void OnLose() = 0;
};

