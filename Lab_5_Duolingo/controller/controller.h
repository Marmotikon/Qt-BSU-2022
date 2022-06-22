#pragma once

#include <QObject>

#include <memory>

#include "abstract_controller.h"
#include "../view/main_window.h"
#include "../model/model.h"

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

  void OnCorrect() override;
  void OnWrong() override;
  void OnWin() override;
  void OnLose() override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<MainWindow> view_;
};
