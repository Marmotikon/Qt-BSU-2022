#include "main_window.h"

const int MainWindow::kMaxTicketsCount = 100;
const int MainWindow::kMinWindowHeight = 300;
const int MainWindow::kMinWindowWidth = 400;

MainWindow::MainWindow() :
    QMainWindow(nullptr),
    main_layout_(new QGridLayout()),
    main_widget_(new QWidget(this)),

    tickets_count_(new QSpinBox(main_widget_)),
    tickets_view_(new QListWidget(main_widget_)),

    ticket_number_(new QLabel("Ticket number 1", main_widget_)),
    ticket_name_(new QLineEdit("Paragraph 1", main_widget_)),
    ticket_description_(new QTextEdit("Something about numbers idk...")),
    ticket_status_(new QComboBox(main_widget_)),

    next_ticket_(new QPushButton("Next ticket", main_widget_)),
    prev_ticket_(new QPushButton("Previous ticket", main_widget_)),

    total_progress_(new QProgressBar(main_widget_)),
    green_progress_(new QProgressBar(main_widget_)) {

  resize(kMinWindowWidth * 2, kMinWindowHeight * 2);
  setMinimumSize(kMinWindowWidth, kMinWindowHeight);
  setWindowTitle("Mathematical analysis tickets");
  ManageLayout();
  previous_tickets_.push(tickets_view_->item(0));
  NewItemSelected(tickets_view_->item(0));
}

void MainWindow::ManageLayout() {
  main_layout_->addWidget(tickets_count_, 0, 0);
  main_layout_->addWidget(tickets_view_, 1, 0, 3, 1);

  main_layout_->addWidget(ticket_number_, 0, 1);
  main_layout_->addWidget(ticket_name_, 1, 1);
  main_layout_->addWidget(ticket_description_, 2, 1);

  main_layout_->addWidget(ticket_status_, 3, 1);
  ticket_status_->addItem("I see this ticket the first time lol");
  ticket_status_->addItem("I know, but I don't know, what I know");
  ticket_status_->addItem("Seems like I have wrote this ticket");

  main_layout_->addWidget(prev_ticket_, 4, 0);
  main_layout_->addWidget(next_ticket_, 4, 1);

  main_layout_->addWidget(green_progress_, 5, 0, 1, 2);
  main_layout_->addWidget(total_progress_, 6, 0, 1, 2);

  main_layout_->setColumnStretch(0, 1);
  main_layout_->setColumnStretch(1, 1);
  main_layout_->setColumnMinimumWidth(0, kMinWindowWidth/4);
  main_layout_->setColumnMinimumWidth(1, kMinWindowWidth/2);

  main_layout_->setRowStretch(0, 1);
  main_layout_->setRowStretch(1, 4);
  main_layout_->setRowStretch(2, 4);
  main_layout_->setRowStretch(3, 1);
  main_layout_->setRowStretch(4, 1);
  main_layout_->setRowStretch(5, 1);
  main_layout_->setRowStretch(6, 1);
  main_layout_->setRowMinimumHeight(0, kMinWindowWidth/12);
  main_layout_->setRowMinimumHeight(1, kMinWindowWidth/3);
  main_layout_->setRowMinimumHeight(2, kMinWindowHeight/3);
  main_layout_->setRowMinimumHeight(3, kMinWindowHeight/12);
  main_layout_->setRowMinimumHeight(4, kMinWindowHeight/12);
  main_layout_->setRowMinimumHeight(5, kMinWindowHeight/12);
  main_layout_->setRowMinimumHeight(6, kMinWindowHeight/12);

  main_widget_->setLayout(main_layout_);
  setCentralWidget(main_widget_);
  UpdateProgressBars();

  connect(tickets_count_, &QSpinBox::valueChanged, tickets_view_, [&] {
    ResetView();
  });  // todo
  // double click on item from tickets_view_
  connect(tickets_view_, &QListWidget::itemDoubleClicked, tickets_view_, [&](QListWidgetItem* item) {

    if (item->background() == Qt::green) {
      AddTicket(item);
      item->setBackground(Qt::yellow);
      ticket_status_->setCurrentIndex(1);
    } else {
      if (item->background() == Qt::gray) {
        gray_tickets_--;
      }
      EraseTicket(item);
      item->setBackground(Qt::green);
      ticket_status_->setCurrentIndex(2);
    }
    green_progress_->setValue(tickets_count_->value() - gray_yellow_tickets_.size());
    total_progress_->setValue(tickets_count_->value() - gray_tickets_);
  });
  // click on item from tickets_view_
  connect(tickets_view_, &QListWidget::itemClicked, tickets_view_, [&](QListWidgetItem* item) {
    previous_tickets_.push(item);
    NewItemSelected(item);
  });
  // new item selected in ticket_status_
  connect(ticket_status_, &QComboBox::activated, ticket_status_, [&](int index) {
    QListWidgetItem* selected_item(*tickets_view_->selectedItems().begin());
    if (selected_item->background() == Qt::gray ||
        selected_item->background() == Qt::yellow) {
      if (selected_item->background() == Qt::gray) {
        gray_tickets_--;
      }
      EraseTicket(selected_item);
    }

    if (index == 0) {
      selected_item->setBackground(Qt::gray);
      gray_tickets_++;
      AddTicket(selected_item);
    } else if (index == 1) {
      selected_item->setBackground(Qt::yellow);
      AddTicket(selected_item);
    } else {
      selected_item->setBackground(Qt::green);
    }

    green_progress_->setValue(tickets_count_->value() - gray_yellow_tickets_.size());
    total_progress_->setValue(tickets_count_->value() - gray_tickets_);
  });
  // Enter pressed
  connect(ticket_name_, &QLineEdit::returnPressed, ticket_name_, [&] {
    if (!ticket_name_->text().isEmpty()) {
      ticket_name_->setText(ticket_name_->text());

      QListWidgetItem* selected_item(*tickets_view_->selectedItems().begin());
      selected_item->setText(ticket_name_->text());
    }
  });
  // next question pressed
  connect(next_ticket_, &QPushButton::pressed, tickets_view_, [&] {
    if (gray_yellow_tickets_.size() > 0) {
      QListWidgetItem* new_item = GetNewItem();
      tickets_view_->setCurrentItem(new_item);
      previous_tickets_.push(new_item);
      NewItemSelected(new_item);
    }
  });
  // previous qusetion pressed
  connect(prev_ticket_, &QPushButton::pressed, tickets_view_, [&] {
    if (previous_tickets_.size() > 1) {
      previous_tickets_.pop();
      QListWidgetItem* new_item = previous_tickets_.top();
      tickets_view_->setCurrentItem(new_item);
      NewItemSelected(new_item);
    }
  });

  tickets_count_->setPrefix("Всего билетов: ");
  tickets_count_->setMaximum(kMaxTicketsCount);
  tickets_count_->setMinimum(1);
  tickets_count_->setValue(25);


}

