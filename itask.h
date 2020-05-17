// Header-only library for otus-algo homework testing
// Written by Sergey Tsynikin, 2020

#ifndef ITASK_H
#define ITASK_H

#include <string>
#include <vector>

class ITask
{
public:
    virtual std::vector<std::string> Run(const std::vector<std::string> &_data) = 0;
    virtual ~ITask() {};
};

#endif // ITASK_H
