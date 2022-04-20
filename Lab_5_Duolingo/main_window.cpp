#include <QMessageBox>
#include <QActionGroup>

#include "main_window.h"
#include "pick_an_option_widget.h"
#include "input_answer_widget.h"

MainWindow::MainWindow(AbstractController* controller) :
    QMainWindow(nullptr), //todo
    controller_(controller),
    // main_layout_(new QHBoxLayout()),
    progress_points_(new QLabel("Набранные очки: ...")),
    progress_bar_(new QProgressBar(this)),

    central_widget_(new QWidget(this)),
    central_layout_(new QVBoxLayout()),

    main_page_widget_(new MainPageWidget()),
    pick_an_option_widget_(new PickAnOptionWidget()),
    input_answer_widget_(new InputAnswerWidget()),
    audio_widget_(new AudioWidget()),

    attempts_(new QLabel("Оставшиеся попытки: ...")),
    exit_(new QPushButton("Выход")),

    right_sound_(new QSoundEffect(this)),
    wrong_sound_(new QSoundEffect(this)),
    lose_sound_(new QSoundEffect(this)),
    win_sound_(new QSoundEffect(this)) {

  resize(500, 500);
  setMinimumSize(300, 300);
  setWindowTitle("Duolingo (made in China)");
  setWindowIcon(QIcon(":/images/icon.jpg"));

  statusBar()->setVisible(true);
  CreateMenu();
  ManageCentralWidget();
  ManageSounds();
  GoToMainPage();

  controller_->ConnectExitButton(exit_);
}

void MainWindow::ManageCentralWidget() {
  central_layout_->addWidget(progress_points_);
  central_layout_->addWidget(main_page_widget_);
  central_layout_->addWidget(pick_an_option_widget_);
  central_layout_->addWidget(input_answer_widget_);
  central_layout_->addWidget(audio_widget_);
  central_layout_->addWidget(progress_bar_);
  central_layout_->addWidget(attempts_);
  central_layout_->addWidget(exit_);

  central_layout_->setStretch(0, 1);
  central_layout_->setStretch(1, 10);
  central_layout_->setStretch(2, 10);
  central_layout_->setStretch(3, 10);
  central_layout_->setStretch(4, 10);
  central_layout_->setStretch(5, 2);
  central_layout_->setStretch(6, 1);
  central_layout_->setStretch(7, 1);

  setCentralWidget(central_widget_);
  central_widget_->setLayout(central_layout_);
}

void MainWindow::ManageSounds() {
  right_sound_->setSource(QUrl("qrc:/sounds/answer_is_right.wav"));
  right_sound_->setLoopCount(1);
  right_sound_->setVolume(1.0f);

  wrong_sound_->setSource(QUrl("qrc:/sounds/answer_is_wrong.wav"));
  wrong_sound_->setLoopCount(1);
  wrong_sound_->setVolume(1.0f);

  lose_sound_->setSource(QUrl("qrc:/sounds/lose.wav"));
  lose_sound_->setLoopCount(1);
  lose_sound_->setVolume(1.0f);

  win_sound_->setSource(QUrl("qrc:/sounds/win.wav"));
  win_sound_->setLoopCount(1);
  win_sound_->setVolume(1.0f);
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

void MainWindow::CreateMenu() {
  auto* difficulty_menu = menuBar()->addMenu("Сложность");
  controller_->ManageDifficultyMenu(difficulty_menu);

  auto* sound_menu = menuBar()->addMenu("Звук");
  controller_->ManageSoundMenu(sound_menu);

  auto* reset_progress_action = menuBar()->addAction("Сбросить прогресс");
  controller_->ConnectResetProgressAction(reset_progress_action);

  progress_points_->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(progress_points_, &QMainWindow::customContextMenuRequested,
          reset_progress_action, &QAction::trigger);
}

void MainWindow::GoToMainPage() {
  menuBar()->show();
  main_page_widget_->show();
  pick_an_option_widget_->hide();
  input_answer_widget_->hide();
  audio_widget_->hide();
  progress_bar_->hide();
  attempts_->hide();
}

void MainWindow::GoToPickAnOption() {
  attempts_count_ = 3;
  tasks_to_complete_ = 10;
  progress_bar_->setValue(0);
  progress_bar_->setMaximum(tasks_to_complete_);
  UpdateAttempts();
  menuBar()->hide();
  main_page_widget_->hide();
  pick_an_option_widget_->show();
  input_answer_widget_->hide();
  audio_widget_->hide();
  progress_bar_->show();
  attempts_->show();

  pick_an_option_widget_->NextQuestionButtonPressed();
}

void MainWindow::GoToInputAnswer() {
  menuBar()->hide();
  main_page_widget_->hide();
  pick_an_option_widget_->hide();
  input_answer_widget_->show();
  audio_widget_->hide();
  progress_bar_->show();
  attempts_->show();
}

void MainWindow::GoToAudio() {
  menuBar()->hide();
  main_page_widget_->hide();
  pick_an_option_widget_->hide();
  input_answer_widget_->hide();
  audio_widget_->show();
  progress_bar_->show();
  attempts_->show();
}

MainPageWidget* MainWindow::GetMainPage() {
  return main_page_widget_;
}

PickAnOptionWidget* MainWindow::GetPickAnOption() {
  return pick_an_option_widget_;
}

InputAnswerWidget* MainWindow::GetInputAnswer() {
  return input_answer_widget_;
}

AudioWidget* MainWindow::GetAudio() {
  return audio_widget_;
}

void MainWindow::Update() {
  if (controller_->IsSoundOn()) {
    UnmuteSounds();
  } else {
    MuteSounds();
  }

  progress_points_->setText(
      "Текущий прогресс: " + controller_->GetProgressPoints());
}

void MainWindow::SetProgressPoints(QString string) {
  progress_points_->setText("Текущий прогресс: " + string);
}
void MainWindow::UpdateAfterCheck(bool was_right) {
  if (was_right) {
    progress_bar_->setValue(progress_bar_->value() + 1);
    if (progress_bar_->value() == tasks_to_complete_) {
      win_sound_->play();
      controller_->Win();
    } else {
      right_sound_->play();
    }
  } else {
    attempts_count_--;
    if (attempts_count_ == 0) {
      lose_sound_->play();
      controller_->Lose();
      // GoToPickAnOption();
    } else {
      wrong_sound_->play();
      UpdateAttempts();
    }
  }
}
void MainWindow::UpdateAttempts() {
  QString string = "Оставшиеся попытки: ";
  string += std::to_string(attempts_count_).c_str();
  attempts_->setText(string);
}

void MainWindow::MuteSounds() {
  right_sound_->setMuted(true);
  wrong_sound_->setMuted(true);
  lose_sound_->setMuted(true);
  win_sound_->setMuted(true);
}

void MainWindow::UnmuteSounds() {
  right_sound_->setMuted(false);
  wrong_sound_->setMuted(false);
  lose_sound_->setMuted(false);
  win_sound_->setMuted(false);
}


