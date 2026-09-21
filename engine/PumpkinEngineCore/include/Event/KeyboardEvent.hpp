#pragma once

#include "Event/Event.hpp"
#include <format>

namespace Pumpkin::Core {

class PE_EVENT(KeyPressedEvent) {
public:
  KeyPressedEvent(uint32_t keycode) : m_Code(keycode) {}

  inline uint32_t GetKeyCode() const { return m_Code; }

  inline std::string ToString() const override {
    return std::format("Key pressed event({})", m_Code);
  }

private:
  uint32_t m_Code;
};

class PE_EVENT(KeyReleasedEvent) {
public:
  KeyReleasedEvent(uint32_t keycode) : m_Code(keycode) {}

  inline uint32_t GetKeyCode() const { return m_Code; }

  inline std::string ToString() const override {
    return std::format("Key released event({})", m_Code);
  }

private:
  uint32_t m_Code;
};

} // namespace Pumpkin::Core
