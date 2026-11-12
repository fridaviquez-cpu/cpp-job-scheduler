
#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <string>

class Job
{
public:
    // Pre: None
    // Post: Creates an empty job
    Job();

    // Pre: Priority is -19 to 20 and length is 1 to 100
    // Post: Creates a job with a priority and length
    Job(int p, int l);

    // Pre: Valid priority and length
    // Post: Creates a job with a name
    Job(int p, int l, const std::string& n);

    // Pre: None
    // Post: Returns how many cycles are left
    int getLength() const;

    // Pre: Job still has cycles left
    // Post: Subtracts one cycle from the job
    void decrementLength();

    // Pre: None
    // Post: Returns the priority
    int getPriority() const;

    // Pre: None
    // Post: Returns the job name
    std::string getName() const;

    // Pre: Output stream is valid
    // Post: Prints the job information
    friend std::ostream& operator<<(std::ostream& out,
                                    const Job& j);

    // Pre: None
    // Post: Compares the priorities of two jobs
    bool operator<(Job otherJob);
    bool operator>(Job otherJob);
    bool operator==(Job otherJob);
    bool operator<=(Job otherJob);

private:
    int length;
    int priority;
    std::string name;
};

#endif
