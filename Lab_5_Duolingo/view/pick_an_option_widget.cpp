#include "pick_an_option_widget.h"

PickAnOptionWidget::PickAnOptionWidget() :
    layout_(new QGridLayout()),
    task_text_(new QLabel("Выберите правильный ответ")),
    task_condition_(new QLabel("condition...")),
    variants_(new QButtonGroup(this)),
    check_answer_button_(new QPushButton("Проверить", this)),
    next_question_button_(new QPushButton("Следующий", this)),
    go_to_main_page_button_(new QPushButton("На главную", this)) {

  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 4);
  layout_->setRowStretch(2, 4);
  layout_->setRowStretch(3, 2);
  layout_->setRowStretch(4, 2);
  layout_->setRowStretch(5, 2);
  setLayout(layout_);

  connect(check_answer_button_, &QPushButton::pressed, this,
          &PickAnOptionWidget::CheckAnswerButtonPressed);
  connect(next_question_button_, &QPushButton::pressed, this,
          &PickAnOptionWidget::NextQuestionButtonPressed);
  connect(go_to_main_page_button_, &QPushButton::pressed, this,
          &PickAnOptionWidget::GoToMainPageButtonPressed);
}

void PickAnOptionWidget::SetTaskCondition(const QString& string) {
  task_condition_->setText(string);
}

void PickAnOptionWidget::SetVariants(const std::vector<QString>& variant_texts) {
  variants_count_ = variant_texts.size();

  //delete previous buttons
  for (auto button : variants_->buttons()) {
    layout_->removeWidget(button);
    variants_->removeButton(button);
    delete button;
  }

  for (int i = 0; i < variants_count_; i++) {
    auto* button = new QPushButton(variant_texts.at(i));
    button->setCheckable(true);
    variants_->addButton(button);
    variants_->setId(button, i);
    layout_->addWidget(button, 2, i + 1);
  }
  variants_->setExclusive(true);
}

void PickAnOptionWidget::UpdateForNextTask() {
  layout_->removeWidget(task_text_);
  layout_->addWidget(task_text_, 0, 1, 1, variants_count_);
  layout_->removeWidget(task_condition_);
  layout_->addWidget(task_condition_, 1, 1, 1, variants_count_);
  layout_->removeWidget(check_answer_button_);
  layout_->addWidget(check_answer_button_, 3, 1, 1, variants_count_);
  layout_->removeWidget(next_question_button_);
  layout_->addWidget(next_question_button_, 4, 1, 1, variants_count_);
  layout_->removeWidget(go_to_main_page_button_);
  layout_->addWidget(go_to_main_page_button_, 5, 1, 1, variants_count_);

  next_question_button_->setEnabled(false);
  check_answer_button_->setEnabled(true);
}

void PickAnOptionWidget::UpdateAfterCheck() {
  for (auto button : variants_->buttons())
    // if (variants_->id(button) != right_answer_) {
      button->setEnabled(false);
    // }
  // variants_->button(right_answer_)->setCheckable(false);
  next_question_button_->setEnabled(true);
  check_answer_button_->setEnabled(false);
}

QString PickAnOptionWidget::GetAnswer() {
  return variants_->button(variants_->checkedId())->text();
}
