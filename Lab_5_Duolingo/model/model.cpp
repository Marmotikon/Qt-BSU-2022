#include "model.h"

Model::Model(AbstractController* controller) :
    controller_(controller),
    settings_(new QSettings("2DaysBeforeDeadlineCorp", "Dualingo")) {
  TasksInit();
}

void Model::SetDifficultyMode(const QString& value) {
  settings_->setValue("difficulty", value);
}

QString Model::GetDifficultyMode() {
  return settings_->value("difficulty","easy").toString();
}

void Model::SetSoundMode(QString value) {
  settings_->setValue("sound", value);
}

bool Model::IsSoundOn() {
  return settings_->value("sound","on").toString() == "on";
}

void Model::AddProgressPoints(int value) {
  value += settings_->value("progress").toInt();
  settings_->setValue("progress", value);
}

void Model::ResetProgressPoints() {
  settings_->setValue("progress", 0);
}

int Model::GetProgressPoints() {
  return settings_->value("progress", 0).toInt();
}

QString Model::GetCondition() {
  return current_task_->GetStatement();
}

std::vector<QString> Model::GetVariants() {
  return current_task_->GetVariants();
}

void Model::SwitchToNextTask() {
  current_task_->SwitchToNextTask();
}

void Model::CheckAnswer(const QString& answer) {
  if (current_task_->IsAnswerCorrect(answer)) {
    current_correct_count_++;
    if (current_correct_count_ == current_task_->GetCorrectNeeded()) {
      AddProgressPoints(current_task_->GetWinPoints());
      controller_->OnWin();
    } else {
      controller_->OnCorrect();
    }
  } else {
    attempts_remained_--;
    if (attempts_remained_ == 0) {
      controller_->OnLose();
    } else {
      controller_->OnWrong();
    }
  }
}

int Model::GetAttemptsRemained() const {
  return attempts_remained_;
}

int Model::GetCurrentCorrectCount() const {
  return current_correct_count_;
}

void Model::StartNewExercise(const QString& task_mode) {
  current_correct_count_ = 0;
  QString difficulty = settings_->value("difficulty").toString();
  attempts_remained_ = constants::kAttempts.at(difficulty);
  current_task_ =
      tasks_.at(task_name_to_index_.at(task_mode).at(difficulty)).get();
  SwitchToNextTask();
}

void Model::TasksInit() {
  for (auto [mode, map_temp] : task_name_to_index_) {
    for (auto [difficulty, index] : map_temp) {
      tasks_.push_back(std::make_unique<Task>());
      tasks_.back()->LoadTasks(constants::kFilenames.at(mode).at(difficulty));
      tasks_.back()->SetTaskMode(mode);
      tasks_.back()->SetDifficulty(difficulty);
    }
  }
}

int Model::GetCorrectNeeded() {
  return current_task_->GetCorrectNeeded();
}
const QString& Model::GetCorrectAnswer() {
  return current_task_->GetCorrectAnswer();
}
