#include "main_page_widget.h"

MainPageWidget::MainPageWidget() :
    layout_(new QGridLayout()),
    pick_an_option_button_(new QPushButton("Выбери правильный вариант", this)),
    input_answer_button_(new QPushButton("Введи ответ", this)),
    audio_button_(new QPushButton("Аудио", this)),
    mixed_button_(new QPushButton("Рандом", this)) {
  layout_->addWidget(pick_an_option_button_, 0, 1);
  layout_->addWidget(input_answer_button_, 1, 1);
  layout_->addWidget(audio_button_, 2, 1);
  layout_->addWidget(mixed_button_, 3, 1);


  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 8);
  layout_->setColumnStretch(2, 1);

  setLayout(layout_);

  connect(pick_an_option_button_, &QPushButton::pressed, this,
          &MainPageWidget::PickAnOptionButtonPressed);
  connect(input_answer_button_, &QPushButton::pressed, this,
          &MainPageWidget::InputAnswerButtonPressed);
  connect(audio_button_, &QPushButton::pressed, this,
          &MainPageWidget::AudioButtonPressed);
  connect(mixed_button_, &QPushButton::pressed, this,
          &MainPageWidget::MixedButtonPressed);
}
//
// QPushButton* MainPageWidget::GetPickAnOptionButton() {
//   return pick_an_option_button_;
// }
//
// QPushButton* MainPageWidget::GetAudioButton() {
//   return audio_button_;
// }
//
// QPushButton* MainPageWidget::GetInputAnswerButton() {
//   return input_answer_button_;
// }
//
// QPushButton* MainPageWidget::GetMixedButton() {
//   return mixed_button_;
// }
