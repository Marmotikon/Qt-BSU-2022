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

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(AbstractController* controller);

  // QMenu* GetMenu();
  // void Update();

 private:
  void ManageMenu();
  void ShowResetProgressDialog();
  void ManageMainPage();
  void ManagePickAnOnpion();
  void ManageInputAnswer();
  void ManageAudio();
 private:
  AbstractController* controller_;

  QSettings* settings_;
  QMenu* menu_;
  QWidget* central_widget_;
  QHBoxLayout* main_layout_;

  QWidget* main_menu_widget_;
  QWidget* pick_an_option_widget_;
  QWidget* input_answer_widget_;
  QWidget* audio_widget_;

  QGridLayout* main_menu_layout_;
  QGridLayout* pick_an_option_layout_;
  QGridLayout* input_answer_layout_;
  QGridLayout* audio_layout_;

  QPushButton* pick_an_option_;
  QPushButton* input_answer_;
  QPushButton* audio_;
  QPushButton* mixed_;

};
