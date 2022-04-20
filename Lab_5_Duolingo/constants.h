#pragma once

#include <QString>

namespace constants {

//model constants
const QString pick_an_option_easy_filename{":tasks/PickAnOption_easy_tasks.txt"};
const QString pick_an_option_medium_filename{":tasks/PickAnOption_medium_tasks.txt"};
const QString pick_an_option_hard_filename{":tasks/PickAnOption_hard_tasks.txt"};

const int pick_an_option_easy_win_points{1};
const int pick_an_option_medium_win_points{2};
const int pick_an_option_hard_win_points{3};

const int easy_correct_needed{10};
const int medium_correct_needed{8};
const int hard_correct_needed{6};

const int pick_an_option_easy_attempts{3};
const int pick_an_option_medium_attempts{2};
const int pick_an_option_hard_attempts{1};

}  // namespace constants