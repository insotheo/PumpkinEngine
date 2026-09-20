#pragma once

namespace Pumpkin::Core {
enum class EventType {
  None = 0,

  WindowClose,
  WindowResize,

  KeyPressed,
  KeyReleased,

  MouseMoved,
  MouseButtonPressed,
  MouseScrolled,
};

class Event {
public:
  virtual ~Event() = default;

  virtual EventType GetType() const = 0;
  virtual const char *GetName() const = 0;

  bool Handled = false;
};

} // namespace Pumpkin::Core
