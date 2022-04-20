#pragma once

#include <QString>
#include <QFile>
#include <QTextStream>

#include "constants.h"

class Task {
 public:
  void LoadTasks(const QString& file_name);
  QString GetCondition();
  std::vector<QString> GetVariants();
  void SwitchToNextTask();
  bool IsAnswerCorrect(const QString& answer);
  void SetTaskMode(const QString& mode);
  void SetDifficulty(const QString& difficulty);
  int GetCorrectNeeded();
  int GetWinPoints();

 private:
  std::vector<QString> conditions_;
  std::vector<std::vector<QString>> variants_;
  std::vector<QString> answers_;
  int tasks_count_;

  int current_task_index_{-1};

  QString mode_;
  QString difficulty_;
};
