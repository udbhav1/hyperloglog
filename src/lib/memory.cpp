#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>
#include <mach/mach.h>
#include "memory.h"

void getMemoryUsage(){
   std::cout << "Linux getrusage():\n";
   struct rusage resources;
   if(getrusage(RUSAGE_SELF, &resources) != 0){
      std::cout << "Could not retrieve resource usage.\n";
   }
   // unit is bytes on OSX and kilobytes on Linux
   std::cout << "    Total Resident Size: " << resources.ru_maxrss << " bytes\n\n";
   // unimplemented metrics that would've been interesting
   /* std::cout << "Integral Unshared Data Size: " << resources.ru_idrss << "" << "\n"; */
   /* std::cout << "Integral Unshared Stack Size: " << resources.ru_isrss << "" << "\n"; */

   std::cout << "MacOS task_info():\n";
   struct task_basic_info t_info;
   mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

   if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t) &t_info, &t_info_count) != KERN_SUCCESS){
      std::cout << "Could not retrieve resource usage\n";
   }
   std::cout << "    Total Resident Size: " << t_info.resident_size << " bytes\n";
   std::cout << "    Total Virtual Size:  " << t_info.virtual_size << " bytes\n";
}