int MainWindow::GetWidgetItemIndex(QListWidgetItem* item) {
  QListWidget* list_widget = item->listWidget();

  for (int i = 0; i < list_widget->count(); i++) {
    if (list_widget->item(i) == item) {
      return i;
    }
  }
  return -1;
}

void MainWindow::ResetView() {
  tickets_view_->clear();
  gray_yellow_tickets_.clear();
  while (previous_tickets_.size() > 0) {
    previous_tickets_.pop();
  }
  green_progress_->setValue(0);
  green_progress_->setMaximum(tickets_count_->value());
  total_progress_->setValue(0);
  total_progress_->setMaximum(tickets_count_->value());
  gray_tickets_ = tickets_count_->value();

  for (int i = 1; i <= tickets_count_->value(); i++) {
    std::string ticket_id = "Ticket number " + std::to_string(i);
    tickets_view_->addItem(ticket_id.c_str());

    tickets_view_->item(i - 1)->setBackground(Qt::gray);
    gray_yellow_tickets_.push_back(tickets_view_->item(i - 1));
  }
}

void MainWindow::UpdateProgressBars() {
  green_progress_->setStyleSheet("QProgressBar::chunk {\n"
                                 "    background-color: #00ff00;\n"
                                 " }"
                                 "QProgressBar {"
                                 "    text-align: center;"
                                 "    border: 1px solid gray;"
                                 "}");
  green_progress_->setFormat("Хорошо повторенное");
  green_progress_->setMinimum(0);
  green_progress_->setVisible(true);
  green_progress_->setMinimumHeight(kMinWindowHeight / 12);
  green_progress_->setMaximumHeight(kMinWindowHeight / 12);

  total_progress_->setStyleSheet("QProgressBar::chunk {\n"
                                 "    background-color: #ffff00;\n"
                                 " }"
                                 "QProgressBar {"
                                 "    text-align: center;"
                                 "    border: 1px solid gray;"
                                 "}");
  total_progress_->setFormat("Повторенное");
  total_progress_->setMinimum(0);
  total_progress_->setVisible(true);
  total_progress_->setMinimumHeight(kMinWindowHeight / 12);
  total_progress_->setMaximumHeight(kMinWindowHeight / 12);
}

