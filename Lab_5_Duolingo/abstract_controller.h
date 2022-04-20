#pragma once

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QPushButton>

class AbstractController : public QObject {
  Q_OBJECT
 public:
  virtual void ManageDifficultyMenu(QMenu* difficulty_menu) = 0;
  virtual void ManageSoundMenu(QMenu* sound_menu) = 0;
  virtual void ConnectResetProgressAction(QAction* reset_progress_action) = 0;
  virtual void ConnectExitButton(QPushButton* exit_button) = 0;

  virtual void ShowResetProgressDialog() = 0;
  virtual void ShowExitDialog() = 0;
  virtual void Win() = 0;
  virtual void Lose() = 0;

  virtual bool IsSoundOn() = 0;
  virtual QString GetProgressPoints() = 0;
 public:
  // AbstractController() = default;

  // virtual void SetDifficultyMode(DifficultyMode new_mode);
  // virtual DifficultyMode GetDifficulty() const { return DifficultyMode::easy; };
  //
  // virtual void SetSoundMode(SoundMode new_mode) { SoundMode d = new_mode; };
  // virtual SoundMode GetSound() const { return SoundMode::on; };
  //
  // virtual void SetWindowMode(WindowMode new_mode) { WindowMode d = new_mode; };
  // virtual WindowMode GetWindow() const { return WindowMode::main_menu; };

 private:
  // DifficultyMode difficulty_mode_{DifficultyMode::easy};
  // SoundMode sound_mode_{SoundMode::on};
  // WindowMode window_mode_{WindowMode::main_menu};
};
