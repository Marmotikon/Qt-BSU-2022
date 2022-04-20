#pragma once

#include <QObject>

#include <memory>

#include "abstract_controller.h"
#include "main_window.h"
#include "model.h"

class Controller : public AbstractController {
  Q_OBJECT
 public:
  Controller();

  void ManageDifficultyMenu(QMenu* difficulty_menu) override;
  void ManageSoundMenu(QMenu* sound_menu) override;
  void ConnectResetProgressAction(QAction* reset_progress_action) override;
  void ConnectExitButton(QPushButton* exit_button) override;
  void ShowResetProgressDialog() override;
  void ShowExitDialog() override;

  void ConnectMainPageButtons();
  void ConnectPickAnOptionButtons();
  void ConnectInputAnswerButtons();
  void ConnectAudioButtons();

  void PickAnOptionNextTask();

  bool IsSoundOn() override;
  QString GetProgressPoints() override;
  int GetAttemptsRemained() override;
  int GetCurrentCorrectCount() override;
  int GetCorrectNeeded() override;

  void OnCorrect() override;
  void OnWrong() override;
  void OnWin() override;
  void OnLose() override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<MainWindow> view_;
};