void MainWindow::NewItemSelected(QListWidgetItem* item) {
  std::string item_number_str = std::to_string(GetWidgetItemIndex(item) + 1);
  std::string new_number = "Ticket number " + item_number_str;
  ticket_number_->setText(new_number.c_str());
  item_number_str = "Paragraph" + item_number_str;
  ticket_name_->setText(QString(item_number_str.c_str()));
  ticket_name_->setText(item->text());

  if (item->background() == Qt::gray) {
    ticket_status_->setCurrentIndex(0);
  } else if (item->background() == Qt::yellow) {
    ticket_status_->setCurrentIndex(1);
  } else {
    ticket_status_->setCurrentIndex(2);
  }
}

void MainWindow::AddTicket(QListWidgetItem* item) {
  gray_yellow_tickets_.push_back(item);
}

void MainWindow::EraseTicket(QListWidgetItem* item) {
  for (auto& ticket : gray_yellow_tickets_) {
    if (ticket == item) {
      std::swap(ticket, gray_yellow_tickets_.back());
      gray_yellow_tickets_.pop_back();
      return;
    }
  }
}

QListWidgetItem* MainWindow::GetNewItem() {
  std::mt19937 random_generator(std::chrono::system_clock().now().time_since_epoch().count());
  int new_id = (random_generator() % gray_yellow_tickets_.size());

  if (gray_yellow_tickets_.size() > 1) {
    QListWidgetItem* selected_item(*tickets_view_->selectedItems().begin());
    while (gray_yellow_tickets_[new_id] == selected_item) {
      new_id = (random_generator() % gray_yellow_tickets_.size());
    }
  }
  return gray_yellow_tickets_[new_id];
}

