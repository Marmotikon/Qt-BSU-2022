#pragma once

#include <QObject>
#include <QMenu>
#include <QAction>

class AbstractController : public QObject {
  Q_OBJECT
 public:
  virtual void ManageDifficultyMenu(QMenu* difficulty_menu) = 0;
  virtual void ManageSoundMenu(QMenu* sound_menu) = 0;
  virtual void ManageResetProgressAction(QAction* reset_progress_action) = 0;
  virtual void ShowResetProgressDialog() = 0;
 //  enum class DifficultyMode {
 //    easy,
 //    medium,
 //    hard
 //  };
 //
 //  enum class SoundMode {
 //    on,
 //    off
 //  };
 //
 //  enum class WindowMode {
 //    main_menu,
 //    pick_an_option,
 //    input_answer,
 //    audio,
 //    mixed
 //  };

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
