#include <sys/time.h>
#include <sys/resource.h>
#include <mach/mach.h>
#include "memory.h"

void showMemoryUsage(std::ostream &ss){
   ss << "Linux getrusage():\n";
   struct rusage resources;
   if(getrusage(RUSAGE_SELF, &resources) != 0){
      ss << "Could not retrieve resource usage.\n";
   }
   // unit is bytes on OSX and kilobytes on Linux
   ss << "    Total Resident Size: " << resources.ru_maxrss << " bytes\n\n";
   // unimplemented metrics that would've been interesting
   /* std::cout << "Integral Unshared Data Size: " << resources.ru_idrss << "" << "\n"; */
   /* std::cout << "Integral Unshared Stack Size: " << resources.ru_isrss << "" << "\n"; */

   ss << "MacOS task_info():\n";
   struct task_basic_info t_info;
   mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

   if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t) &t_info, &t_info_count) != KERN_SUCCESS){
      ss << "Could not retrieve resource usage\n";
   }
   ss << "    Total Resident Size: " << t_info.resident_size << " bytes\n";
   ss << "    Total Virtual Size:  " << t_info.virtual_size << " bytes\n";
}
