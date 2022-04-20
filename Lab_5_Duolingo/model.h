#pragma once

#include <vector>
#include <QString>
#include <QSettings>
#include <QFile>
#include <fstream>
#include "abstract_controller.h"

class Model : public QObject {
  Q_OBJECT
 public:
  Model(AbstractController* controller);
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
  struct PickAnOption {
    QString easy_filename_{":tasks/PickAnOption_easy_tasks.txt"};
    QString medium_filename_{":tasks/PickAnOption_medium_tasks.txt"};
    QString hard_filename_{":tasks/PickAnOption_hard_tasks.txt"};
    std::vector<std::vector<QString>> easy_tasks;
    std::vector<std::vector<QString>> medium_tasks;
    std::vector<std::vector<QString>> hard_tasks;
    int easy_next_index{0};
    int medium_next_index{0};
    int hard_next_index{0};
  };
  AbstractController* controller_;
  PickAnOption pick_an_option_;
  QSettings* settings_;



};