// #include "main_window.h"
//
// MainWindow::MainWindow() : main_layout_(new QGridLayout()),
//                            // main_widget_(new QWidget(this)),
//                            tickets_count_(new QSpinBox(this)),
//                            tickets_view_(new QListWidget(this)),
//                            // tickets_view_(new QListWidget(this)),
//                            ticket_number_(new QLabel("Ticket number 1", this)),
//                            ticket_name_(new QLineEdit("Ticket 1", this)),
//                            ticket_description_(new QLineEdit("Bla Bla Bla", this)),
//                            next_ticket_(new QPushButton("Next ticket", this)),
//                            prev_ticket_(new QPushButton("Previous ticket", this)),
//                            green_progress_(new QProgressBar(this)),
//                            total_progress_(new QProgressBar(this)),
//                            ticket_status_(new QComboBox(this)) {
//
//     // question_view_(new QGroupBox("Описание билета", main_widget_)),
//                            // question_view_layout_(new QVBoxLayout()),
//                            // ticket_number_(new QLabel("Номер билета: 1", question_view_)),
//                            // ticket_name_(new QLabel("Назавние билета: Билет №1", question_view_)),
//                            // ticket_name_(new QLineEdit("Билет №1", question_view_)),
//                            // next_ticket_(new QPushButton("Следующий билет", main_widget_)),
//                            // prev_ticket_(new QPushButton("Предыдущий билет", main_widget_)),
//
//   // resize(kMinWindowWidth, kMinWindowHeight);
//   // setMinimumSize(kMinWindowWidth, kMinWindowHeight);
//   // setWindowTitle("Repeating tickets");
//
//   ManageLayout();
// }
//
// void MainWindow::ManageLayout() {
//   main_layout_->addWidget(tickets_count_, 0, 0);
//   main_layout_->addWidget(tickets_view_, 1, 0, 3, 1);
//
//   main_layout_->addWidget(ticket_number_, 0, 1);
//   main_layout_->addWidget(ticket_name_, 1, 1);
//   main_layout_->addWidget(ticket_description_, 2, 1);
//   main_layout_->addWidget(ticket_status_, 3, 1);
//
//   main_layout_->addWidget(prev_ticket_, 3, 0);
//   main_layout_->addWidget(next_ticket_, 3, 1);
//   main_layout_->addWidget(green_progress_, 4, 0, 1, 2);
//   main_layout_->addWidget(total_progress_, 5, 0, 1, 2);
//
//   // UpdateProgressBars();
//   // ManageQuestionViewLayout();
//   //
//   // // quantity of tickets changed
//   // connect(tickets_count_, &QSpinBox::valueChanged, tickets_view_, [&] {
//   //   ResetView();
//   // });
//   // // double click on item from tickets_view_
//   // connect(tickets_view_, &QListWidget::itemDoubleClicked, tickets_view_, [&](QListWidgetItem* item) {
//   //   if (item->background() == Qt::green) {
//   //     AddTicket(item);
//   //     item->setBackground(Qt::yellow);
//   //     ticket_status_->setCurrentIndex(1);
//   //   } else {
//   //     if (item->background() == Qt::gray) {
//   //       gray_tickets_--;
//   //     }
//   //     EraseTicket(item);
//   //     item->setBackground(Qt::green);
//   //     ticket_status_->setCurrentIndex(2);
//   //   }
//   //   green_progress_->setValue(tickets_count_->value() - gray_yellow_tickets_.size());
//   //   total_progress_->setValue(tickets_count_->value() - gray_tickets_);
//   // });
//   // // click on item from tickets_view_
//   // connect(tickets_view_, &QListWidget::itemClicked, question_view_, [&](QListWidgetItem* item) {
//   //   previous_tickets_.push(item);
//   //   NewItemSelected(item);
//   // });
//   // // new item selected in ticket_status_
//   // connect(ticket_status_, &QComboBox::activated, ticket_status_, [&](int index) {
//   //   QListWidgetItem* selected_item(*tickets_view_->selectedItems().begin());
//   //   if (selected_item->background() == Qt::gray ||
//   //       selected_item->background() == Qt::yellow) {
//   //     if (selected_item->background() == Qt::gray) {
//   //       gray_tickets_--;
//   //     }
//   //     EraseTicket(selected_item);
//   //   }
//   //
//   //   if (index == 0) {
//   //     selected_item->setBackground(Qt::gray);
//   //     gray_tickets_++;
//   //     AddTicket(selected_item);
//   //   } else if (index == 1) {
//   //     selected_item->setBackground(Qt::yellow);
//   //     AddTicket(selected_item);
//   //   } else {
//   //     selected_item->setBackground(Qt::green);
//   //   }
//   //
//   //   green_progress_->setValue(tickets_count_->value() - gray_yellow_tickets_.size());
//   //   total_progress_->setValue(tickets_count_->value() - gray_tickets_);
//   // });
//   // // Enter pressed
//   // connect(ticket_name_, &QLineEdit::returnPressed, ticket_name_, [&] {
//   //   if (!ticket_name_->text().isEmpty()) {
//   //     ticket_name_->setText(QString("Название билета: ") + ticket_name_->text());
//   //
//   //     QListWidgetItem* selected_item(*tickets_view_->selectedItems().begin());
//   //     selected_item->setText(ticket_name_->text());
//   //   }
//   // });
//   // // next question pressed
//   // connect(next_ticket_, &QPushButton::pressed, tickets_view_, [&] {
//   //   if (gray_yellow_tickets_.size() > 0) {
//   //     QListWidgetItem* new_item = GetNewItem();
//   //     tickets_view_->setCurrentItem(new_item);
//   //     previous_tickets_.push(new_item);
//   //     NewItemSelected(new_item);
//   //   }
//   // });
//   // // previous qusetion pressed
//   // connect(prev_ticket_, &QPushButton::pressed, tickets_view_, [&] {
//   //   if (previous_tickets_.size() > 1) {
//   //     previous_tickets_.pop();
//   //     QListWidgetItem* new_item = previous_tickets_.top();
//   //     tickets_view_->setCurrentItem(new_item);
//   //     NewItemSelected(new_item);
//   //   }
//   // });
//   //
//   // tickets_count_->setPrefix("Всего билетов: ");
//   // tickets_count_->setMaximum(kMaxTicketsCount);
//   // tickets_count_->setMinimum(1);
//   // tickets_count_->setValue(10);
//   //
//   main_layout_->setColumnStretch(0, 1);
//   // main_layout_->setColumnMinimumWidth(0, kMinWindowHeight/4);
//   main_layout_->setColumnStretch(1, 1);
//   // main_layout_->setColumnMinimumWidth(1, kMinWindowHeight/2);
//   // main_layout_->setColumnMinimumWidth(2, kMinWindowHeight/4);
//
//   // main_layout_->setRowStretch(0, 2);
//   // main_layout_->setRowMinimumHeight(0, kMinWindowWidth/2);
//   // main_layout_->setRowStretch(1, 1);
//   // main_layout_->setRowMinimumHeight(1, kMinWindowWidth/4);
//   // main_layout_->setRowStretch(2, 1);
//   // main_layout_->setRowMinimumHeight(2, kMinWindowWidth/4);
//
//   this->setLayout(main_layout_);
//   setCentralWidget(this);
// }
