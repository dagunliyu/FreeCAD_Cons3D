/***************************************************************************
 *   Spdlog Integration Example for FreeCAD                                *
 *                                                                         *
 *   This example demonstrates how to use spdlog with Base::Console        *
 *                                                                         *
 ***************************************************************************/

#include <Base/Console.h>
#include <Base/ConsoleObserverSpdlog.h>
#include <spdlog/spdlog.h>

/*
 * Example 1: Basic Integration
 * 
 * This shows the simplest way to integrate spdlog with FreeCAD's Console system.
 * All messages sent through Base::Console will be automatically logged by spdlog.
 */
void example_basic_integration()
{
    // Create and attach spdlog observer
    Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
    Base::Console().AttachObserver(spdlogObserver);
    
    // Now all console messages will be logged through spdlog
    Base::Console().Message("Application started\n");
    Base::Console().Log("Initializing modules...\n");
    Base::Console().Warning("Configuration file not found, using defaults\n");
    
    // Messages with notifier/source
    Base::Console().Message("MainWindow", "GUI initialized successfully\n");
    Base::Console().Error("Database", "Connection failed: timeout\n");
    
    // Don't forget to detach and cleanup when done
    Base::Console().DetachObserver(spdlogObserver);
    delete spdlogObserver;
}

/*
 * Example 2: Advanced Logging with Direct spdlog Access
 * 
 * You can access the underlying spdlog logger for advanced features
 * like structured logging and custom formatting.
 */
void example_advanced_logging()
{
    Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
    Base::Console().AttachObserver(spdlogObserver);
    
    // Get direct access to spdlog logger
    auto logger = spdlogObserver->GetLogger();
    
    // Use spdlog's structured logging capabilities
    logger->info("User logged in: username={}, role={}, session={}", 
                 "john_doe", "admin", "abc123");
    
    logger->warn("Resource usage high: cpu={:.1f}%, memory={}MB, disk={}GB",
                 87.5, 4096, 500);
    
    // Spdlog supports various log levels
    logger->trace("Detailed trace information");
    logger->debug("Debug information for developers");
    logger->info("General information");
    logger->warn("Warning message");
    logger->error("Error message");
    logger->critical("Critical error requiring immediate attention");
    
    Base::Console().DetachObserver(spdlogObserver);
    delete spdlogObserver;
}

/*
 * Example 3: Combining Multiple Observers
 * 
 * Spdlog observer works alongside other console observers.
 * This allows simultaneous logging to multiple destinations.
 */
void example_multiple_observers()
{
    // Attach both file and spdlog observers
    Base::ConsoleObserverFile* fileObserver = 
        new Base::ConsoleObserverFile("traditional.log");
    Base::ConsoleObserverSpdlog* spdlogObserver = 
        new Base::ConsoleObserverSpdlog();
    
    Base::Console().AttachObserver(fileObserver);
    Base::Console().AttachObserver(spdlogObserver);
    
    // Messages will go to both traditional log file and spdlog
    Base::Console().Message("This message goes to both log systems\n");
    Base::Console().Warning("Both systems will receive this warning\n");
    
    // Cleanup
    Base::Console().DetachObserver(fileObserver);
    Base::Console().DetachObserver(spdlogObserver);
    delete fileObserver;
    delete spdlogObserver;
}

/*
 * Example 4: Performance Monitoring
 * 
 * Demonstrates using spdlog for performance logging and monitoring.
 */
void example_performance_monitoring()
{
    Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
    Base::Console().AttachObserver(spdlogObserver);
    
    auto logger = spdlogObserver->GetLogger();
    
    // Simulate operation monitoring
    logger->info("Operation started: id={}, type={}", 1001, "model_calculation");
    
    // Log performance metrics
    logger->info("Operation progress: {}% complete, elapsed={}ms", 
                 25, 1500);
    logger->info("Operation progress: {}% complete, elapsed={}ms", 
                 50, 3200);
    logger->info("Operation progress: {}% complete, elapsed={}ms", 
                 75, 4800);
    
    // Log completion
    logger->info("Operation completed: id={}, status={}, duration={}ms, vertices={}, faces={}",
                 1001, "success", 6400, 10000, 5000);
    
    Base::Console().DetachObserver(spdlogObserver);
    delete spdlogObserver;
}

