#include <QMessageBox>
#include <QActionGroup>

#include "main_window.h"
#include "pick_an_option_widget.h"
#include "input_answer_widget.h"

MainWindow::MainWindow(AbstractController* controller) :
    QMainWindow(nullptr), //todo
    controller_(controller),
    central_widget_(new QWidget(this)),
    main_layout_(new QHBoxLayout()),

    main_page_widget_(new QWidget(this)),
    pick_an_option_widget_(new PickAnOptionWidget()),
    input_answer_widget_(new InputAnswerWidget()),
    audio_widget_(new QWidget(this)),

    main_menu_layout_(new QGridLayout(/*main_page_widget_*/)),
    input_answer_layout_(new QGridLayout(/*input_answer_widget_*/)),
    audio_layout_(new QGridLayout(/*audio_widget_*/)),

    pick_an_option_(new QPushButton("Выбери правильный вариант", this)),
    input_answer_(new QPushButton("Введи ответ", this)),
    audio_(new QPushButton("Аудио", this)),
    mixed_(new QPushButton("Рандом", this))
    {
  statusBar()->setVisible(true);

  resize(400, 400);

  main_layout_->addWidget(main_page_widget_);
  main_layout_->addWidget(pick_an_option_widget_);
  main_layout_->addWidget(input_answer_widget_);
  main_layout_->addWidget(audio_widget_);

  ManageMainPage();
  // ManagePickAnOnpion();
  // ManageInputAnswer();
  // ManageAudio();

  main_page_widget_->show();
  pick_an_option_widget_->hide();
  input_answer_widget_->hide();
  audio_widget_->hide();

  central_widget_->setLayout(main_layout_);
  setCentralWidget(central_widget_);

  // QAction* exit_action = new QAction;
  // exit_action->setShortcut(QKeySequence("u"));
  //     connect(exit_action, &QAction::triggered, this, &MainWindow::close);

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


void MainWindow::ManageMainPage() {
  main_menu_layout_->addWidget(pick_an_option_, 0, 1);
  main_menu_layout_->addWidget(input_answer_, 1, 1);
  main_menu_layout_->addWidget(audio_, 2, 1);
  main_menu_layout_->addWidget(mixed_, 3, 1);

  main_menu_layout_->setColumnStretch(0, 1);
  main_menu_layout_->setColumnStretch(1, 8);
  main_menu_layout_->setColumnStretch(2, 1);

  main_page_widget_->setLayout(main_menu_layout_);

  connect(pick_an_option_, &QPushButton::clicked, this,
          [this] {
    GoToPickAnOption();
  });
  connect(input_answer_, &QPushButton::clicked, this,
          [this] {
    GoToInputAnswer();
  });
  connect(pick_an_option_, &QPushButton::clicked, this,
          [this] {
    GoToPickAnOption();
  });
  connect(pick_an_option_, &QPushButton::clicked, this,
          [this] {
    GoToPickAnOption();
  });
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

void MainWindow::GoToPickAnOption() {
  main_page_widget_->hide();
  pick_an_option_widget_->show();
  input_answer_widget_->hide();
  audio_widget_->hide();
}

void MainWindow::CreateMenu() {
  auto* difficulty_menu = menuBar()->addMenu("Сложность");
  controller_->ManageDifficultyMenu(difficulty_menu);

  auto* sound_menu = menuBar()->addMenu("Звук");
  controller_->ManageSoundMenu(sound_menu);

  auto* reset_progress_action = menuBar()->addAction("Сбросить прогресс");
  controller_->ManageResetProgressAction(reset_progress_action);
}

void MainWindow::GoToInputAnswer() {
  main_page_widget_->hide();
  pick_an_option_widget_->hide();
  input_answer_widget_->show();
  audio_widget_->hide();
}
