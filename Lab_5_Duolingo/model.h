#pragma once

#include <vector>
#include <QString>
#include <QSettings>

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
  int GetProgressPoints();

  // QString GetTaskMode();

 private:
  QSettings* settings_;
};
