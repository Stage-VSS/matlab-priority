#include <mex.h>

#ifdef __APPLE__
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach_init.h>
#include <mach/thread_act.h>
#elif defined _WIN32 || defined _WIN64

#elif __linux || __unix || __posix

#endif

#ifdef __APPLE__
void setNormalPriority()
{
    thread_standard_policy_data_t policy;
    mach_msg_type_number_t count;
    boolean_t getDefault;
    kern_return_t result;
    
    count = THREAD_STANDARD_POLICY_COUNT;
    getDefault = true;
    result = thread_policy_get(mach_thread_self(), THREAD_STANDARD_POLICY, (thread_policy_t)&policy, &count, &getDefault);
    if (result)
    {
        mexErrMsgIdAndTxt("priority:failed", "Failed to get normal priority");
    }
    
    result = thread_policy_set(mach_thread_self(), THREAD_STANDARD_POLICY, (thread_policy_t)&policy, THREAD_STANDARD_POLICY_COUNT);
    if (result)
    {
        mexErrMsgIdAndTxt("priority:failed", "Failed to set normal priority");
    }
}

#elif defined _WIN32 || defined _WIN64
void setNormalPriority()
{
    mexErrMsgIdAndTxt("priority:failed", "Not implemented for this platform");
}

#elif __linux || __unix || __posix
void setNormalPriority()
{
    mexErrMsgIdAndTxt("priority:failed", "Not implemented for this platform");
}

#endif

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{    
    if (nrhs > 0)
    {
        mexErrMsgIdAndTxt("priority:usage", "Usage: setNormalPriority()");
        return;
    }
    
    setNormalPriority();
}