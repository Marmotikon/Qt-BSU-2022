#pragma once

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QPushButton>
#include <QSettings>
#include <QSoundEffect>
#include <QStatusBar>

#include <memory>

#include "abstract_controller.h"
#include "audio_widget.h"
#include "constants.h"
#include "input_answer_widget.h"
#include "main_page_widget.h"
#include "pick_an_option_widget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(AbstractController* controller);

  MainPageWidget* GetMainPage();
  PickAnOptionWidget* GetPickAnOption();
  InputAnswerWidget* GetInputAnswer();
  AudioWidget* GetAudio();

  void CreateMenu();
  void ManageCentralWidget();
  void ManageSounds();

  void MuteSounds();
  void UnmuteSounds();

  void GoToMainPage();
  void GoToPickAnOption();
  void GoToInputAnswer();
  void GoToAudio();

  void GoToWinPage();
  void GoToLosePage();

  void Update();

  void OnCorrect();
  void OnWrong();
  void OnWin();
  void OnLose();

 private:
  void GoToTaskMode();

  AbstractController* controller_;

  QLabel* progress_points_;
  QProgressBar* progress_bar_;

  QWidget* central_widget_;
  QVBoxLayout* central_layout_;

  MainPageWidget* main_page_widget_;
  PickAnOptionWidget* pick_an_option_widget_;
  InputAnswerWidget* input_answer_widget_;
  AudioWidget* audio_widget_;

  QLabel* attempts_;
  QPushButton* exit_;

  QSoundEffect* right_sound_;
  QSoundEffect* wrong_sound_;
  QSoundEffect* lose_sound_;
  QSoundEffect* win_sound_;
};
