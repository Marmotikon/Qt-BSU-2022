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

#include "abstract_controller.h"
#include "pick_an_option_widget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(AbstractController* controller);

  // void Update();

  // QMenu* GetMenu();
  // void ShowResetProgressDialog();
  void CreateMenu();
 private:
  void ManageMainPage();
  void ManagePickAnOnpion();
  void ManageInputAnswer();
  void ManageAudio();
  void GoToPickAnOption();
  void GoToInputAnswer();
 private:
  //Main window
  AbstractController* controller_;

  // QSettings* settings_;
  QMenu* menu_;
  QWidget* central_widget_;
  QHBoxLayout* main_layout_;

  QWidget* main_page_widget_;
  PickAnOptionWidget* pick_an_option_widget_;
  QWidget* input_answer_widget_;
  QWidget* audio_widget_;

  QGridLayout* main_menu_layout_;
  QGridLayout* pick_an_option_layout_;
  QGridLayout* input_answer_layout_;
  QGridLayout* audio_layout_;

  //Main page
  QPushButton* pick_an_option_;
  QPushButton* input_answer_;
  QPushButton* audio_;
  QPushButton* mixed_;

  //Pick-an-option


  //Input-answer
  QLabel* task_condition2_;
  QTextBlock* task_text2_;
  QLineEdit* answer_;
  QPushButton* go_to_main_page2_;

  //Audio
  QLabel* task_condition3_;
  QLineEdit* answer3_;
  QPushButton* go_to_main_page3_;
};
