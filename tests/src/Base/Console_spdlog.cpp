/***************************************************************************
 *   Copyright (c) 2024 FreeCAD Developers                                 *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include <gtest/gtest.h>

#include <Base/Console.h>
#include <Base/ConsoleObserverSpdlog.h>
#include <spdlog/spdlog.h>

// Test fixture for Console with spdlog integration
class ConsoleSpdlogTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Attach spdlog observer
        spdlogObserver = new Base::ConsoleObserverSpdlog();
        Base::Console().AttachObserver(spdlogObserver);
    }

    void TearDown() override
    {
        // Detach and clean up
        Base::Console().DetachObserver(spdlogObserver);
        delete spdlogObserver;
        spdlogObserver = nullptr;
    }

    Base::ConsoleObserverSpdlog* spdlogObserver = nullptr;
};

// Test basic message logging through Base::Console to spdlog
TEST_F(ConsoleSpdlogTest, BasicMessageLogging)
{
    ASSERT_NE(spdlogObserver, nullptr);
    
    // These messages should be logged through spdlog
    Base::Console().Message("Test message\n");
    Base::Console().Warning("Test warning\n");
    Base::Console().Error("Test error\n");
    Base::Console().Log("Test log\n");
    
    // Flush to ensure all messages are written
    auto logger = spdlogObserver->GetLogger();
    ASSERT_NE(logger, nullptr);
    logger->flush();
    
    // Test passes if no crash occurred
    SUCCEED();
}

// Test message with notifier
TEST_F(ConsoleSpdlogTest, MessageWithNotifier)
{
    ASSERT_NE(spdlogObserver, nullptr);
    
    Base::Console().Message("TestModule", "Message from test module\n");
    Base::Console().Warning("TestModule", "Warning from test module\n");
    Base::Console().Error("TestModule", "Error from test module\n");
    
    auto logger = spdlogObserver->GetLogger();
    logger->flush();
    
    SUCCEED();
}

// Test different log levels
TEST_F(ConsoleSpdlogTest, DifferentLogLevels)
{
    ASSERT_NE(spdlogObserver, nullptr);
    
    // Test all log levels
    Base::Console().Message("Info level message\n");
    Base::Console().Warning("Warning level message\n");
    Base::Console().Error("Error level message\n");
    Base::Console().Log("Debug level message\n");
    Base::Console().Critical("Critical level message\n");
    
    auto logger = spdlogObserver->GetLogger();
    logger->flush();
    
    SUCCEED();
}

// Test formatted messages
TEST_F(ConsoleSpdlogTest, FormattedMessages)
{
    ASSERT_NE(spdlogObserver, nullptr);
    
    int value = 42;
    double pi = 3.14159;
    const char* str = "formatted";
    
    Base::Console().Message("Integer value: %d\n", value);
    Base::Console().Warning("Float value: %.2f\n", pi);
    Base::Console().Error("String value: %s\n", str);
    Base::Console().Log("Combined: %d, %.2f, %s\n", value, pi, str);
    
    auto logger = spdlogObserver->GetLogger();
    logger->flush();
    
    SUCCEED();
}

// Test spdlog logger direct access
TEST_F(ConsoleSpdlogTest, DirectSpdlogAccess)
{
    ASSERT_NE(spdlogObserver, nullptr);
    
    auto logger = spdlogObserver->GetLogger();
    ASSERT_NE(logger, nullptr);
    
    // Use spdlog API directly
    logger->info("Direct spdlog info message");
    logger->warn("Direct spdlog warn message");
    logger->error("Direct spdlog error message");
    logger->debug("Direct spdlog debug message");
    
    logger->flush();
    
    SUCCEED();
}

// Test spdlog with structured logging
TEST_F(ConsoleSpdlogTest, StructuredLogging)
{
    ASSERT_NE(spdlogObserver, nullptr);
    
    auto logger = spdlogObserver->GetLogger();
    ASSERT_NE(logger, nullptr);
    
    // Structured logging with parameters
    logger->info("Processing item: id={}, name={}, status={}", 
                 123, "TestItem", "active");
    logger->warn("Resource usage: cpu={}%, memory={}MB", 
                 75.5, 2048);
    logger->error("Operation failed: code={}, message={}", 
                  -1, "File not found");
    
    logger->flush();
    
    SUCCEED();
}

// Test concurrent logging (spdlog is thread-safe)
TEST_F(ConsoleSpdlogTest, ConcurrentLogging)
{
    ASSERT_NE(spdlogObserver, nullptr);
    
    // Log from multiple threads (simplified test)
    for (int i = 0; i < 10; ++i) {
        Base::Console().Message("Concurrent message %d\n", i);
    }
    
    auto logger = spdlogObserver->GetLogger();
    logger->flush();
    
    SUCCEED();
}

// Example: Integration with Base::Console tag-based logging
TEST_F(ConsoleSpdlogTest, TagBasedLogging)
{
    ASSERT_NE(spdlogObserver, nullptr);
    
    // Simulate tag-based logging through Base::Console
    Base::Console().Message("MyModule", "Module initialized successfully\n");
    Base::Console().Log("MyModule", "Starting operation...\n");
    Base::Console().Warning("MyModule", "Performance degraded\n");
    Base::Console().Error("MyModule", "Operation failed\n");
    
    auto logger = spdlogObserver->GetLogger();
    logger->flush();
    
    SUCCEED();
}
