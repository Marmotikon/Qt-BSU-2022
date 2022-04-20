#pragma once

#include <memory>

#include <QObject>

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

  void Win() override;
  void Lose() override;

  //Getters from model
  bool IsSoundOn() override;
  QString GetProgressPoints() override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<MainWindow> view_;
};
