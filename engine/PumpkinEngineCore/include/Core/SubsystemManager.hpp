#pragma once

#include "Core/Subsystem.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Pumpkin::Core {

class SubsystemManager {
public:
  SubsystemManager() = default;
  ~SubsystemManager() { ShutdownAll(); }

  // NO COPY
  SubsystemManager(const SubsystemManager &) = delete;
  SubsystemManager &operator=(const SubsystemManager &) = delete;

  template <typename T, typename... Args> T *RegisterSubsystem(Args &&...args) {
    static_assert(std::is_base_of<PESubsystem, T>::value,
                  "Class must derive from PESubsystem!");

    auto subsystem = std::make_unique<T>(std::forward<Args>(args)...);
    T *rawPtr = subsystem.get();

    subsystem->OnBegin();

    m_Subsystems.push_back(std::move(subsystem));
    m_SubsystemMap[typeid(T)] = rawPtr;

    return rawPtr;
  }

  template <typename T> T *GetSubsystem() {
    auto it = m_SubsystemMap.find(typeid(T));
    if (it != m_SubsystemMap.end()) {
      return static_cast<T *>(it->second);
    }
    return nullptr;
  }

  void UpdateAll(const Time &time);
  void RenderAll();
  void OnEventAll(Event &event);
  void ShutdownAll();

private:
  std::vector<std::unique_ptr<PESubsystem>> m_Subsystems;
  std::unordered_map<std::type_index, PESubsystem *> m_SubsystemMap;
};

} // namespace Pumpkin::Core
