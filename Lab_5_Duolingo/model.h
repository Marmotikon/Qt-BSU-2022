#pragma once

#include <QFile>
#include <QSettings>
#include <QString>

#include <fstream>
#include <vector>

#include "abstract_controller.h"
#include "constants.h"

class Model : public QObject {
  Q_OBJECT
 private:
  struct Tasks {
    std::vector<QString> conditions;
    std::vector<std::vector<QString>> variants;
    std::vector<int> answers;
    int tasks_count;

    int current_task_index{0};
  };

  struct PickAnOption {
    Tasks easy;
    Tasks medium;
    Tasks hard;
  };

 public:
  Model(AbstractController* controller);
  int GetAttemptsRemained();
  int GetCurrentCorrectCount();

  void SetDifficultyMode(QString value);
  QString GetDifficultyMode();

  void SetSoundMode(QString value);
  QString GetSoundMode();

  void AddProgressPoints(int value);
  void ResetProgressPoints();
  QString GetProgressPoints();
  int GetCorrectNeeded();

  static void PickAnOptionLoadTasks(const QString& file_name,
      Tasks& tasks);
  void StartNewPickAnOption();
  QString GetPickAnOptionCondition();
  std::vector<QString> GetPickAnOptionVariants();
  void PickAnOptionNextTask();
  void PickAnOptionCheckAnswer(int checked_variant);

 private:
  AbstractController* controller_;
  PickAnOption pick_an_option_;
  QSettings* settings_;

  int current_correct_count_;
  int attempts_remained_;

};
