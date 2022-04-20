#include "audio_widget.h"

AudioWidget::AudioWidget() :
    layout_(new QGridLayout()),
    task_text_(new QLabel("Введите услышанное слово")),
    task_condition_(new QLabel("...")),
    answer_(new QLineEdit(this)),
    speaker_(new QPushButton("Послушать", this)),
    check_answer_button_(new QPushButton("Проверить", this)),
    next_question_button_(new QPushButton("Следующий", this)),
    go_to_main_page_button_(new QPushButton("На главную", this)),
    sound_effect_(new QSoundEffect(this)) {
  layout_->addWidget(task_text_, 0, 1);
  layout_->addWidget(task_condition_, 1, 1);
  layout_->addWidget(speaker_, 2, 1);
  layout_->addWidget(answer_, 3, 1);
  layout_->addWidget(check_answer_button_, 4, 1);
  layout_->addWidget(next_question_button_, 5, 1);
  layout_->addWidget(go_to_main_page_button_, 6, 1);

  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 2);
  layout_->setRowStretch(2, 4);
  layout_->setRowStretch(3, 4);
  layout_->setRowStretch(4, 2);
  layout_->setRowStretch(5, 2);
  layout_->setRowStretch(6, 2);


  setLayout(layout_);

  connect(check_answer_button_, &QPushButton::pressed, this,
          &AudioWidget::CheckAnswerButtonPressed);
  connect(next_question_button_, &QPushButton::pressed, this,
          &AudioWidget::NextQuestionButtonPressed);
  connect(go_to_main_page_button_, &QPushButton::pressed, this,
          &AudioWidget::GoToMainPageButtonPressed);

  connect(speaker_, &QPushButton::pressed, this, [this] {
    sound_effect_->play();
  });
  sound_effect_->setLoopCount(1);
  sound_effect_->setVolume(1.0f);
}

void AudioWidget::SetTaskCondition(const QString& string) {
  task_condition_->setText(string);
}

void AudioWidget::UpdateForNextTask() {
  answer_->clear();
  next_question_button_->setEnabled(false);
  check_answer_button_->setEnabled(true);
}

void AudioWidget::UpdateAfterCheck() {
  next_question_button_->setEnabled(true);
  check_answer_button_->setEnabled(false);
}

QString AudioWidget::GetAnswer() {
  return answer_->text();
}

void AudioWidget::SetVariants(const std::vector<QString>& strings) {
  sound_effect_->setSource(QUrl(strings.at(0)));
}
