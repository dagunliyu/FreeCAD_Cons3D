# Spdlog Integration Quick Start Guide
# Spdlog 集成快速入门指南

## English Version

### What is spdlog?

Spdlog is a very fast, header-only/compiled C++ logging library. It provides:
- Very fast performance
- Rich formatting capabilities
- Multiple output targets (console, file, etc.)
- Thread-safe logging
- Rotating log files
- Multiple log levels

### Integration Summary

This integration adds spdlog v1.13.0 to FreeCAD_Cons3D as a **static library** with **zero breaking changes** to existing code.

### Key Points

✓ **No code changes required** - All existing Base::Console APIs work unchanged
✓ **Observer pattern** - Spdlog integrated as new ILogger observer  
✓ **Static library** - No runtime dependencies
✓ **Optional** - Can be used alongside existing console observers
✓ **Thread-safe** - Safe for multi-threaded applications

### Quick Start

#### 1. Basic Usage (3 lines of code)

```cpp
#include <Base/Console.h>
#include <Base/ConsoleObserverSpdlog.h>

// 1. Create observer
Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();

// 2. Attach to console
Base::Console().AttachObserver(spdlogObserver);

// 3. Use normally - all messages now logged by spdlog!
Base::Console().Message("Hello, spdlog!\n");
Base::Console().Warning("This is a warning\n");
Base::Console().Error("Error message\n");

// Cleanup when done
Base::Console().DetachObserver(spdlogObserver);
delete spdlogObserver;
```

#### 2. Advanced Usage - Direct spdlog Access

```cpp
Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
Base::Console().AttachObserver(spdlogObserver);

// Get spdlog logger for advanced features
auto logger = spdlogObserver->GetLogger();

// Structured logging with parameters
logger->info("User: {}, Action: {}, Result: {}", "john", "save", "success");
logger->warn("CPU: {:.1f}%, Memory: {}MB", 85.5, 2048);
logger->error("Error code: {}, Message: {}", -1, "File not found");
```

#### 3. Default Configuration

When you create `ConsoleObserverSpdlog`, it automatically:
- Outputs to console with colors
- Creates rotating log file `FreeCAD.log` (5MB max, 3 files)
- Includes timestamps, log levels, and notifier names
- Enables all log levels

#### 4. What Gets Logged?

All these Base::Console calls are automatically logged:
```cpp
Base::Console().Message("msg");      // → spdlog info level
Base::Console().Warning("warn");     // → spdlog warn level  
Base::Console().Error("err");        // → spdlog error level
Base::Console().Log("log");          // → spdlog debug level
Base::Console().Critical("crit");    // → spdlog critical level
```

### Files Added

```
src/3rdParty/spdlog/              # spdlog v1.13.0 library
src/Base/ConsoleObserverSpdlog.h  # Bridge class header
src/Base/ConsoleObserverSpdlog.cpp # Bridge class implementation
tests/src/Base/Console_spdlog.cpp # Unit tests
src/Base/ConsoleObserverSpdlog_Example.cpp # Usage examples
src/Base/SPDLOG_INTEGRATION.md   # Detailed documentation
```

### Testing

#### Run Standalone Test
```bash
cd test_spdlog_standalone
mkdir build && cd build
cmake -DCMAKE_SOURCE_DIR=../.. ..
make
./test_spdlog_basic
```

#### Run Unit Tests (requires full FreeCAD build)
```bash
cd build
ctest -R Console_spdlog
```

### Examples

See `src/Base/ConsoleObserverSpdlog_Example.cpp` for 7 detailed usage examples:
1. Basic Integration
2. Advanced Logging
3. Multiple Observers
4. Performance Monitoring
5. Error Tracking
6. Module-based Logging
7. Tag-based Logging

### When to Use

**Use spdlog when you need:**
- High-performance logging
- Structured log data
- Advanced formatting
- Log file rotation
- Multiple output targets
- Thread-safe logging

**Continue using Base::Console when you need:**
- Simple message output
- GUI integration
- Python integration
- Existing code compatibility

---

## 中文版本

### 什么是 spdlog？

Spdlog 是一个非常快速的、仅头文件/编译式 C++ 日志库。它提供：
- 极快的性能
- 丰富的格式化功能
- 多种输出目标（控制台、文件等）
- 线程安全的日志记录
- 滚动日志文件
- 多个日志级别

