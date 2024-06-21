#ifndef PROCESS_CALLER_FACTORY_HPP_
#define PROCESS_CALLER_FACTORY_HPP_

#include "processCaller/process_caller.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include "processCaller/process_caller_win.hpp"
#endif
#if defined(__linux__)
#include "processCaller/process_caller_lin.hpp"
#endif

namespace mlcxc
{
 mlcxc::ReturnStatus process_caller_new(mlcxc::ProcessCaller ** caller);
 
 void process_caller_destroy(mlcxc::ProcessCaller ** caller);
}
#endif //PROCESS_CALLER_FACTORY_HPP_