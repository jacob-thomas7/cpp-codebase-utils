#pragma once

#include <chrono>
#include <cstdint>

#include "core/application.hpp"
#include "core/event.hpp"

namespace crotale::utils
{
    //! \brief Event to be called at the start of an application.
    //! \addtogroup events
    struct Start : public core::Event
    {
        Start();
    };
    
    //! \brief Event to be called at the start of every frame.
    //! \addtogroup events
    struct Update : public core::Event
    {
        Update();
    };

    //! \brief Event to be called at the end of the application.
    //! \addtogroup events
    struct Quit : public core::Event
    {
        Quit();
    };

    //! \brief System which provides runtime events.
    //! \addtogroup systems
    class Runtime : public core::System
    {
    public:
        Runtime(uint8_t max_fps = 60, bool self_start = true);
        void on_start(Start& event);
        void on_update(Update& event);
        void on_quit(Quit& event);
    
    private:
        std::chrono::milliseconds refresh_delay;
    };
}