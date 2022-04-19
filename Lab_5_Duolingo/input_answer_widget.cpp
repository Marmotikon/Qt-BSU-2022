#include "input_answer_widget.h"

InputAnswerWidget::InputAnswerWidget() :
    layout_(new QGridLayout()),
    task_condition_(new QLabel("task condition")),
    task_text_(new QLabel("task text")),
    anser_(new QLineEdit(this)),
    next_question_(new QPushButton("next", this)),
    go_to_main_page_(new QPushButton("main page", this)) {
  layout_->addWidget(task_condition_, 0, 1);
  layout_->addWidget(task_text_, 1, 1);
  layout_->addWidget(anser_, 2, 1);
  layout_->addWidget(next_question_, 3, 1);
  layout_->addWidget(go_to_main_page_, 4, 1);

  // layout_->setColumnStretch(0, 1);
  // layout_->setColumnStretch(1, 8);
  // layout_->setColumnStretch(2, 1);

  setLayout(layout_);
}