### 集成概要

本集成将 spdlog v1.13.0 作为**静态库**添加到 FreeCAD_Cons3D，对现有代码**零破坏性更改**。

### 关键点

✓ **无需更改代码** - 所有现有的 Base::Console API 保持不变
✓ **观察者模式** - spdlog 作为新的 ILogger 观察者集成
✓ **静态库** - 无运行时依赖
✓ **可选** - 可以与现有控制台观察者一起使用
✓ **线程安全** - 适用于多线程应用程序

### 快速开始

#### 1. 基本用法（3 行代码）

```cpp
#include <Base/Console.h>
#include <Base/ConsoleObserverSpdlog.h>

// 1. 创建观察者
Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();

// 2. 附加到控制台
Base::Console().AttachObserver(spdlogObserver);

// 3. 正常使用 - 所有消息现在都由 spdlog 记录！
Base::Console().Message("你好，spdlog！\n");
Base::Console().Warning("这是一个警告\n");
Base::Console().Error("错误消息\n");

// 完成后清理
Base::Console().DetachObserver(spdlogObserver);
delete spdlogObserver;
```

#### 2. 高级用法 - 直接访问 spdlog

```cpp
Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
Base::Console().AttachObserver(spdlogObserver);

// 获取 spdlog logger 以使用高级功能
auto logger = spdlogObserver->GetLogger();

// 结构化日志记录与参数
logger->info("用户: {}, 操作: {}, 结果: {}", "张三", "保存", "成功");
logger->warn("CPU: {:.1f}%, 内存: {}MB", 85.5, 2048);
logger->error("错误代码: {}, 消息: {}", -1, "文件未找到");
```

#### 3. 默认配置

当您创建 `ConsoleObserverSpdlog` 时，它会自动：
- 输出到带颜色的控制台
- 创建滚动日志文件 `FreeCAD.log`（最大 5MB，3 个文件）
- 包含时间戳、日志级别和通知者名称
- 启用所有日志级别

#### 4. 记录什么？

所有这些 Base::Console 调用都会自动记录：
```cpp
Base::Console().Message("msg");      // → spdlog info 级别
Base::Console().Warning("warn");     // → spdlog warn 级别
Base::Console().Error("err");        // → spdlog error 级别
Base::Console().Log("log");          // → spdlog debug 级别
Base::Console().Critical("crit");    // → spdlog critical 级别
```

### 添加的文件

```
src/3rdParty/spdlog/              # spdlog v1.13.0 库
src/Base/ConsoleObserverSpdlog.h  # 桥接类头文件
src/Base/ConsoleObserverSpdlog.cpp # 桥接类实现
tests/src/Base/Console_spdlog.cpp # 单元测试
src/Base/ConsoleObserverSpdlog_Example.cpp # 使用示例
src/Base/SPDLOG_INTEGRATION.md   # 详细文档
```

### 测试

#### 运行独立测试
```bash
cd test_spdlog_standalone
mkdir build && cd build
cmake -DCMAKE_SOURCE_DIR=../.. ..
make
./test_spdlog_basic
```

#### 运行单元测试（需要完整的 FreeCAD 构建）
```bash
cd build
ctest -R Console_spdlog
```

### 示例

查看 `src/Base/ConsoleObserverSpdlog_Example.cpp` 获取 7 个详细使用示例：
1. 基本集成
2. 高级日志记录
3. 多个观察者
4. 性能监控
5. 错误跟踪
6. 基于模块的日志记录
7. 基于标签的日志记录

### 何时使用

**使用 spdlog 当您需要：**
- 高性能日志记录
- 结构化日志数据
- 高级格式化
- 日志文件轮转
- 多个输出目标
- 线程安全的日志记录

**继续使用 Base::Console 当您需要：**
- 简单的消息输出
- GUI 集成
- Python 集成
- 现有代码兼容性

---

## Additional Resources / 其他资源

- **Detailed Documentation**: `src/Base/SPDLOG_INTEGRATION.md`
- **Usage Examples**: `src/Base/ConsoleObserverSpdlog_Example.cpp`
- **Unit Tests**: `tests/src/Base/Console_spdlog.cpp`
- **Spdlog Official Docs**: https://github.com/gabime/spdlog
