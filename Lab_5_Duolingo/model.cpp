#include "model.h"

void Model::SetDifficultyMode(QString value) {
  settings_->setValue("difficulty", value);
}

QString Model::GetDifficultyMode() {
  return settings_->value("difficulty","easy").toString();
}

void Model::SetSoundMode(QString value) {
  settings_->setValue("sound", value);
}

QString Model::GetSoundMode() {
  return settings_->value("sound","on").toString();
}

void Model::AddProgressPoints(int value) {
  settings_->setValue("progress", value);
}

int Model::GetProgressPoints() {
  return settings_->value("progress", 0).toInt();
}

Model::Model() :
    settings_(new QSettings("2DaysBeforeDeadlineCorp", "Dualingo"))
    {

}
void Model::ResetProgressPoints() {
  settings_->setValue("progress", 0);
}

