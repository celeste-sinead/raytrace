/******************************************************************************
 * logger.h
 * Copyright 2011 Iain Peet
 *
 * Provides a simple logger class.
 ******************************************************************************
 * This program is distributed under the of the GNU Lesser Public License. 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>

// This is at global scope for the sake of brevity.
enum LogLevel {
    FATAL,
    ERROR,
    WARNING,
    INFO,
    DETAIL
};

/** Logger is a functor which, called with a log level, returns a reference
 *  to an ostream, which will point to a real output stream if the log level
 *  is sufficiently high, and /dev/null otherwise. */
class Logger {
private:
    enum LogLevel m_level;

public:
    Logger(enum LogLevel level = WARNING):
        m_level(level)
        {}

    void setLevel(enum LogLevel level) { m_level = level; }

    std::ostream& operator()(enum LogLevel level = WARNING);
};

#endif //LOGGER_H_
