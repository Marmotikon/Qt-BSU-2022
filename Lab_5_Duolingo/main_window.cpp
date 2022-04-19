#include <QMessageBox>
#include <QActionGroup>

#include "main_window.h"

MainWindow::MainWindow(AbstractController* controller) :
    QMainWindow(nullptr),
    controller_(controller),
    settings_(new QSettings("2DaysBeforeDeadlineCorp", "Dualingo")),
    central_widget_(new QWidget(this)),
    main_layout_(new QHBoxLayout()),

    main_menu_widget_(new QWidget(this)),
    pick_an_option_widget_(new QWidget(this)),
    input_answer_widget_(new QWidget(this)),
    audio_widget_(new QWidget(this)),

    main_menu_layout_(new QGridLayout(/*main_menu_widget_*/)),
    pick_an_option_layout_(new QGridLayout(/*pick_an_option_widget_*/)),
    input_answer_layout_(new QGridLayout(/*input_answer_widget_*/)),
    audio_layout_(new QGridLayout(/*audio_widget_*/)),

    pick_an_option_(new QPushButton("Выбери правильный вариант", this)),
    input_answer_(new QPushButton("Введи ответ", this)),
    audio_(new QPushButton("Аудио", this)),
    mixed_(new QPushButton("Рандом", this))
    {
  statusBar()->setVisible(true);

  resize(400, 400);

  main_layout_->addWidget(main_menu_widget_);
  main_layout_->addWidget(pick_an_option_widget_);
  main_layout_->addWidget(input_answer_widget_);
  main_layout_->addWidget(audio_widget_);

  ManageMainPage();
  ManagePickAnOnpion();
  ManageInputAnswer();
  ManageAudio();

  main_menu_widget_->show();
  pick_an_option_widget_->hide();
  input_answer_widget_->hide();
  audio_widget_->hide();

  central_widget_->setLayout(main_layout_);
  setCentralWidget(central_widget_);

  QAction* exit_action = new QAction;
  exit_action->setShortcut(QKeySequence("u"));
      connect(exit_action, &QAction::triggered, this, &MainWindow::close);

  // auto* progress_label = new QLabel("Progress: 0");
  // statusBar()->addPermanentWidget(progress_label);
  // if (settings_->contains("progress")) {
  //   progress_label->setText(settings_->value("progress"));
  // }
  // statusBar()->setVisible(false);

      // connect(input_answer_, &QPushButton::clicked, this,
      //         [this]{
      //   // central_widget_->setVisible(false);
      //   central_widget_->setLayout(input_answer_layout_);
      // });

  ManageMenu();
}

void MainWindow::ManageMenu() {
  // Manage difficulty menu
  auto* difficulty_menu = menuBar()->addMenu("Сложность");

  auto* set_easy_difficulty = difficulty_menu->addAction("Легкая");
  auto* set_medium_difficulty = difficulty_menu->addAction("Средняя");
  auto* set_hard_difficulty = difficulty_menu->addAction("Сложная");

  set_easy_difficulty->setCheckable(true);
  set_medium_difficulty->setCheckable(true);
  set_hard_difficulty->setCheckable(true);

  auto* difficulty_group = new QActionGroup(menuBar());
  difficulty_group->addAction(set_easy_difficulty);
  difficulty_group->addAction(set_medium_difficulty);
  difficulty_group->addAction(set_hard_difficulty);
  difficulty_group->setExclusive(true);

  connect(set_easy_difficulty, &QAction::triggered, this,
          [this] {
            // controller_->SetDifficultyMode(
            //     AbstractController::DifficultyMode::easy);
            settings_->setValue("difficulty", "easy");
            statusBar()->showMessage("easy");
            // Update();
          });
  connect(set_medium_difficulty, &QAction::triggered, this,
          [this] {
            // controller_->SetDifficultyMode(
            //     AbstractController::DifficultyMode::medium);
            settings_->setValue("difficulty", "medium");
            statusBar()->showMessage("medium");
            // Update();
          });
  connect(set_hard_difficulty, &QAction::triggered, this,
          [this] {
            // controller_->SetDifficultyMode(
            //     AbstractController::DifficultyMode::hard);
            settings_->setValue("difficulty", "hard");
            statusBar()->showMessage("hard");
            // Update();
          });

  settings_->setValue("difficulty", "easy");
  set_easy_difficulty->setChecked(true);



    // Manage sound menu
  auto* sound_menu = menuBar()->addMenu("Звук");

  auto* set_sound_on = sound_menu->addAction("Включить");
  auto* set_sound_off = sound_menu->addAction("Выключить");

  set_sound_on->setCheckable(true);
  set_sound_off->setCheckable(true);

  auto* sound_group = new QActionGroup(menuBar());
  sound_group->addAction(set_sound_on);
  sound_group->addAction(set_sound_off);
  sound_group->setExclusive(true);

  connect(set_sound_on, &QAction::triggered, this,
          [this] {
            // controller_->SetSoundMode(
            //     AbstractController::SoundMode::on);
            settings_->setValue("sound", "on");
            statusBar()->showMessage("sound on");
            // Update();
          });
  connect(set_sound_off, &QAction::triggered, this,
          [this] {
            // controller_->SetSoundMode(
            //     AbstractController::SoundMode::on);
            settings_->setValue("sound", "off");
            statusBar()->showMessage("sound off");
            // Update();
          });

  settings_->setValue("sound", "on");
  set_sound_on->setChecked(true);

  // Manage reset progress
  auto* reset_progress_action = menuBar()->addAction("Сбросить прогресс");
  connect(reset_progress_action, &QAction::triggered, this,
        &MainWindow::ShowResetProgressDialog);




  // show_context_menu_action->setCheckable(true);
  // connect(show_context_menu_action, &QAction::triggered, this,
  //         [&, show_context_menu_action] {
  //           show_context_menu_ = show_context_menu_action->isChecked();
  //         });

//  menu->addSeparator();

    // // Menu in menu
    // some_menu = menu->addMenu("There is something here");
    // auto* show_dialog_action = some_menu->addAction("Show dialog");
    // // connect(show_dialog_action, &QAction::triggered, this,
    // //         &MainWindow::ShowDialog);
}

