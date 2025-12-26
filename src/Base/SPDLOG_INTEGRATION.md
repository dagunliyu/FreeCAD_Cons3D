# Spdlog Integration with FreeCAD Console / Spdlog与FreeCAD Console集成

## English Documentation

### Overview

This integration adds [spdlog](https://github.com/gabime/spdlog) - a fast, header-only/compiled C++ logging library - to the FreeCAD_Cons3D project as a static library. The integration is designed with minimal changes to the existing codebase, utilizing the Observer pattern already present in `Base::Console`.

### Key Features

- **Zero Breaking Changes**: All existing Base::Console APIs remain unchanged
- **Observer Pattern**: Spdlog is integrated as a new `ILogger` observer
- **Static Library**: Built as a static library to avoid runtime dependencies
- **Dual Logging**: Can work alongside existing console observers
- **Rich Features**: Access to spdlog's advanced features (structured logging, formatting, etc.)
- **Thread-Safe**: Spdlog provides thread-safe logging out of the box

### Architecture

```
Base::Console (existing)
    ├── ConsoleObserverFile (existing)
    ├── ConsoleObserverStd (existing)
    └── ConsoleObserverSpdlog (NEW)
            └── spdlog::logger (static library)
```

### Integration Details

1. **Location**: `src/3rdParty/spdlog/` - spdlog v1.13.0 as a static library
2. **Bridge Class**: `Base::ConsoleObserverSpdlog` - implements `ILogger` interface
3. **Files Added**:
   - `src/Base/ConsoleObserverSpdlog.h`
   - `src/Base/ConsoleObserverSpdlog.cpp`
   - `tests/src/Base/Console_spdlog.cpp` (unit tests)
   - `src/Base/ConsoleObserverSpdlog_Example.cpp` (usage examples)

### Usage

#### Basic Usage

```cpp
#include <Base/Console.h>
#include <Base/ConsoleObserverSpdlog.h>

// Create and attach spdlog observer
Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
Base::Console().AttachObserver(spdlogObserver);

// All console messages will now be logged through spdlog
Base::Console().Message("Hello, spdlog!\n");
Base::Console().Warning("This is a warning\n");
Base::Console().Error("This is an error\n");

// Cleanup
Base::Console().DetachObserver(spdlogObserver);
delete spdlogObserver;
```

#### Advanced Usage - Direct spdlog Access

```cpp
Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
Base::Console().AttachObserver(spdlogObserver);

// Get direct access to spdlog logger for advanced features
auto logger = spdlogObserver->GetLogger();

// Structured logging
logger->info("User: {}, Action: {}, Status: {}", "john", "login", "success");
logger->warn("CPU: {:.1f}%, Memory: {}MB", 85.5, 2048);
```

### Default Configuration

The default `ConsoleObserverSpdlog` setup includes:
- Console output with color coding (stdout)
- Rotating file output to `FreeCAD.log` (5MB max, 3 files)
- Timestamp format: `[YYYY-MM-DD HH:MM:SS.mmm] [level] [notifier] message`
- All log levels enabled by default

### Log Level Mapping

| Base::Console Level | spdlog Level |
|---------------------|--------------|
| Error               | error        |
| Warning             | warn         |
| Message             | info         |
| Log                 | debug        |
| Critical            | critical     |
| Notification        | info         |

### Building

The integration is automatically built when you build FreeCAD_Cons3D:

```bash
mkdir build
cd build
cmake ..
make
```

Spdlog is compiled as a static library and linked to `FreeCADBase`.

### Testing

Run the unit tests:

```bash
cd build
ctest -R Console_spdlog
```

Or run the standalone example:

```bash
./bin/ConsoleObserverSpdlog_Example
```

### Compatibility

- **Minimum CMake**: 3.16.3 (same as FreeCAD)
- **C++ Standard**: C++11 (same as FreeCAD)
- **spdlog Version**: 1.13.0
- **Thread Safety**: Yes (multi-threaded sinks)

---

## 中文文档

### 概述

本集成将 [spdlog](https://github.com/gabime/spdlog)（一个快速的、仅头文件/编译式 C++ 日志库）作为静态库添加到 FreeCAD_Cons3D 项目中。该集成设计为对现有代码库进行最小化更改，利用了 `Base::Console` 中已经存在的观察者模式。

### 主要特性

- **零破坏性更改**：所有现有的 Base::Console API 保持不变
- **观察者模式**：spdlog 作为新的 `ILogger` 观察者集成
- **静态库**：构建为静态库以避免运行时依赖
- **双重日志**：可以与现有的控制台观察者一起工作
- **丰富功能**：访问 spdlog 的高级功能（结构化日志、格式化等）
- **线程安全**：spdlog 开箱即用提供线程安全的日志记录

### 架构

```
Base::Console (现有)
    ├── ConsoleObserverFile (现有)
    ├── ConsoleObserverStd (现有)
    └── ConsoleObserverSpdlog (新增)
            └── spdlog::logger (静态库)
```

### 集成详情

1. **位置**：`src/3rdParty/spdlog/` - spdlog v1.13.0 作为静态库
2. **桥接类**：`Base::ConsoleObserverSpdlog` - 实现 `ILogger` 接口
3. **新增文件**：
   - `src/Base/ConsoleObserverSpdlog.h`
   - `src/Base/ConsoleObserverSpdlog.cpp`
   - `tests/src/Base/Console_spdlog.cpp`（单元测试）
   - `src/Base/ConsoleObserverSpdlog_Example.cpp`（使用示例）

### 使用方法

#### 基本用法

```cpp
#include <Base/Console.h>
#include <Base/ConsoleObserverSpdlog.h>

// 创建并附加 spdlog 观察者
Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
Base::Console().AttachObserver(spdlogObserver);

// 现在所有控制台消息都将通过 spdlog 记录
Base::Console().Message("你好，spdlog！\n");
Base::Console().Warning("这是一个警告\n");
Base::Console().Error("这是一个错误\n");

// 清理
Base::Console().DetachObserver(spdlogObserver);
delete spdlogObserver;
```

#### 高级用法 - 直接访问 spdlog

```cpp
Base::ConsoleObserverSpdlog* spdlogObserver = new Base::ConsoleObserverSpdlog();
Base::Console().AttachObserver(spdlogObserver);

// 获取对 spdlog logger 的直接访问以使用高级功能
auto logger = spdlogObserver->GetLogger();

// 结构化日志
logger->info("用户: {}, 操作: {}, 状态: {}", "张三", "登录", "成功");
logger->warn("CPU: {:.1f}%, 内存: {}MB", 85.5, 2048);
```

### 默认配置

默认的 `ConsoleObserverSpdlog` 设置包括：
- 带颜色编码的控制台输出（stdout）
- 滚动文件输出到 `FreeCAD.log`（最大 5MB，3 个文件）
- 时间戳格式：`[YYYY-MM-DD HH:MM:SS.mmm] [级别] [通知者] 消息`
- 默认启用所有日志级别

### 日志级别映射

| Base::Console 级别 | spdlog 级别 |
|--------------------|-------------|
| Error              | error       |
| Warning            | warn        |
| Message            | info        |
| Log                | debug       |
| Critical           | critical    |
| Notification       | info        |

### 构建

集成在构建 FreeCAD_Cons3D 时自动构建：

```bash
mkdir build
cd build
cmake ..
make
```

spdlog 编译为静态库并链接到 `FreeCADBase`。

### 测试

运行单元测试：

```bash
cd build
ctest -R Console_spdlog
```

或运行独立示例：

```bash
./bin/ConsoleObserverSpdlog_Example
```

### 兼容性

- **最低 CMake 版本**：3.16.3（与 FreeCAD 相同）
- **C++ 标准**：C++11（与 FreeCAD 相同）
- **spdlog 版本**：1.13.0
- **线程安全**：是（多线程 sinks）

### 设计理念

1. **最小化改动**：不修改任何现有的 Base::Console 代码，只添加新的观察者
2. **可选集成**：用户可以选择是否使用 spdlog，不影响现有功能
3. **观察者模式**：利用已有的设计模式，保持代码整洁
4. **静态链接**：避免动态库依赖问题
5. **向后兼容**：完全兼容现有的日志代码

### 优势

- **高性能**：spdlog 是最快的 C++ 日志库之一
- **异步支持**：可选的异步日志记录提高性能
- **格式化灵活**：支持 fmt 库的强大格式化能力
- **多输出目标**：同时输出到控制台和文件
- **日志轮转**：自动管理日志文件大小和数量
- **线程安全**：多线程环境下安全使用
