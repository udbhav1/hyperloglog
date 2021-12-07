#include "memory.h"

long long bytesUsed(){

#ifdef __linux__

   struct rusage resources;
   if(getrusage(RUSAGE_SELF, &resources) != 0){
      return -1;
   }
   return resources.ru_maxrss*1000;

#elif __APPLE__

   struct task_basic_info t_info;
   mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

   if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t) &t_info, &t_info_count) != KERN_SUCCESS){
      return -1;
   }
   return t_info.resident_size;

#endif

}
