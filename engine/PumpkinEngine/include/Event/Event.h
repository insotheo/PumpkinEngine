#ifndef PUMPKIN_ENGINE_EVENT_H
#define PUMPKIN_ENGINE_EVENT_H

#include <cstdint>
#include <string>

namespace Pumpkin{
    class Event{
    public:
        virtual ~Event() = default;
        virtual std::string ToString() const = 0;

        virtual uint32_t GetTypeID() const = 0;

        bool Handled = false;
    };

    template<typename T>
    class EventImpl : public Event{
    public:
        static uint32_t GetStaticTypeID(){
            static uint32_t s_TypeID = GetNextID();
            return s_TypeID;
        }

        inline uint32_t GetTypeID() const override { return GetStaticTypeID(); }
    private:
        static uint32_t GetNextID(){
            static uint32_t s_EventCounter = 0;
            return s_EventCounter++;
        }
    };

    class EventDispatcher{
    public:
        EventDispatcher(Event& event) : m_Event(event)
        {}

        template<typename T, typename Func>
        void Dispatch(Func&& fn){
            if(m_Event.Handled) return;

            if(m_Event.GetTypeID() == T::GetStaticTypeID()){
                fn(static_cast<T&>(m_Event));
            }
        }

    private:
        Event& m_Event;
    };
}

#endif