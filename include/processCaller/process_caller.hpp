#ifndef PROCESS_CALLER_HPP_
#define PROCESS_CALLER_HPP_

#include <windows.h>
#include "utils/status.hpp"

namespace mlcxc
{
    class ProcessCaller
    {
        public:
        ProcessCaller();
        virtual ~ProcessCaller();
        virtual mlcxc::ReturnStatus init() = 0;
        virtual mlcxc::ReturnStatus call(const std::string& command) = 0;
    };
}
#endif //PROCESS_CALLER_HPP_