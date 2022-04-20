#include "task.h"

#include "QDebug"

void Task::LoadTasks(const QString& file_name) {
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QTextStream text_stream(&file);

    tasks_count_ = text_stream.readLine().toInt();
    text_stream.readLine();
    variants_.resize(tasks_count_);
    for (int i = 0; i < tasks_count_; i++) {
      conditions_.push_back(text_stream.readLine());
      int variant_count = text_stream.readLine().toInt();
      for (int j = 0; j < variant_count; j++) {
        variants_[i].push_back(text_stream.readLine());
      }
      answers_.push_back(text_stream.readLine());
      text_stream.readLine();
    }
}

QString Task::GetCondition() {
  return conditions_.at(current_task_index_);
}

void Task::SetTaskMode(const QString& mode) {
  mode_ = mode;
}

void Task::SetDifficulty(const QString& difficulty) {
  difficulty_ = difficulty;
}

std::vector<QString> Task::GetVariants() {
  return variants_.at(current_task_index_);
}

void Task::SwitchToNextTask() {
  current_task_index_++;
  if (current_task_index_ == tasks_count_) {
    current_task_index_ = 0;
  }
}

bool Task::IsAnswerCorrect(const QString& answer) {
  return answers_.at(current_task_index_) == answer;
}

int Task::GetCorrectNeeded() {
  return constants::kCorrectNeeded.at(difficulty_);
}

int Task::GetWinPoints() {
  return constants::kWinPoints.at(mode_).at(difficulty_);
}
const QString& Task::GetCorrectAnswer() {
  return answers_.at(current_task_index_);
}

