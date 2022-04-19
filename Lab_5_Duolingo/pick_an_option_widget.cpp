#include "pick_an_option_widget.h"

PickAnOptionWidget::PickAnOptionWidget() :
    layout_(new QGridLayout(/*pick_an_option_widget_*/)),
    task_condition_(new QLabel("task condition")),
    task_text_(new QLabel("task text")),
    variants_(new QButtonGroup(this)),
    next_question_(new QPushButton("next", this)),
    go_to_main_page_(new QPushButton("main page", this)) {
  layout_->addWidget(task_condition_, 0, 1);
  layout_->addWidget(task_text_, 1, 1);
  layout_->addWidget(next_question_, 2, 1);
  layout_->addWidget(go_to_main_page_, 3, 1);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 8);
  layout_->setColumnStretch(2, 1);

  setLayout(layout_);
}
