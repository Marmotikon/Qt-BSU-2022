#include "model.h"

Model::Model(AbstractController* controller) :
    controller_(controller),
    settings_(new QSettings("2DaysBeforeDeadlineCorp", "Dualingo")) {
  PickAnOptionLoadTasks(constants::pick_an_option_easy_filename,
                        pick_an_option_.easy);
  PickAnOptionLoadTasks(constants::pick_an_option_medium_filename,
                        pick_an_option_.medium);
  PickAnOptionLoadTasks(constants::pick_an_option_hard_filename,
                        pick_an_option_.hard);
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

void Model::PickAnOptionLoadTasks(
    const QString& file_name, Tasks& tasks) {
  QFile file(file_name);
  file.open(QIODevice::ReadOnly);
  QTextStream text_stream(&file);

  tasks.tasks_count = text_stream.readLine().toInt();
  text_stream.readLine();
  tasks.variants.resize(tasks.tasks_count);
  for (int i = 0; i < tasks.tasks_count; i++) {
    tasks.conditions.push_back(text_stream.readLine());
    int variant_count = text_stream.readLine().toInt();
    for (int j = 0; j < variant_count; j++) {
      tasks.variants[i].push_back(text_stream.readLine());
    }
    tasks.answers.push_back(text_stream.readLine().toInt());
    text_stream.readLine();
  }
}

QString Model::GetPickAnOptionCondition() {
  QString difficulty = settings_->value("difficulty").toString();
  if (difficulty == "easy") {
    return pick_an_option_.easy.conditions.at(
        pick_an_option_.easy.current_task_index);
  } else if (difficulty == "medium") {
    return pick_an_option_.medium.conditions.at(
        pick_an_option_.medium.current_task_index);
  } else {  // hard
    return pick_an_option_.hard.conditions.at(
        pick_an_option_.hard.current_task_index);
  }
}

std::vector<QString> Model::GetPickAnOptionVariants() {
  QString difficulty = settings_->value("difficulty").toString();
  if (difficulty == "easy") {
    return pick_an_option_.easy.variants.at(
        pick_an_option_.easy.current_task_index);
  } else if (difficulty == "medium") {
    return pick_an_option_.medium.variants.at(
        pick_an_option_.medium.current_task_index);
  } else {  // hard
    return pick_an_option_.hard.variants.at(
        pick_an_option_.hard.current_task_index);
  }
}

void Model::PickAnOptionNextTask() {
  QString difficulty = settings_->value("difficulty").toString();
  if (difficulty == "easy") {
    pick_an_option_.easy.current_task_index++;
    if (pick_an_option_.easy.current_task_index
        == pick_an_option_.easy.tasks_count) {
      pick_an_option_.easy.current_task_index = 0;
    }
  } else if (difficulty == "medium") {
    pick_an_option_.medium.current_task_index++;
    if (pick_an_option_.medium.current_task_index
        == pick_an_option_.medium.tasks_count) {
      pick_an_option_.medium.current_task_index = 0;
    }
  } else {  // hard
    pick_an_option_.hard.current_task_index++;
    if (pick_an_option_.hard.current_task_index
        == pick_an_option_.hard.tasks_count) {
      pick_an_option_.hard.current_task_index = 0;
    }
  }
}

void Model::PickAnOptionCheckAnswer(int checked_variant) {
  QString difficulty = settings_->value("difficulty").toString();
  if (difficulty == "easy") {
    if (checked_variant == pick_an_option_.easy.answers.at(
        pick_an_option_.easy.current_task_index)) {
      current_correct_count_++;
      if (current_correct_count_ ==
      constants::easy_correct_needed) {
        AddProgressPoints(constants::pick_an_option_easy_win_points);
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
  } else if (difficulty == "medium") {
    if (checked_variant == pick_an_option_.medium.answers.at(
        pick_an_option_.medium.current_task_index)) {
      current_correct_count_++;
      if (current_correct_count_ ==
          constants::medium_correct_needed) {
        AddProgressPoints(constants::pick_an_option_medium_win_points);
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
  } else {  // hard
    if (checked_variant == pick_an_option_.hard.answers.at(
        pick_an_option_.hard.current_task_index)) {
      current_correct_count_++;
      if (current_correct_count_ ==
          constants::hard_correct_needed) {
        AddProgressPoints(constants::pick_an_option_hard_win_points);
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
}

void Model::StartNewPickAnOption() {
  current_correct_count_ = 0;
  QString difficulty = settings_->value("difficulty").toString();
  if (difficulty == "easy") {
    attempts_remained_ = constants::pick_an_option_easy_attempts;
  } else if (difficulty == "medium") {
    attempts_remained_ = constants::pick_an_option_medium_attempts;
  } else {  // hard
    attempts_remained_ = constants::pick_an_option_hard_attempts;
  }
}

int Model::GetAttemptsRemained() {
  return attempts_remained_;
}

int Model::GetCurrentCorrectCount() {
  return current_correct_count_;
}

int Model::GetCorrectNeeded() {
  QString difficulty = settings_->value("difficulty").toString();
  if (difficulty == "easy") {
    return constants::easy_correct_needed;
  } else if (difficulty == "medium") {
    return constants::medium_correct_needed;
  } else {
    return constants::hard_correct_needed;
  }
}
