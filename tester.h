// Header-only library for otus-algo homework testing
// Written by Sergey Tsynikin, 2020

#ifndef TESTER_H
#define TESTER_H

#include <string>
#include <iostream>
#include <fstream>
#include <experimental\filesystem>
#include <chrono>
#include <iomanip>
#include <list>
#include <tuple>

#include "itask.h"

namespace fs = std::experimental::filesystem;

using ClockType = std::chrono::steady_clock;

class Tester
{
protected:
//    ITask &Task;

    std::list<std::tuple<std::string, ITask*>> Tasks;

    std::string Path;
//    bool ShowExpects = true;
//    bool ShowActuals = true;
//    bool ShowTime = true;

    ITask *ActiveTask = nullptr;

//    size_t MaxTestCount = 20;

    void RunTests()
    {
        std::cout << std::setw(6) << "Test#" << std::setw(8) <<
                     "Status" << std::setw(22) << "Expected" << std::setw(22) << "Actual" << std::setw(14) << "Time, s" << std::endl;

        std::cout << std::boolalpha;

        for (size_t nr = 0;; ++nr)
        {
            std::string inFile  = Path + "\\test." + std::to_string(nr) + ".in";
            std::string outFile = Path + "\\test." + std::to_string(nr) + ".out";

            if ( !fs::exists(inFile) || !fs::exists(outFile) )
                break;

            std::cout << std::setw(6) << nr << ":" << std::endl;
            bool res_test = RunTest(inFile, outFile);
            std::cout << "Test passed: " << res_test << std::endl << std::endl;

        }
    }

    bool RunTest(const std::string &_inFile, const std::string &_outFile)
    {
        std::vector<std::string> data;
        std::string line;
        std::ifstream i_stream_in(_inFile);
        while (getline(i_stream_in, line))
            data.emplace_back(move(line));   // Уточнить можно ли повторно использовать line после move ?
//            data.emplace_back(line);

        std::vector<std::string> expects;
        std::ifstream i_stream_out(_outFile);
        while (getline(i_stream_out, line))
//            expects.emplace_back(line);
            expects.emplace_back(move(line));   // Уточнить можно ли повторно использовать line после move ?

//        if (ShowExpects)
//            std::cout << "expect = " << expect << std::endl;

        std::chrono::time_point<ClockType> TimeStart = ClockType::now();

        std::vector<std::string> actuals = ActiveTask->Run(data);

        std::chrono::time_point<ClockType> TimeEnd = ClockType::now();

        double Time = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count();
        Time /= 1.0e9;

//        if (ShowTime)
//            std::cout << "Time, s = " << Time << std::endl;
//        if (ShowActuals)
//            std::cout << "actual = " << actual << std::endl;

        bool res_all = expects == actuals;

        size_t MaxLines = std::max(expects.size(), actuals.size());

        for (size_t i = 0; i < MaxLines; ++i)
        {
            std::string expect, actual;
            if (i < expects.size())
                expect = std::move(expects[i]);

            if (i < actuals.size())
                actual = std::move(actuals[i]);

            bool res_line = expect == actual;
            std::cout << std::setw(8+6) << res_line << std::setw(22) << expect << std::setw(22) << actual << std::setw(14) << Time << std::endl;
        }

        return res_all;
    }

public:
    Tester() = delete;

    void AddTask(ITask *_task, const std::string &_name)
    {
        Tasks.emplace_back(_name, _task);
    }

    Tester(ITask *_task, const std::string &_name, const std::string &_path) : Path(_path)
    {
        AddTask(_task, _name);
    }

    void RunTasks()
    {
        for (const auto [name, task] : Tasks)
        {
            std::cout << "Task - " << name << ":" << std::endl;
            ActiveTask = task;
            RunTests();
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }


//    void SetMaxTestCount(size_t _maxTestCount) {MaxTestCount = _maxTestCount;}
//    void SetShowExpects(bool _showExpects) {ShowExpects = _showExpects;}
//    void SetShowActuals(bool _showActuals) {ShowActuals = _showActuals;}
//    void SetShowTime(bool _showTime) {ShowTime = _showTime;}
};

#endif // TESTER_H
