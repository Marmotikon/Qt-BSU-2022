#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QSoundEffect>

class AudioWidget : public QWidget {
 Q_OBJECT
 public:
  AudioWidget();

  void SetTaskCondition(const QString& string);
  void SetVariants(const std::vector<QString>& strings);

  void UpdateForNextTask();
  void UpdateAfterCheck();
  QString GetAnswer();

 signals:
  void CheckAnswerButtonPressed();
  void NextQuestionButtonPressed();
  void GoToMainPageButtonPressed();

 private:
  QGridLayout* layout_;
  QLabel* task_text_;
  QLabel* task_condition_;
  QPushButton* speaker_;
  QSoundEffect* sound_effect_;
  QLineEdit* answer_;
  QPushButton* check_answer_button_;
  QPushButton* next_question_button_;
  QPushButton* go_to_main_page_button_;
};
