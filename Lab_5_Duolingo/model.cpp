#include "model.h"

#include <QFile>


Model::Model(AbstractController* controller) :
    controller_(controller),
    settings_(new QSettings("2DaysBeforeDeadlineCorp", "Dualingo")) {
  PickAnOptionLoadTasks(pick_an_option_.easy_filename_, 
                        pick_an_option_.easy_tasks);
  PickAnOptionLoadTasks(pick_an_option_.medium_filename_, 
                        pick_an_option_.medium_tasks);
  PickAnOptionLoadTasks(pick_an_option_.hard_filename_, 
                        pick_an_option_.hard_tasks);
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
    if (pick_an_option_.easy_next_index == pick_an_option_.easy_tasks.size()) {
      pick_an_option_.easy_next_index = 0;
    }
    return pick_an_option_.easy_tasks.at(pick_an_option_.easy_next_index++);
  } else if (difficulty == "medium") {
    if (pick_an_option_.medium_next_index == pick_an_option_.medium_tasks.size()) {
      pick_an_option_.medium_next_index = 0;
    }
    return pick_an_option_.medium_tasks.at(pick_an_option_.medium_next_index++);
  } else {  // hard
    if (pick_an_option_.hard_next_index == pick_an_option_.hard_tasks.size()) {
      pick_an_option_.hard_next_index = 0;
    }
    return pick_an_option_.hard_tasks.at(pick_an_option_.hard_next_index++);
  }
}