// void MainWindow::Update() {
  // switch (difficulty_) {
  //   case Difficulty::easy : {
  //     set_easy_difficulty_->setChecked(true);
  //     set_medium_difficulty_->setChecked(false);
  //     set_hard_difficulty_->setChecked(false);
  //     break;
  //   }
  //   case Difficulty::medium : {
  //     set_easy_difficulty_->setChecked(false);
  //     set_medium_difficulty_->setChecked(true);
  //     set_hard_difficulty_->setChecked(false);
  //     break;
  //   }
  //   case Difficulty::hard : {
  //     set_easy_difficulty_->setChecked(false);
  //     set_medium_difficulty_->setChecked(false);
  //     set_hard_difficulty_->setChecked(true);
  //     break;
  //   }
  // }
  //
  // switch (sound_) {
  //   case Sound::on : {
  //     set_sound_on_->setChecked(true);
  //     set_sound_off_->setChecked(false);
  //     break;
  //   }
  //   case Sound::off : {
  //       set_sound_on_->setChecked(false);
  //       set_sound_off_->setChecked(true);
  //       break;
  //   }
  // }
// }
// QMenu* MainWindow::GetMenu() {
//   return menu_;
// }
void MainWindow::ShowResetProgressDialog() {
  auto answer = QMessageBox::question(this, "Reset progress",
                                      "Вы уверены, что хотите сбросить текущий прогресс");
  if (answer == QMessageBox::Yes) {
    settings_->setValue("progress", 0);
  }
  // statusBar()->showMessage(answer == QMessageBox::Yes ?  "Н" : "Д");
}
void MainWindow::ManageMainPage() {
  main_menu_layout_->addWidget(pick_an_option_, 0, 1);
  main_menu_layout_->addWidget(input_answer_, 1, 1);
  main_menu_layout_->addWidget(audio_, 2, 1);
  main_menu_layout_->addWidget(mixed_, 3, 1);

  main_menu_layout_->setColumnStretch(0, 1);
  main_menu_layout_->setColumnStretch(1, 8);
  main_menu_layout_->setColumnStretch(2, 1);

  main_menu_widget_->setLayout(main_menu_layout_);
}
void MainWindow::ManagePickAnOnpion() {
  // main_menu_layout_->addWidget(pick_an_option_, 0, 1);
  // main_menu_layout_->addWidget(pick_an_option_, 1, 1);
  // main_menu_layout_->addWidget(pick_an_option_, 2, 1);
  // main_menu_layout_->addWidget(pick_an_option_, 3, 1);

  main_menu_layout_->setColumnStretch(0, 1);
  main_menu_layout_->setColumnStretch(1, 8);
  main_menu_layout_->setColumnStretch(2, 1);

  pick_an_option_widget_->setLayout(pick_an_option_layout_);
}
void MainWindow::ManageInputAnswer() {
  // main_menu_layout_->addWidget(input_answer_, 0, 1);
  // main_menu_layout_->addWidget(input_answer_, 1, 1);
  // main_menu_layout_->addWidget(input_answer_, 2, 1);
  // main_menu_layout_->addWidget(input_answer_, 3, 1);

  main_menu_layout_->setColumnStretch(0, 1);
  main_menu_layout_->setColumnStretch(1, 8);
  main_menu_layout_->setColumnStretch(2, 1);

  input_answer_widget_->setLayout(input_answer_layout_);
}
void MainWindow::ManageAudio() {
  // main_menu_layout_->addWidget(audio_, 0, 1);
  // main_menu_layout_->addWidget(audio_, 1, 1);
  // main_menu_layout_->addWidget(audio_, 2, 1);
  // main_menu_layout_->addWidget(audio_, 3, 1);

  main_menu_layout_->setColumnStretch(0, 1);
  main_menu_layout_->setColumnStretch(1, 8);
  main_menu_layout_->setColumnStretch(2, 1);

  audio_widget_->setLayout(audio_layout_);

}
