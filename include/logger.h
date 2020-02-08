#pragma once

#include <string>
#include <string_view>
#include <array>

template <class char_t, size_t buffer_size>
class Logger {
    public:
        enum message_t {
            DebugMsg,
            InfoMsg,
            WarningMsg,
            CriticalMsg,
            FatalMsg
        };
        using char_type = char_t;
        using string_type = std::basic_string<char_type>;
        using string_view_type = std::basic_string_view<char_type>;
        using handler_type = void(*)(message_t, string_view_type);
    private:
        handler_type messageHandler;

        template<message_t msgType>
        class Outputer {
            private:
                std::array<char_type, buffer_size> buffer;
                Logger& toOut;
            public:
                Outputer(Logger& toOut) : toOut(toOut) {}
                Outputer& operator << (string_type data) {
                    toOut.print(msgType, data);
                    return *this;
                }
        };
    public:
        Logger(handler_type msgHandler) : messageHandler(msgHandler) {};

        void setMessageHandler(handler_type newHandler) {
            messageHandler = newHandler;
        }

        void print(message_t type, string_view_type data) {
            messageHandler(type, data);
        }
};
