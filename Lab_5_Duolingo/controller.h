#pragma once

#include <memory>

#include <QObject>

#include "abstract_controller.h"
#include "main_window.h"
#include "model.h"

class Controller : public AbstractController {
  Q_OBJECT
 public:
  Controller();

  void ManageDifficultyMenu(QMenu* difficulty_menu) override;
  void ManageSoundMenu(QMenu* sound_menu) override;
  void ManageResetProgressAction(QAction* reset_progress_action) override;

  void ShowResetProgressDialog() override;


  // virtual void SetDifficultyMode(DifficultyMode new_mode);
  // virtual DifficultyMode GetDifficulty() const;
  //
  // virtual void SetSoundMode(SoundMode new_mode);
  // virtual SoundMode GetSound() const;
  //
  // virtual void SetWindowMode(WindowMode new_mode);
  // virtual WindowMode GetWindow() const;

 private:
  void RefreshView();

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<MainWindow> view_;

  // DifficultyMode difficulty_mode_{DifficultyMode::easy};
  // SoundMode sound_mode_{SoundM

  // DifficultyMode difficulty_mode_{DifficultyMode::easy};
  // SoundMode sound_mode_{SoundMode::on};
  // WindowMode window_mode_{WindowMode::main_menu};
};
