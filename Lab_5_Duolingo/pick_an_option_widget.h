#pragma once

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>
#include <QGridLayout>
// #include <QTextBlock>

class PickAnOptionWidget : public QWidget {
 public:
  PickAnOptionWidget();

 private:
  QGridLayout* layout_;
  QLabel* task_condition_;
  QLabel* task_text_;
  QButtonGroup* variants_;
  QPushButton* next_question_;
  QPushButton* go_to_main_page_;
};
