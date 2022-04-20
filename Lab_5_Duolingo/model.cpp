#include "model.h"

#include <QFile>


Model::Model() :
    settings_(new QSettings("2DaysBeforeDeadlineCorp", "Dualingo")) {
  PickAnOptionLoadTasks(pao_easy_filename_, pao_easy_tasks_);
  PickAnOptionLoadTasks(pao_medium_filename_, pao_medium_tasks_);
  PickAnOptionLoadTasks(pao_hard_filename_, pao_hard_tasks_);
}



void Model::SetDifficultyMode(QString value) {
  settings_->setValue("difficulty", value);
}

QString Model::GetDifficultyMode() {
  return settings_->value("difficulty","easy").toString();
}

void Model::SetSoundMode(QString value) {
  settings_->setValue("sound", value);
}

QString Model::GetSoundMode() {
  return settings_->value("sound","on").toString();
}

void Model::AddProgressPoints(int value) {
  value += settings_->value("progress").toInt();
  settings_->setValue("progress", value);
}

void Model::ResetProgressPoints() {
  settings_->setValue("progress", 0);
}

QString Model::GetProgressPoints() {
  return settings_->value("progress", 0).toString();
}

void Model::PickAnOptionLoadTasks(const QString& file_name,
    std::vector<std::vector<QString>>& tasks) {
  QFile file(file_name);
  file.open(QIODevice::ReadOnly);
  QTextStream text_stream(&file);

  int tasks_count = text_stream.readLine().toInt();
  text_stream.readLine();
  tasks.resize(tasks_count);
  for (int i = 0; i < tasks_count; i++) {
    tasks[i].push_back(text_stream.readLine());
    int variant_count = text_stream.readLine().toInt();
    for (int j = 0; j < variant_count; j++) {
      tasks[i].push_back(text_stream.readLine());
    }
    tasks[i].push_back(text_stream.readLine());
    text_stream.readLine();
  }
}

std::vector<QString> Model::GetPickAnOptionTask() {
  QString difficulty = settings_->value("difficulty").toString();
  if (difficulty == "easy") {
    if (pao_easy_next_task_index == pao_easy_tasks_.size()) {
      pao_easy_next_task_index = 0;
    }
    return pao_easy_tasks_.at(pao_easy_next_task_index++);
  } else if (difficulty == "medium") {
    if (pao_medium_next_task_index == pao_medium_tasks_.size()) {
      pao_medium_next_task_index = 0;
    }
    return pao_medium_tasks_.at(pao_medium_next_task_index++);
  } else {  // hard
    if (pao_hard_next_task_index == pao_hard_tasks_.size()) {
      pao_hard_next_task_index = 0;
    }
    return pao_hard_tasks_.at(pao_hard_next_task_index++);
  }
}

