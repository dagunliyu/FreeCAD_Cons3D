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

#ifndef BASE_CONSOLEOBSERVERSPDLOG_H
#define BASE_CONSOLEOBSERVERSPDLOG_H

#include <Base/Console.h>
#include <memory>

// Forward declaration to avoid including spdlog headers
namespace spdlog {
    class logger;
}

namespace Base {

/** The ConsoleObserverSpdlog class
 *  This class integrates spdlog with FreeCAD's Console system.
 *  It implements the ILogger interface and forwards messages to spdlog.
 */
class BaseExport ConsoleObserverSpdlog : public ILogger
{
public:
    ConsoleObserverSpdlog();
    ~ConsoleObserverSpdlog() override;

    void SendLog(const std::string& notifiername, const std::string& msg, LogStyle level,
                 IntendedRecipient recipient, ContentType content) override;
    const char* Name() override {return "Spdlog";}

    // Get the underlying spdlog logger for advanced configuration
    std::shared_ptr<spdlog::logger> GetLogger();

private:
    std::shared_ptr<spdlog::logger> logger;
};

} // namespace Base

#endif // BASE_CONSOLEOBSERVERSPDLOG_H
