#include "Event/Event.hpp"

uint32_t Pumpkin::Core::EventTypeCounter::GetNextID() {
  static uint32_t s_GlobalEventCounter = 0;
  return s_GlobalEventCounter++;
}
