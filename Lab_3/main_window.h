#pragma once

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>

#include <chrono>
#include <random>
#include <stack>
#include <string>
#include <vector>

class MainWindow : public QMainWindow {
 Q_OBJECT
 public:
  MainWindow();
  static int GetWidgetItemIndex(QListWidgetItem* item);

 private:
  void ManageLayout();
  void ResetView();
  void UpdateProgressBars();

  void NewItemSelected(QListWidgetItem*);
  void AddTicket(QListWidgetItem*);
  void EraseTicket(QListWidgetItem*);
  QListWidgetItem* GetNewItem();

 private:
  static const int kMaxTicketsCount;
  static const int kMinWindowHeight;
  static const int kMinWindowWidth;

  QGridLayout* main_layout_;
  QWidget* main_widget_;

  QSpinBox* tickets_count_;
  QListWidget* tickets_view_;

  QLabel* ticket_number_;
  QLineEdit* ticket_name_;
  QTextEdit* ticket_description_;
  QComboBox* ticket_status_;

  QPushButton* next_ticket_;
  QPushButton* prev_ticket_;

  QProgressBar* total_progress_;
  QProgressBar* green_progress_;

  std::vector<QListWidgetItem*> gray_yellow_tickets_;
  int gray_tickets_;
  std::stack<QListWidgetItem*> previous_tickets_;
};
