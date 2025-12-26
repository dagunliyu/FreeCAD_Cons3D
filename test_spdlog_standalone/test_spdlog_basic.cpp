/*
 * Standalone test to verify spdlog builds and works correctly
 * This does NOT require FreeCAD dependencies
 */

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <iostream>

int main() {
    std::cout << "=== Testing spdlog static library ===" << std::endl;
    
    try {
        // Create a multi-sink logger
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);
        
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "test.log", 1024 * 1024 * 5, 3);
        file_sink->set_level(spdlog::level::trace);
        
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        auto logger = std::make_shared<spdlog::logger>("test", sinks.begin(), sinks.end());
        
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        logger->set_level(spdlog::level::trace);
        
        // Test all log levels
        logger->trace("This is a trace message");
        logger->debug("This is a debug message");
        logger->info("This is an info message");
        logger->warn("This is a warning message");
        logger->error("This is an error message");
        logger->critical("This is a critical message");
        
        // Test formatted logging
        logger->info("Testing formatted logging: int={}, float={:.2f}, string={}", 
                     42, 3.14159, "hello");
        
        logger->flush();
        
        std::cout << "\n✓ All spdlog tests passed!" << std::endl;
        std::cout << "✓ Spdlog static library is working correctly" << std::endl;
        std::cout << "✓ Log file created: test.log" << std::endl;
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "✗ Error: " << e.what() << std::endl;
        return 1;
    }
}
