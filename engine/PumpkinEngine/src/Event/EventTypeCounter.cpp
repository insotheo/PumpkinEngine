#include "Event/Event.h"

namespace Pumpkin{
    uint32_t EventTypeCounter::GetNextID(){
        static uint32_t s_GlobalEventCounter = 0;
        return s_GlobalEventCounter++;
    }
}