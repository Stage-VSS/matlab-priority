#include <mex.h>

#ifdef __APPLE__
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach_init.h>
#include <mach/thread_act.h>
#elif defined _WIN32 || defined _WIN64
#include <windows.h>
#elif __linux || __unix || __posix

#endif

#ifdef __APPLE__
void setMaxPriority()
{
    int mib[2];
    int busFreq;
    size_t len;
    thread_time_constraint_policy_data_t policy;
    kern_return_t result;
    
    mib[0] = CTL_HW;
    mib[1] = HW_BUS_FREQ;
    len = sizeof(busFreq);
    sysctl(mib, 2, &busFreq, &len, NULL, 0);
    
    policy.period = busFreq / 120;
    policy.computation = policy.period * 0.9;
    policy.constraint = policy.computation;
    policy.preemptible = 1;
    
    result = thread_policy_set(mach_thread_self(), THREAD_TIME_CONSTRAINT_POLICY, (thread_policy_t)&policy, THREAD_TIME_CONSTRAINT_POLICY_COUNT);
    if (result)
    {
        mexErrMsgIdAndTxt("priority:failed", "Failed to set max priority");
    }
}

#elif defined _WIN32 || defined _WIN64
void setMaxPriority()
{
	bool result;
	
    result = SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
    if (!result)
    {
        mexErrMsgIdAndTxt("priority:failed", "Failed to set max priority");
    }
	
	result = SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	if (!result)
    {
        mexErrMsgIdAndTxt("priority:failed", "Failed to set max priority");
    }
}

#elif __linux || __unix || __posix
void setMaxPriority()
{
    mexErrMsgIdAndTxt("priority:failed", "Not implemented for this platform");
}

#endif

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{    
    if (nrhs > 0)
    {
        mexErrMsgIdAndTxt("priority:usage", "Usage: setMaxPriority()");
        return;
    }
    
    setMaxPriority();
}