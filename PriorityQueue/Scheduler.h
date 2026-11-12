
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "PQType.h"

template <class ItemType>
class Scheduler : public PQType<ItemType>
{
public:
    // Pre: Size is greater than 0
    // Post: Creates an empty scheduler
    Scheduler(int s);

    // Pre: None
    // Post: Returns the number of waiting jobs
    int getNumJobs() const;

    // Pre: Job is valid
    // Post: Saves the job currently using the CPU
    void setCurrentJob(ItemType& j);

    // Pre: Queue is not full
    // Post: Adds a job to the queue
    void addJob(ItemType& j);

    // Pre: Queue is not empty
    // Post: Removes the highest priority job
    void removeJob(ItemType& j);

private:
    int numJobs;
    ItemType currentJob;
};

template <class ItemType>
Scheduler<ItemType>::Scheduler(int s)
    : PQType<ItemType>(s)
{
    numJobs = 0;
}

template <class ItemType>
int Scheduler<ItemType>::getNumJobs() const
{
    return numJobs;
}

template <class ItemType>
void Scheduler<ItemType>::setCurrentJob(ItemType& j)
{
    currentJob = j;
}

template <class ItemType>
void Scheduler<ItemType>::addJob(ItemType& j)
{
    // Heap rule:
    // A parent must have a higher or equal priority
    // than its children.
    // ReheapUp fixes the heap after adding a job.
    // ReheapDown fixes it after removing a job.
    // This keeps the highest priority job at the top.

    this->Enqueue(j);
    numJobs++;
}

template <class ItemType>
void Scheduler<ItemType>::removeJob(ItemType& j)
{
    this->Dequeue(j);
    numJobs--;
}

#endif
