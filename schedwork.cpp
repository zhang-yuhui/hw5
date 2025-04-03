#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    size_t day, size_t worker,
    const AvailabilityMatrix& avail, 
    const size_t dailyNeed, 
    const size_t maxShifts,
    vector<size_t>& shifts,
    DailySchedule& sched);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t numWorkers = avail[0].size();
    size_t numDays = avail.size();

    if(numWorkers < dailyNeed){
        return false;
    }
    vector<size_t> shifts(numWorkers, 0);
    sched = DailySchedule(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));
    return scheduleHelper(0, 0, avail, dailyNeed, maxShifts, shifts, sched);
}

bool scheduleHelper(
    size_t day, size_t worker,
    const AvailabilityMatrix& avail, 
    const size_t dailyNeed, 
    const size_t maxShifts,
    vector<size_t>& shifts,
    DailySchedule& sched)
{
    if(day >= sched.size())
        return true;

    size_t numWorkers = avail[0].size();

    if(worker < dailyNeed){
        size_t start_ID = (worker == 0) ? 0 : sched[day][worker - 1] + 1;
        //std::cout<<start_ID << std::endl;
        for(size_t i = start_ID; i < numWorkers; i++){
            if(avail[day][i] and (shifts[i] < maxShifts)){
                shifts[i] ++; // mark as taken, also >> maxShifts
                sched[day][worker] = i;

                if(scheduleHelper(day, worker + 1, avail, dailyNeed, maxShifts, shifts, sched))
                    return true;

                shifts[i] --;
                sched[day][worker] = INVALID_ID;
            }
        }
        return false;
    } else {
        size_t index = -1; // record index of shifts, starts at -1 to compensate for 0-index
        auto updateShifts = [&sched,&index, day](size_t s){
            index++;
            return std::find(sched[day].begin(), sched[day].end(), index) != sched[day].end() ? s : 0;
        };
        std::for_each(shifts.cbegin(), shifts.cend() ,updateShifts);
        return scheduleHelper(day + 1, 0, avail, dailyNeed, maxShifts, shifts, sched);
    }
}


