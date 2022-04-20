#pragma once

#include <memory>

#include <QMainWindow>
#include <QMenu>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QSettings>
#include <QProgressBar>
#include <QSoundEffect>

#include "abstract_controller.h"
#include "pick_an_option_widget.h"
#include "main_page_widget.h"
#include "input_answer_widget.h"
#include "audio_widget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(AbstractController* controller);

  MainPageWidget* GetMainPage();
  PickAnOptionWidget* GetPickAnOption();
  InputAnswerWidget* GetInputAnswer();
  AudioWidget* GetAudio();

  void SetProgressPoints(QString);
  void UpdateAfterCheck(bool was_right);
  void UpdateAttempts();

  void CreateMenu();
  void ManageCentralWidget();
  void ManageSounds();

  void MuteSounds();
  void UnmuteSounds();

  void GoToMainPage();
  void GoToPickAnOption();
  void GoToInputAnswer();
  void GoToAudio();

  void Update();
 private:
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

  int attempts_count_;
  int tasks_to_complete_;

  QSoundEffect* right_sound_;
  QSoundEffect* wrong_sound_;
  QSoundEffect* lose_sound_;
  QSoundEffect* win_sound_;
};
