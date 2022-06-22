#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>

class CustomWidget : public QWidget {
 Q_OBJECT
 public:
  // PickAnOptionWidget();

  void SetTaskCondition(const QString& string);
  void SetVariants(const std::vector<QString>& variant_texts);

  void UpdateView();
  void BlockButtons();
  QString GetChosenVariant();
 signals:
  void CheckAnswerButtonPressed();
  void NextQuestionButtonPressed();
  void GoToMainPageButtonPressed();

 private:
  QGridLayout* layout_;
  QLabel* task_text_;
  QLabel* task_condition_;
  QButtonGroup* variants_;
  QPushButton* check_answer_button_;
  QPushButton* next_question_button_;
  QPushButton* go_to_main_page_button_;

  int variants_count_;
};
