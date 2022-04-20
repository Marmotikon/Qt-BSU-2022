#include "controller.h"

#include <QActionGroup>
#include <QAction>
#include <QString>
#include <QMessageBox>

#include "main_page_widget.h"
#include "pick_an_option_widget.h"
#include "input_answer_widget.h"
#include "audio_widget.h"

Controller::Controller() : model_(std::make_unique<Model>(this)),
    view_(std::make_unique<MainWindow>(this)) {
  ConnectMainPageButtons();
  ConnectPickAnOptionButtons();
  ConnectInputAnswerButtons();
  ConnectAudioButtons();

  view_->show();
  view_->Update();
}

void Controller::ManageDifficultyMenu(QMenu* difficulty_menu) {
  auto* set_easy_difficulty = difficulty_menu->addAction("Легкая");
  auto* set_medium_difficulty = difficulty_menu->addAction("Средняя");
  auto* set_hard_difficulty = difficulty_menu->addAction("Сложная");

  set_easy_difficulty->setCheckable(true);
  set_medium_difficulty->setCheckable(true);
  set_hard_difficulty->setCheckable(true);

  auto* difficulty_group = new QActionGroup(this);
  difficulty_group->addAction(set_easy_difficulty);
  difficulty_group->addAction(set_medium_difficulty);
  difficulty_group->addAction(set_hard_difficulty);
  difficulty_group->setExclusive(true);

  connect(set_easy_difficulty, &QAction::triggered, this,
          [this] {
            model_->SetDifficultyMode("easy");
            view_->statusBar()->showMessage("easy");
          });
  connect(set_medium_difficulty, &QAction::triggered, this,
          [this] {
            model_->SetDifficultyMode("medium");
            view_->statusBar()->showMessage("medium");
          });
  connect(set_hard_difficulty, &QAction::triggered, this,
          [this] {
            model_->SetDifficultyMode("hard");
            view_->statusBar()->showMessage("hard");
          });

  if (model_->GetDifficultyMode() == "easy") {
    set_easy_difficulty->setChecked(true);
  } else if (model_->GetDifficultyMode() == "medium") {
    set_medium_difficulty->setChecked(true);
  } else {
    set_hard_difficulty->setChecked(true);
  }
}

void Controller::ManageSoundMenu(QMenu* sound_menu) {
  auto* set_sound_on = sound_menu->addAction("Включить");
  auto* set_sound_off = sound_menu->addAction("Выключить");

  set_sound_on->setCheckable(true);
  set_sound_off->setCheckable(true);

  auto* sound_group = new QActionGroup(this);
  sound_group->addAction(set_sound_on);
  sound_group->addAction(set_sound_off);
  sound_group->setExclusive(true);

  connect(set_sound_on, &QAction::triggered, this,
          [this] {
            model_->SetSoundMode("on");
            view_->statusBar()->showMessage("by Hans Zimmer)");
            view_->Update();
          });
  connect(set_sound_off, &QAction::triggered, this,
          [this] {
            model_->SetSoundMode("off");
            view_->statusBar()->showMessage("Тишина должна быть в библиотеке)");
            view_->Update();
          });

  if (model_->GetSoundMode() == "on") {
    set_sound_on->setChecked(true);
  } else {
    set_sound_off->setChecked(true);
  }
}

void Controller::ConnectResetProgressAction(QAction* reset_progress_action) {
  connect(reset_progress_action, &QAction::triggered, this,
          &Controller::ShowResetProgressDialog);
}

void Controller::ConnectExitButton(QPushButton* exit_button) {
  connect(exit_button, &QPushButton::pressed, this,
          &Controller::ShowExitDialog);
  exit_button->setShortcut(QKeySequence("Ctrl+Q"));
}

void Controller::ShowResetProgressDialog() {
  auto answer = QMessageBox::question(view_->centralWidget(), "Duolingo",
                                      "Вы уверены, что хотите сбросить текущий прогресс?");
  if (answer == QMessageBox::Yes) {
    model_->ResetProgressPoints();
    view_->statusBar()->showMessage("Начнем с презент симпл)");
    view_->Update();
  } else {
    view_->statusBar()->showMessage("Это было опасно)");
  }
}

void Controller::ShowExitDialog() {
  auto answer = QMessageBox::question(view_->centralWidget(), "Duolingo",
                                      "Вы уверены, что хотите выйти?");
  if (answer == QMessageBox::Yes) {
    view_->close();
  } else {
    view_->statusBar()->showMessage("Не выходи из комнаты, не совершай ошибку)");
  }
}

void Controller::ConnectMainPageButtons() {
  auto* widget = view_->GetMainPage();
  connect(widget, &MainPageWidget::PickAnOptionButtonPressed, this, [this] {
    view_->GoToPickAnOption();
  });
  connect(widget, &MainPageWidget::InputAnswerButtonPressed, this, [this] {
    view_->GoToInputAnswer();
  });
  connect(widget, &MainPageWidget::AudioButtonPressed, this, [this] {
    view_->GoToAudio();
  });
  connect(widget, &MainPageWidget::MixedButtonPressed, this, [this] {
    //todo
  });
}

void Controller::ConnectPickAnOptionButtons() {
  auto* widget = view_->GetPickAnOption();
  connect(widget, &PickAnOptionWidget::CheckAnswerButtonPressed, this, [=] {
    widget->BlockButtons();
    view_->UpdateAfterCheck(widget->CheckAnswer());
  });
  connect(widget, &PickAnOptionWidget::NextQuestionButtonPressed, this,
          &Controller::PickAnOptionNextTask);
  connect(widget, &PickAnOptionWidget::GoToMainPageButtonPressed, this, [this] {
    view_->GoToMainPage();
  });
}

void Controller::ConnectInputAnswerButtons() {
  auto* widget = view_->GetInputAnswer();
  connect(widget, &InputAnswerWidget::CheckAnswerButtonPressed, this, [this] {
    //todo
  });
  connect(widget, &InputAnswerWidget::NextQuestionButtonPressed, this, [this] {
    //todo
  });
  connect(widget, &InputAnswerWidget::GoToMainPageButtonPressed, this, [this] {
    view_->GoToMainPage();
  });
}

void Controller::ConnectAudioButtons() {
  auto* widget = view_->GetAudio();
  connect(widget, &AudioWidget::CheckAnswerButtonPressed, this, [this] {
    //todo
  });
  connect(widget, &AudioWidget::NextQuestionButtonPressed, this, [this] {
    //todo
  });
  connect(widget, &AudioWidget::GoToMainPageButtonPressed, this, [this] {
    view_->GoToMainPage();
  });
}

void Controller::PickAnOptionNextTask() {
  auto widget = view_->GetPickAnOption();
  std::vector<QString> task_strings = model_->GetPickAnOptionTask();
  widget->SetTaskText(task_strings.at(0));
  widget->SetRightAnswer(task_strings.at(task_strings.size() - 1).toInt());
  task_strings.erase(task_strings.begin());
  task_strings.erase(--task_strings.end());
  widget->SetVariants(task_strings);
  widget->UpdateView();
}

void Controller::Win() {
  view_->statusBar()->showMessage("Победа победа куриный ужин)");
  model_->AddProgressPoints(1);
  view_->GoToMainPage();
  view_->Update();
}

void Controller::Lose() {
  view_->statusBar()->showMessage("Надеюсь ты хоть не у Ситниковой)");
  view_->GoToMainPage();
}

bool Controller::IsSoundOn() {
  return model_->GetSoundMode() == "on";
}

QString Controller::GetProgressPoints() {
  return model_->GetProgressPoints();
}



