#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class InputAnswerWidget : public QWidget {
 Q_OBJECT
 public:
  InputAnswerWidget();
  void SetTaskCondition(const QString& string);

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
  QPushButton* check_answer_button_;
  QPushButton* next_question_button_;
  QPushButton* go_to_main_page_button_;

  QLineEdit* answer_;
};
