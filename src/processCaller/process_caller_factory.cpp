#include "processCaller/process_caller_factory.hpp"

mlcxc::ReturnStatus mlcxc::process_caller_new(ProcessCaller ** caller)
{
    ReturnStatus retStat = ReturnStatus::kOk;
    #ifdef MLCXC_PROC_CALLER_WIN
    *caller = (ProcessCaller *) new ProcessCallerWin();
    #endif
    #ifdef MLCXC_PROC_CALLER_LIN
    *caller = (ProcessCaller *) new ProcessCallerLin();
    #endif
    return retStat;
}

void mlcxc::process_caller_destroy(ProcessCaller ** caller)
{
	if (*caller != nullptr) {
		delete *caller;
	}

	*caller = nullptr;
}