/*
 * Example 5: Error Tracking
 * 
 * Shows how to use spdlog for comprehensive error tracking.
 */
void example_error_tracking()
{
    Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
    Base::Console().AttachObserver(spdlogObserver);
    
    auto logger = spdlogObserver->GetLogger();
    
    // Track errors with context
    logger->error("File operation failed: path={}, operation={}, error_code={}, message={}",
                  "/path/to/file.fcstd", "save", -5, "Permission denied");
    
    logger->error("Geometry validation failed: object={}, check={}, reason={}",
                  "Sketch001", "self_intersection", "Lines 5 and 12 intersect");
    
    logger->critical("System error: component={}, error={}, action={}",
                    "OpenCASCADE", "memory_allocation_failed", "restart_required");
    
    Base::Console().DetachObserver(spdlogObserver);
    delete spdlogObserver;
}

/*
 * Example 6: Module-based Logging
 * 
 * Demonstrates organizing logs by module/component using the notifier parameter.
 */
void example_module_logging()
{
    Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
    Base::Console().AttachObserver(spdlogObserver);
    
    // Different modules can identify themselves
    Base::Console().Message("PartDesign", "Creating new body\n");
    Base::Console().Log("PartDesign", "Applying pad operation: length=10mm\n");
    
    Base::Console().Message("Sketcher", "Creating new sketch\n");
    Base::Console().Log("Sketcher", "Adding constraint: distance=50mm\n");
    
    Base::Console().Message("Mesh", "Importing STL file\n");
    Base::Console().Warning("Mesh", "Mesh contains non-manifold edges\n");
    
    Base::Console().Error("Assembly", "Constraint conflict detected\n");
    
    Base::Console().DetachObserver(spdlogObserver);
    delete spdlogObserver;
}

/*
 * Example 7: Integration with Tag-based Logging
 * 
 * Shows how spdlog works with FreeCAD's tag-based logging system.
 */
void example_tag_based_logging()
{
    Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
    Base::Console().AttachObserver(spdlogObserver);
    
    // Initialize tag-based logging (as per FreeCAD documentation)
    FC_LOG_LEVEL_INIT("MyModule", true, 0, false, true, false);
    
    // Use FreeCAD's tag-based logging macros
    FC_MSG("Module initialized");
    FC_LOG("Processing data...");
    FC_WARN("Performance warning: operation took longer than expected");
    FC_ERR("Fatal error occurred");
    
    // These will be captured by spdlog observer
    
    Base::Console().DetachObserver(spdlogObserver);
    delete spdlogObserver;
}

/*
 * Main function to run all examples
 */
int main()
{
    std::cout << "=== Spdlog Integration Examples ===\n\n";
    
    std::cout << "Example 1: Basic Integration\n";
    example_basic_integration();
    
    std::cout << "\nExample 2: Advanced Logging\n";
    example_advanced_logging();
    
    std::cout << "\nExample 3: Multiple Observers\n";
    example_multiple_observers();
    
    std::cout << "\nExample 4: Performance Monitoring\n";
    example_performance_monitoring();
    
    std::cout << "\nExample 5: Error Tracking\n";
    example_error_tracking();
    
    std::cout << "\nExample 6: Module-based Logging\n";
    example_module_logging();
    
    std::cout << "\nExample 7: Tag-based Logging\n";
    example_tag_based_logging();
    
    std::cout << "\n=== All examples completed ===\n";
    std::cout << "Check 'FreeCAD.log' for spdlog output\n";
    
    return 0;
}
