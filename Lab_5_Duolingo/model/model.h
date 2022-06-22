#pragma once

#include <QFile>
#include <QSettings>
#include <QString>

#include <fstream>
#include <vector>
#include <map>

#include "../controller/abstract_controller.h"
#include "constants.h"
#include "task.h"

class Model : public QObject {
  Q_OBJECT
 public:
  explicit Model(AbstractController* controller);

  int GetAttemptsRemained() const;
  int GetCurrentCorrectCount() const;
  int GetCorrectNeeded();
  QString GetCondition();
  std::vector<QString> GetVariants();
  void CheckAnswer(const QString& answer);
  void StartNewExercise(const QString& task_mode);
  void SwitchToNextTask();
  const QString& GetCorrectAnswer();

  // settings
  void SetDifficultyMode(const QString& value);
  QString GetDifficultyMode();
  void SetSoundMode(QString value);
  bool IsSoundOn();
  void AddProgressPoints(int value);
  void ResetProgressPoints();
  int GetProgressPoints();

 private:
  void TasksInit();

  AbstractController* controller_;
  QSettings* settings_;

  int current_correct_count_;
  int attempts_remained_;

  Task* current_task_;
  std::vector<std::unique_ptr<Task>> tasks_;
  std::map<QString, std::map<QString, int>> task_name_to_index_{
      {"pick_an_option",{{"easy",6},
                         {"medium",8},
                         {"hard",7}}},
      {"input_answer", {{"easy",3},
                        {"medium",5},
                        {"hard",4}}},
      {"audio", {{"easy",0},
                 {"medium",2},
                 {"hard",1}}}
  };
};
