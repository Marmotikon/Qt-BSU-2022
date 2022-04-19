#include "input_answer_widget.h"

InputAnswerWidget::InputAnswerWidget() :
    layout_(new QGridLayout()),
    task_condition_(new QLabel("task condition")),
    task_text_(new QLabel("task text")),
    answer_(new QLineEdit(this)),
    check_answer_button_(new QPushButton("check", this)),
    next_question_button_(new QPushButton("next", this)),
    go_to_main_page_button_(new QPushButton("main page", this)) {
  layout_->addWidget(task_condition_, 0, 1);
  layout_->addWidget(task_text_, 1, 1);
  layout_->addWidget(answer_, 2, 1);
  layout_->addWidget(next_question_button_, 3, 1);
  layout_->addWidget(go_to_main_page_button_, 4, 1);
  layout_->addWidget(check_answer_button_, 5, 1);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 8);
  layout_->setColumnStretch(2, 1);

  setLayout(layout_);

  connect(check_answer_button_, &QPushButton::pressed, this,
          &InputAnswerWidget::CheckAnswerButtonPressed);
  connect(next_question_button_, &QPushButton::pressed, this,
          &InputAnswerWidget::NextQuestionButtonPressed);
  connect(go_to_main_page_button_, &QPushButton::pressed, this,
          &InputAnswerWidget::GoToMainPageButtonPressed);
}
