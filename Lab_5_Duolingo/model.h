#pragma once

#include <vector>
#include <QString>
#include <QSettings>
#include <QFile>
#include <fstream>

class Model : public QObject {
  Q_OBJECT
 public:
  Model();
  // const QString& Element(size_t i) const { return queue_[i]; }
  // size_t Size() const { return queue_.size(); }
  // void Pop() { queue_.erase(queue_.begin()); }
  // void Push(const QString& item) { queue_.push_back(item); }
  void SetDifficultyMode(QString value);
  QString GetDifficultyMode();

  void SetSoundMode(QString value);
  QString GetSoundMode();

  void AddProgressPoints(int value);
  void ResetProgressPoints();
  QString GetProgressPoints();

  static void PickAnOptionLoadTasks(const QString& file_name,
      std::vector<std::vector<QString>>& tasks);
  std::vector<QString> GetPickAnOptionTask();

  // void IAEasyFileStart();
  // std::vector<QString> GetInputAnswerEasyTask();
  // void IAMediumFileStart();
  // std::vector<QString> GetInputAnswerMediumTask();
  // void IAHardFileStart();
  // std::vector<QString> GetInputAnswerHardTask();
  //
  // void AudioEasyFileStart();
  // std::vector<QString> GetAudioEasyTask();
  // void AudioMediumFileStart();
  // std::vector<QString> GetAudioMediumTask();
  // void AudioHardFileStart();
  // std::vector<QString> GetAudioHardTask();

 private:
  QSettings* settings_;

  QString pao_easy_filename_{":PickAnOption_easy_tasks.txt"};
  QString pao_medium_filename_{":PickAnOption_medium_tasks.txt"};
  QString pao_hard_filename_{":PickAnOption_hard_tasks.txt"};
  std::vector<std::vector<QString>> pao_easy_tasks_;
  std::vector<std::vector<QString>> pao_medium_tasks_;
  std::vector<std::vector<QString>> pao_hard_tasks_;
  int pao_easy_next_task_index{0};
  int pao_medium_next_task_index{0};
  int pao_hard_next_task_index{0};
};
