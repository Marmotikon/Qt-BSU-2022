#pragma once

#include <QString>

#include "map"

namespace constants {

const std::map<QString, std::map<QString, QString>> kFilenames{
    {"pick_an_option",{{"easy",":tasks/PickAnOption_easy_tasks.txt"},
                       {"medium",":tasks/PickAnOption_medium_tasks.txt"},
                       {"hard",":tasks/PickAnOption_hard_tasks.txt"}}},
    {"input_answer", {{"easy",":tasks/InputAnswer_easy_tasks.txt"},
                      {"medium",":tasks/InputAnswer_medium_tasks.txt"},
                      {"hard",":tasks/InputAnswer_hard_tasks.txt"}}},
    {"audio", {{"easy",":tasks/Audio_easy_tasks.txt"},
               {"medium",":tasks/Audio_medium_tasks.txt"},
               {"hard",":tasks/Audio_hard_tasks.txt"}}}
};
const std::map<QString, std::map<QString, int>> kWinPoints{
    {"pick_an_option",{{"easy",1},
                       {"medium",2},
                       {"hard",3}}},
    {"input_answer", {{"easy",3},
                      {"medium",4},
                      {"hard",5}}},
    {"audio", {{"easy",4},
               {"medium",5},
               {"hard",6}}}
};
const std::map<QString, int> kCorrectNeeded{
    {"easy",10},
    {"medium",8},
    {"hard",6}
};
const std::map<QString, int> kAttempts{
    {"easy",3},
    {"medium",2},
    {"hard",1}
};

}  // namespace constants
