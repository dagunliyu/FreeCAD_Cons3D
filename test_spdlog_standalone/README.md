# Standalone Spdlog Test

This is a simple standalone test to verify that spdlog static library builds and works correctly WITHOUT requiring FreeCAD dependencies.

## Building

```bash
cd test_spdlog_standalone
mkdir build
cd build
cmake -DCMAKE_SOURCE_DIR=/path/to/FreeCAD_Cons3D ..
make
```

## Running

```bash
./test_spdlog_basic
```

## Expected Output

The test will:
1. Create a console logger with color output
2. Create a rotating file logger (test.log)
3. Test all log levels (trace, debug, info, warn, error, critical)
4. Test formatted logging
5. Display success messages

## Files Created

- `test.log` - Log file containing all test messages
- Rotating log files: `test.1.log`, `test.2.log` (if size exceeds 5MB)

## Purpose

This test verifies that:
- ✓ Spdlog compiles as a static library
- ✓ Spdlog links correctly
- ✓ All spdlog features work (logging, formatting, file rotation)
- ✓ No runtime dependencies are needed
