/***************************************************************************
 *   Copyright (c) 2024 FreeCAD Developers                                 *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License (LGPL)   *
 *   as published by the Free Software Foundation; either version 2 of     *
 *   the License, or (at your option) any later version.                   *
 *   for detail see the LICENCE text file.                                 *
 *                                                                         *
 *   FreeCAD is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with FreeCAD; if not, write to the Free Software        *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
 *   USA                                                                   *
 *                                                                         *
 ***************************************************************************/

#include "PreCompiled.h"

#ifndef _PreComp_
# include <spdlog/spdlog.h>
# include <spdlog/sinks/stdout_color_sinks.h>
# include <spdlog/sinks/rotating_file_sink.h>
#endif

#include "ConsoleObserverSpdlog.h"

using namespace Base;

ConsoleObserverSpdlog::ConsoleObserverSpdlog()
{
    try {
        // Create a multi-sink logger (both console and file)
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);
        
        // Create rotating file sink (5MB max size, 3 rotating files)
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "FreeCAD.log", 1024 * 1024 * 5, 3);
        file_sink->set_level(spdlog::level::trace);
        
        // Combine sinks
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        logger = std::make_shared<spdlog::logger>("FreeCAD", sinks.begin(), sinks.end());
        
        // Set pattern: [timestamp] [level] [notifier] message
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%n] %v");
        logger->set_level(spdlog::level::trace);
        
        // Register logger globally
        spdlog::register_logger(logger);
    }
    catch (const std::exception& ex) {
        // Fallback to basic logger if setup fails
        logger = spdlog::stdout_color_mt("FreeCAD_basic");
        logger->error("Failed to initialize spdlog properly: {}", ex.what());
    }
}

ConsoleObserverSpdlog::~ConsoleObserverSpdlog()
{
    if (logger) {
        logger->flush();
        spdlog::drop("FreeCAD");
    }
}

void ConsoleObserverSpdlog::SendLog(const std::string& notifiername, 
                                    const std::string& msg, 
                                    LogStyle level,
                                    IntendedRecipient recipient, 
                                    ContentType content)
{
    if (!logger) {
        return;
    }

    // Map FreeCAD log levels to spdlog levels
    spdlog::level::level_enum spdlog_level;
    switch (level) {
        case LogStyle::Error:
            spdlog_level = spdlog::level::err;
            break;
        case LogStyle::Warning:
            spdlog_level = spdlog::level::warn;
            break;
        case LogStyle::Message:
            spdlog_level = spdlog::level::info;
            break;
        case LogStyle::Log:
            spdlog_level = spdlog::level::debug;
            break;
        case LogStyle::Critical:
            spdlog_level = spdlog::level::critical;
            break;
        case LogStyle::Notification:
            spdlog_level = spdlog::level::info;
            break;
        default:
            spdlog_level = spdlog::level::trace;
            break;
    }

    // Format the message with notifier if present
    std::string formatted_msg = msg;
    if (!notifiername.empty()) {
        formatted_msg = "[" + notifiername + "] " + msg;
    }

    // Log the message at the appropriate level
    logger->log(spdlog_level, formatted_msg);
}

std::shared_ptr<spdlog::logger> ConsoleObserverSpdlog::GetLogger()
{
    return logger;
}
