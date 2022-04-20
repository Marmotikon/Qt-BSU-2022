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

  void Update();
  // QMenu* GetMenu();
  // void ShowResetProgressDialog();
  void CreateMenu();

  void GoToMainPage();
  void GoToPickAnOption();
  void GoToInputAnswer();
  void GoToAudio();

 private:
  AbstractController* controller_;

  // QMenu* menu_; todo
  // QHBoxLayout* main_layout_;
  QLabel* progress_points_;
  QProgressBar* progress_bar_;

  QWidget* central_widget_;
  QVBoxLayout* central_layout_;

  MainPageWidget* main_page_widget_;
  PickAnOptionWidget* pick_an_option_widget_;
  InputAnswerWidget* input_answer_widget_;
  AudioWidget* audio_widget_;
};
