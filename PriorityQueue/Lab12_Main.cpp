
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

#include "Job.h"
#include "Scheduler.h"

using namespace std;

namespace
{
    const int TOTAL_JOBS = 50;
    const int ARRIVAL_INTERVAL = 20;
    const int RUNS_PER_TEST = 1000;
    const int NUM_ATTEMPTS = 5;

    const double BENCHMARK_RATE = 0.60;

    const int CYCLE_LIMITS[NUM_ATTEMPTS] =
    {
        2600, 2625, 2650, 2675, 2700
    };

    const uint32_t BASE_SEED = 20261108u;

    struct SimulationResult
    {
        bool completed;
        int jobsProcessed;
        int cyclesUsed;
        double averageHeapSize;
    };

    // Pre: Cycle limit is between 1 and 2700
    // Post: Runs one simulation and returns the results
    SimulationResult runSimulation(int cycleLimit, uint32_t seed)
    {
        mt19937 engine(seed);

        uniform_int_distribution<int> coin(0, 1);
        uniform_int_distribution<int> priority(-19, 20);
        uniform_int_distribution<int> length(1, 100);

        Scheduler<Job> scheduler(TOTAL_JOBS);

        Job currentJob;

        bool cpuBusy = false;

        int jobsCreated = 0;
        int jobsProcessed = 0;
        int cyclesUsed = 0;

        long long heapSizeTotal = 0;

        // Go through each CPU cycle
        for (int cycle = 0; cycle < cycleLimit; ++cycle)
        {
            // Every 20 cycles, flip a coin to add a job
            if (cycle % ARRIVAL_INTERVAL == 0
                && jobsCreated < TOTAL_JOBS
                && coin(engine) == 1)
            {
                Job nextJob(
                    priority(engine),
                    length(engine),
                    "P" + to_string(jobsCreated + 1)
                );

                scheduler.addJob(nextJob);
                jobsCreated++;
            }

            // Get a new job if the CPU is free
            if (!cpuBusy && !scheduler.IsEmpty())
            {
                scheduler.removeJob(currentJob);
                scheduler.setCurrentJob(currentJob);

                cpuBusy = true;
            }

            // Count jobs waiting in the heap
            heapSizeTotal += scheduler.getNumJobs();

            // Run the current job for one cycle
            if (cpuBusy)
            {
                currentJob.decrementLength();

                // Check if the job is finished
                if (currentJob.getLength() == 0)
                {
                    cpuBusy = false;
                    jobsProcessed++;
                }
            }

            cyclesUsed++;

            // Stop when all 50 jobs are finished
            if (jobsProcessed == TOTAL_JOBS)
            {
                break;
            }
        }

        SimulationResult result;

        result.completed = (jobsProcessed == TOTAL_JOBS);
        result.jobsProcessed = jobsProcessed;
        result.cyclesUsed = cyclesUsed;

        result.averageHeapSize =
            static_cast<double>(heapSizeTotal) / cyclesUsed;

        return result;
    }

    // Pre: Output stream is valid
    // Post: Prints the results of one simulation
    void reportRun(ostream& out, const SimulationResult& result)
    {
        out << fixed << setprecision(2);

        out << "Average number of jobs in the heap per cycle: "
            << result.averageHeapSize << '\n';

        if (result.completed)
        {
            out << "The scheduler completed all 50 jobs.\n";

            out << "It took " << result.cyclesUsed
                << " cycles to complete them.\n";
        }
        else
        {
            out << "The scheduler did not complete all 50 jobs.\n";

            out << "Jobs processed: "
                << result.jobsProcessed << '\n';
        }
    }
}

int main()
{
    ofstream logFile("Lab12_Results.txt");

    if (!logFile)
    {
        cerr << "Could not create Lab12_Results.txt\n";
        return 1;
    }

    int bestCycleLimit = -1;
    double bestCompletionRate = 0.0;

    cout << "Lab 12 - Operating System Job Scheduler\n";

    cout << "Benchmark: smallest tested cycle limit "
         << "with >= 60% completion\n";

    cout << "Trials per attempt: "
         << RUNS_PER_TEST << "\n\n";

    // Try five different cycle limits
    for (int attempt = 0; attempt < NUM_ATTEMPTS; ++attempt)
    {
        int cycleLimit = CYCLE_LIMITS[attempt];

        int completed = 0;
        int incomplete = 0;

        double averageHeapAcrossRuns = 0.0;

        logFile << "========== Attempt "
                << attempt + 1 << ": "
                << cycleLimit << " cycles ==========\n";

        // Run 1000 simulations for each attempt
        for (int trial = 0; trial < RUNS_PER_TEST; ++trial)
        {
            SimulationResult result = runSimulation(
                cycleLimit,
                BASE_SEED + static_cast<uint32_t>(trial)
            );

            // Count completed and incomplete runs
            if (result.completed)
            {
                completed++;
            }
            else
            {
                incomplete++;
            }

            averageHeapAcrossRuns += result.averageHeapSize;

            // Save each simulation result
            logFile << "Simulation " << trial + 1 << "\n";

            reportRun(logFile, result);

            logFile << '\n';
        }

        // Calculate the completion rate
        double completionRate =
            static_cast<double>(completed) / RUNS_PER_TEST;

        averageHeapAcrossRuns /= RUNS_PER_TEST;

        logFile << "Completed simulations: "
                << completed << '\n';

        logFile << "Incomplete simulations: "
                << incomplete << "\n\n";

        // Print the results for this attempt
        cout << "Attempt " << attempt + 1
             << " (" << cycleLimit << " cycles)\n";

        cout << "Completed simulations: "
             << completed << '\n';

        cout << "Incomplete simulations: "
             << incomplete << '\n';

        cout << "Completion rate: "
             << fixed << setprecision(1)
             << completionRate * 100.0 << "%\n";

        cout << "Average heap jobs/cycle across trials: "
             << setprecision(2)
             << averageHeapAcrossRuns << "\n\n";

        // Find the first limit that reaches 60%
        if (completionRate >= BENCHMARK_RATE
            && bestCycleLimit < 0)
        {
            bestCycleLimit = cycleLimit;
            bestCompletionRate = completionRate;
        }
    }

    // Print the final benchmark
    if (bestCycleLimit >= 0)
    {
        cout << "Benchmark threshold: "
             << bestCycleLimit << " cycles ("
             << fixed << setprecision(1)
             << bestCompletionRate * 100.0
             << "% completion).\n";
    }
    else
    {
        cout << "No tested limit achieved "
             << "the 60% benchmark.\n";
    }

    cout << "Full individual-run output saved "
         << "in Lab12_Results.txt\n";

    return 0;
}
