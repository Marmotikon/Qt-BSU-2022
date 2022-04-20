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
    audio_widget_(new AudioWidget())
    {
  statusBar()->setVisible(true);
  CreateMenu();

  resize(500, 500);
  setMinimumSize(300, 300);

  // main_layout_->addWidget(progress_points_);
  // main_layout_->addWidget(central_widget_);
  // main_layout_->addWidget(progress_bar_);


  central_layout_->addWidget(progress_points_);
  central_layout_->addWidget(main_page_widget_);
  central_layout_->addWidget(pick_an_option_widget_);
  central_layout_->addWidget(input_answer_widget_);
  central_layout_->addWidget(audio_widget_);
  central_layout_->addWidget(progress_bar_);

  central_layout_->setStretch(0, 1);
  central_layout_->setStretch(1, 10);
  central_layout_->setStretch(2, 10);
  central_layout_->setStretch(3, 10);
  central_layout_->setStretch(4, 10);
  central_layout_->setStretch(5, 2);

  setCentralWidget(central_widget_);
  central_widget_->setLayout(central_layout_);
  GoToMainPage();

  connect(progress_points_, &QMainWindow::customContextMenuRequested, this,
          [this] {
    controller_->ShowResetProgressDialog();
  });
  central_widget_->setContextMenuPolicy(Qt::NoContextMenu);
  progress_points_->setContextMenuPolicy(Qt::CustomContextMenu);

  // QAction* exit_action = new QAction;
  // exit_action->setShortcut(QKeySequence("u"));
  //     connect(exit_action, &QAction::triggered, this, &MainWindow::close);

  // auto* progress_label = new QLabel("Progress: 0");
  // statusBar()->addPermanentWidget(progress_label);
  // if (settings_->contains("progress")) {
  //   progress_label->setText(settings_->value("progress"));
  // }
  // statusBar()->setVisible(false);

      // connect(input_answer_button_, &QPushButton::clicked, this,
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

void MainWindow::CreateMenu() {
  auto* difficulty_menu = menuBar()->addMenu("Сложность");
  controller_->ManageDifficultyMenu(difficulty_menu);

  auto* sound_menu = menuBar()->addMenu("Звук");
  controller_->ManageSoundMenu(sound_menu);

  auto* reset_progress_action = menuBar()->addAction("Сбросить прогресс");
  controller_->ConnectResetProgressAction(reset_progress_action);
}

void MainWindow::GoToMainPage() {
  main_page_widget_->show();
  pick_an_option_widget_->hide();
  input_answer_widget_->hide();
  audio_widget_->hide();
  progress_bar_->hide();
}

void MainWindow::GoToPickAnOption() {
  main_page_widget_->hide();
  pick_an_option_widget_->show();
  input_answer_widget_->hide();
  audio_widget_->hide();
  progress_bar_->show();

  pick_an_option_widget_->NextQuestionButtonPressed();
}

void MainWindow::GoToInputAnswer() {
  main_page_widget_->hide();
  pick_an_option_widget_->hide();
  input_answer_widget_->show();
  audio_widget_->hide();
  progress_bar_->show();
}

void MainWindow::GoToAudio() {
  main_page_widget_->hide();
  pick_an_option_widget_->hide();
  input_answer_widget_->hide();
  audio_widget_->show();
  progress_bar_->show();
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
}

void MainWindow::SetProgressPoints(QString string) {
  progress_points_->setText("Текущий прогресс: " + string);
}
