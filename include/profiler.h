#ifndef _PROFILER_H
#define _PROFILER_H

#include <chrono>
#include <ctime>
#include <iostream>

#include "ioutils.h"

using namespace std;

typedef chrono::steady_clock _clock;
typedef double _duration;

template <typename T>
class usage_timer
{
    public:
        static void addInterval(const _duration& d)
        {
            computation_time += d;
        }

    private:
        static _duration computation_time;
};

template <typename T>
_duration usage_timer<T>::computation_time(0);

class timed_frame
{
    public:
        timed_frame() : _frame_start(_clock::now()) {
        }

        ~timed_frame() {
            insert_check();
        }

        inline void insert_check() const {
            print_duration();
        }
    private:
        void print_duration() const {
            chrono::duration<_duration> elapsed_time(_clock::now() - _frame_start);
            //io.printComment("elapsed time : " + std::to_string(elapsed_time.count()) + "s");
        }

        chrono::time_point<_clock> _frame_start;
};

# ifndef VERBOSE
#define PROFILE_FRAME_BEGIN
#define PROFILE_TAG
#define PROFILE_FRAME_END
# else
#define PROFILE_FRAME_BEGIN do{ timed_frame _timed_obj
#define PROFILE_TAG do{ _timed_obj.insert_check(); } while(false)
#define PROFILE_FRAME_END  } while(false)
# endif

#endif // _PROFILER_H
