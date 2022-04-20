#include "custom_widget.h"

void CustomWidget::SetTaskCondition(const QString& string) {
  task_condition_->setText(string);
}

// void CustomWidget::SetVariants(const std::vector<QString>& variant_texts) {
//   variants_count_ = variant_texts.size();
//
//   //delete previous buttons
//   for (auto button : variants_->buttons()) {
//     layout_->removeWidget(button);
//     variants_->removeButton(button);
//     delete button;
//   }
//
//   for (int i = 0; i < variants_count_; i++) {
//     auto* button = new QPushButton(variant_texts.at(i));
//     button->setCheckable(true);
//     variants_->addButton(button);
//     variants_->setId(button, i);
//     layout_->addWidget(button, 2, i + 1);
//   }
//   variants_->setExclusive(true);
// }

// void CustomWidget::UpdateForNextTask() {
//   layout_->removeWidget(task_text_);
//   layout_->addWidget(task_text_, 0, 1, 1, variants_count_);
//   layout_->removeWidget(task_text_);
//   layout_->addWidget(task_text_, 1, 1, 1, variants_count_);
//   layout_->removeWidget(check_answer_button_);
//   layout_->addWidget(check_answer_button_, 3, 1, 1, variants_count_);
//   layout_->removeWidget(next_question_button_);
//   layout_->addWidget(next_question_button_, 4, 1, 1, variants_count_);
//   layout_->removeWidget(go_to_main_page_button_);
//   layout_->addWidget(go_to_main_page_button_, 5, 1, 1, variants_count_);
//
//   check_answer_button_->setEnabled(true);
// }

// void CustomWidget::UpdateAfterCheck() {
//   for (auto button : variants_->buttons())
//     // if (variants_->id(button) != right_answer_) {
//     button->setEnabled(false);
//   // }
//   // variants_->button(right_answer_)->setCheckable(false);
//   check_answer_button_->setEnabled(false);
// }

// QString CustomWidget::GetAnswer() {
//   return variants_->button(variants_->checkedId())->text();
// }
