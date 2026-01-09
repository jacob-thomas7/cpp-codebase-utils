#include <csignal>

#include "utils/runtime.hpp"
#include "utils/metadata.hpp"
#include <iostream>

namespace crotale::utils
{
    using namespace std::chrono_literals;

    Start::Start()   : Event(this) { };
    Update::Update() : Event(this) { };
    Quit::Quit()     : Event(this) { };

    Runtime::Runtime(uint8_t max_fps, bool self_start) : System(this), refresh_delay(1000ms / max_fps)
    {
        add_event_handler(&Runtime::on_start);
        add_event_handler(&Runtime::on_update);
        add_event_handler(&Runtime::on_quit);

        std::signal(SIGINT, [](int signal) {
            core::Application::get_instance().interrupt<Quit>();
        });
        
        std::signal(SIGTERM, [](int signal) {
            core::Application::get_instance().interrupt<Quit>();
        });

        if (self_start) {
            application.queue_event<Start>();
        }
    }

    void Runtime::on_start(Start& event)
    {
        application.queue_event_ms<Update>(refresh_delay);
    }
    
    void Runtime::on_update(Update& event)
    {
        application.queue_event_ms<Update>(refresh_delay);
    }

    void Runtime::on_quit(Quit& event)
    {
        application.quit();
    }
}