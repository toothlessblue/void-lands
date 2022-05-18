//
// Created by ellis on 19/03/2022.
//

#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <ostream>

class Logger {
public:
    // TODO log levels

    struct Info {
        std::stringstream s;

        template<typename T>
        Info &operator<<(const T &x) {
            s << x;
            return *this;
        }

        ~Info();
    };

    struct Error {
        std::stringstream s;

        template<typename T>
        Error &operator<<(const T &x) {
            s << x;
            return *this;
        }

        ~Error();
    };

    struct Debug {
        std::stringstream s;

        template<typename T>
        Debug &operator<<(const T &x) {
            s << x;
            return *this;
        }

        ~Debug();
    };
};