#pragma once

#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

class MainPageWidget : public QWidget {
 Q_OBJECT
 public:
  MainPageWidget();

 signals:
  void PickAnOptionButtonPressed();
  void InputAnswerButtonPressed();
  void AudioButtonPressed();
  void MixedButtonPressed();

 private:
  QGridLayout* layout_;
  QPushButton* pick_an_option_button_;
  QPushButton* input_answer_button_;
  QPushButton* audio_button_;
  QPushButton* mixed_button_;
};
