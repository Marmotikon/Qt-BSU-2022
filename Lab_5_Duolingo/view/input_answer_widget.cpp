#include "input_answer_widget.h"

InputAnswerWidget::InputAnswerWidget() :
    layout_(new QGridLayout()),
    task_text_(new QLabel("Введите правильный ответ")),
    task_condition_(new QLabel("condition ...")),
    answer_(new QLineEdit(this)),
    check_answer_button_(new QPushButton("Проверить", this)),
    next_question_button_(new QPushButton("Следующий", this)),
    go_to_main_page_button_(new QPushButton("На главную", this)) {

  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 4);
  layout_->setRowStretch(2, 4);
  layout_->setRowStretch(3, 2);
  layout_->setRowStretch(4, 2);
  layout_->setRowStretch(5, 2);

  layout_->addWidget(task_text_, 0, 1);
  layout_->addWidget(task_condition_, 1, 1);
  layout_->addWidget(answer_, 2, 1);
  layout_->addWidget(check_answer_button_, 3, 1);
  layout_->addWidget(next_question_button_, 4, 1);
  layout_->addWidget(go_to_main_page_button_, 5, 1);

  setLayout(layout_);

  connect(check_answer_button_, &QPushButton::pressed, this,
          &InputAnswerWidget::CheckAnswerButtonPressed);
  connect(next_question_button_, &QPushButton::pressed, this,
          &InputAnswerWidget::NextQuestionButtonPressed);
  connect(go_to_main_page_button_, &QPushButton::pressed, this,
          &InputAnswerWidget::GoToMainPageButtonPressed);
}

void InputAnswerWidget::SetTaskCondition(const QString& string) {
  task_condition_->setText(string);
}

void InputAnswerWidget::UpdateForNextTask() {
  answer_->clear();
  next_question_button_->setEnabled(false);
  check_answer_button_->setEnabled(true);
}

void InputAnswerWidget::UpdateAfterCheck() {
  next_question_button_->setEnabled(true);
  check_answer_button_->setEnabled(false);
}

QString InputAnswerWidget::GetAnswer() {
  return answer_->text();
}
