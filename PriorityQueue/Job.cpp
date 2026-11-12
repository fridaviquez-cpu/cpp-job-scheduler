
#include "Job.h"

Job::Job()
    : length(0), priority(0), name("")
{
}

Job::Job(int p, int l)
    : length(l), priority(p), name("")
{
}

Job::Job(int p, int l, const std::string& n)
    : length(l), priority(p), name(n)
{
}

int Job::getLength() const
{
    return length;
}

void Job::decrementLength()
{
    if (length > 0)
    {
        --length;
    }
}

int Job::getPriority() const
{
    return priority;
}

std::string Job::getName() const
{
    return name;
}

std::ostream& operator<<(std::ostream& out, const Job& j)
{
    out << j.name << " (priority " << j.priority
        << ", remaining length " << j.length << ")";

    return out;
}

bool Job::operator<(Job otherJob)
{
    return priority < otherJob.priority;
}

bool Job::operator>(Job otherJob)
{
    return priority > otherJob.priority;
}

bool Job::operator==(Job otherJob)
{
    return priority == otherJob.priority;
}

bool Job::operator<=(Job otherJob)
{
    return priority <= otherJob.priority;
}
