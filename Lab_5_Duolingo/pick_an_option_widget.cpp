#include "pick_an_option_widget.h"

PickAnOptionWidget::PickAnOptionWidget() :
    layout_(new QGridLayout(/*pick_an_option_widget_*/)),
    task_condition_(new QLabel("task condition")),
    task_text_(new QLabel("task text")),
    variants_(new QButtonGroup(this)),
    check_answer_button_(new QPushButton("check", this)),
    next_question_button_(new QPushButton("next", this)),
    go_to_main_page_button_(new QPushButton("main page", this)) {
  layout_->addWidget(task_condition_, 0, 1);
  layout_->addWidget(task_text_, 1, 1);
  // layout_->addWidget(variants_, 1, 1);
  layout_->addWidget(next_question_button_, 3, 1);
  layout_->addWidget(go_to_main_page_button_, 4, 1);
  layout_->addWidget(check_answer_button_, 5, 1);


  setLayout(layout_);

  connect(check_answer_button_, &QPushButton::pressed, this,
          &PickAnOptionWidget::CheckAnswerButtonPressed);
  connect(next_question_button_, &QPushButton::pressed, this,
          &PickAnOptionWidget::NextQuestionButtonPressed);
  connect(go_to_main_page_button_, &QPushButton::pressed, this,
          &PickAnOptionWidget::GoToMainPageButtonPressed);
}

void PickAnOptionWidget::SetTaskCondition(QString string) {
  task_condition_->setText(string);
}

void PickAnOptionWidget::SetTaskText(QString string) {
  task_text_->setText(string);
}

void PickAnOptionWidget::SetVariants(int count, std::vector<QString> strings) {
  layout_->addWidget(task_condition_, 0, 1, 1, count);
  layout_->addWidget(task_text_, 1, 1, 1, count);
  // layout_->addWidget(variants_, 1, 1);
  layout_->addWidget(next_question_button_, 3, 1, 1, count);
  layout_->addWidget(go_to_main_page_button_, 4, 1, 1, count);
  layout_->addWidget(check_answer_button_, 5, 1, 1, count);
  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(count + 1, 1);
  for (int i = 0; i < count; i++) {
    auto* button = new QPushButton(strings.at(i));
    variants_->addButton(button);
    layout_->addWidget(button, 2, i + 1);
    layout_->setColumnStretch(i + 1, 8 / count);
  }
  variants_->setExclusive(true);
}
