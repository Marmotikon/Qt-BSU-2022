#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class InputAnswerWidget : public QWidget {
 public:
  InputAnswerWidget();

 private:
  QGridLayout* layout_;
  QLabel* task_condition_;
  QLabel* task_text_;
  QLineEdit* anser_;
  QPushButton* next_question_;
  QPushButton* go_to_main_page_;
};
