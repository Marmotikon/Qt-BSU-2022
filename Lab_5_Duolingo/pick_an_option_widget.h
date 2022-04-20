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

  void SetTaskCondition(QString string);
  void SetWinPoints(int win_points);
  void SetTaskText(QString string);
  void SetVariants(std::vector<QString> strings);
  void SetRightAnswer(int right_answer);

  int GetWinPoints() const;
  bool CheckAnswer() const;

  void UpdateView();
  void BlockButtons();

 signals:
  void CheckAnswerButtonPressed();
  void NextQuestionButtonPressed();
  void GoToMainPageButtonPressed();

 private:
  QGridLayout* layout_;
  QLabel* task_condition_;
  QLabel* task_text_;
  QButtonGroup* variants_;
  QPushButton* check_answer_button_;
  QPushButton* next_question_button_;
  QPushButton* go_to_main_page_button_;

  int win_points_{1};
  int right_answer_;
  int variants_count_;
};
