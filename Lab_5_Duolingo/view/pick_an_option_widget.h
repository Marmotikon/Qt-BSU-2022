#pragma once

#include <QButtonGroup>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class PickAnOptionWidget : public QWidget {
  Q_OBJECT
 public:
  PickAnOptionWidget();

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
  QPushButton* check_answer_button_;
  QPushButton* next_question_button_;
  QPushButton* go_to_main_page_button_;

  QButtonGroup* variants_;
  int variants_count_;
};
