# Barrier Linux Compilation Guide

## Exact Steps Performed (What We Actually Did)

This section documents the exact sequence of commands and fixes applied to successfully build Barrier on WSL2/Ubuntu.

### 1. Fixed CMake Version Requirements
Updated minimum CMake version from 3.4 to 3.5 in three files:

**File 1:** `CMakeLists.txt` (line 18)
```cmake
# Changed from:
cmake_minimum_required (VERSION 3.4)
# To:
cmake_minimum_required (VERSION 3.5)
```

**File 2:** `cmake/Version.cmake` (line 1)
```cmake
# Changed from:
cmake_minimum_required (VERSION 3.4)
# To:
cmake_minimum_required (VERSION 3.5)
```

**File 3:** `src/gui/CMakeLists.txt` (line 1)
```cmake
# Changed from:
cmake_minimum_required (VERSION 3.4)
# To:
cmake_minimum_required (VERSION 3.5)
```

### 2. Installed Dependencies
```bash
sudo apt install -y libcurl4-openssl-dev qtbase5-dev qttools5-dev-tools libssl-dev libx11-dev libxtst-dev libxinerama-dev libxss-dev libxi-dev libxrandr-dev libavahi-compat-libdnssd-dev
```

### 3. Fixed Missing Headers
**File 1:** `src/lib/base/String.h`
Added missing header after line 25:
```cpp
#include <stdarg.h>
#include <vector>
#include <cstdint>  // ADDED THIS LINE
```

**File 2:** `src/lib/net/FingerprintData.h`
Added missing header after line 22:
```cpp
#include <string>
#include <vector>
#include <cstdint>  // ADDED THIS LINE
```

### 4. Build
```bash
cd "/mnt/c/D Drive/CAPTAIN/CodeProjects/barrier"
./clean_build.sh
```

### 5. Verify Build Output
```bash
ls -la "/mnt/c/D Drive/CAPTAIN/CodeProjects/barrier/build/bin/"
```
**Files created:**
- `barriers` (12,709,936 bytes) - Server executable
- `barrierc` (10,165,752 bytes) - Client executable
- `integtests` (20,092,176 bytes) - Integration tests
- `unittests` (15,227,792 bytes) - Unit tests

### 6. Test Functionality
```bash
cd "/mnt/c/D Drive/CAPTAIN/CodeProjects/barrier/build/bin"
./barrierc <server-ip>
```
**Result:** ✅ Successfully connected to server

---

## General Compilation Guide

### Prerequisites

#### System Requirements
- Ubuntu/Debian-based Linux distribution
- CMake 4.0+ (installed via snap)
- GCC 13.3.0
- Git

#### Required Dependencies

Install the following packages:

```bash
sudo apt update
sudo apt install -y \
    libcurl4-openssl-dev \
    qtbase5-dev \
    qttools5-dev-tools \
    libssl-dev \
    libx11-dev \
    libxtst-dev \
    libxinerama-dev \
    libxss-dev \
    libxi-dev \
    libxrandr-dev \
    libavahi-compat-libdnssd-dev
```

**Note on Package Names:**
- Use `qtbase5-dev` instead of the deprecated `qt5-default`
- Use `libavahi-compat-libdnssd-dev` instead of `avahi-compat-libdns_sd-dev`

### Source Code Fixes Required

The original Barrier source code requires several fixes to compile with modern toolchains:

#### 1. CMake Minimum Version Updates

**Files to modify:**
- `CMakeLists.txt` (line 18)
- `cmake/Version.cmake` (line 1)
- `src/gui/CMakeLists.txt` (line 1)

**Change:**
```cmake
# FROM:
cmake_minimum_required (VERSION 3.4)

# TO:
cmake_minimum_required (VERSION 3.5)
```

**Reason:** CMake 4.0+ no longer supports compatibility with CMake < 3.5

#### 2. Missing C++ Headers

**File:** `src/lib/base/String.h`

**Add after existing includes:**
```cpp
#include <stdarg.h>
#include <vector>
#include <cstdint>  // ADD THIS LINE
```

**File:** `src/lib/net/FingerprintData.h`

**Add after existing includes:**
```cpp
#include <string>
#include <vector>
#include <cstdint>  // ADD THIS LINE
```

**Reason:** Modern C++ compilers require explicit inclusion of `<cstdint>` for `std::uint8_t` types

### Compilation Process

#### 1. Clone and Navigate
```bash
git clone <barrier-repo-url>
cd barrier
```

#### 2. Initialize Submodules
```bash
git submodule update --init --recursive
```

#### 3. Apply Source Code Fixes
Apply all the fixes mentioned in the "Source Code Fixes Required" section above.

#### 4. Build
```bash
./clean_build.sh
```

**Alternative manual build:**
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Build Output

#### Successful Build Results
- **Location:** `build/bin/`
- **Core executables:**
  - `barriers` (~12.7MB) - Server component
  - `barrierc` (~10.2MB) - Client component
  - `barrier` - GUI application (if Qt build completes)
  - `integtests` - Integration tests
  - `unittests` - Unit tests

#### Expected Warnings
- OpenSSL deprecation warnings (non-critical)
- CMake compatibility warnings (non-critical)
- Clock skew warnings in WSL (non-critical)

### Usage

#### Server Mode
```bash
cd build/bin
./barriers
```

#### Client Mode
```bash
cd build/bin
./barrierc <server-ip-address>
```

#### GUI Mode (if available)
```bash
cd build/bin
./barrier
```

### Troubleshooting

#### Common Issues

1. **Missing Qt5**: Install `qtbase5-dev` instead of `qt5-default`
2. **Missing Avahi**: Use `libavahi-compat-libdnssd-dev` package name
3. **uint8_t errors**: Add `#include <cstdint>` to header files
4. **CMake version errors**: Update minimum version requirements to 3.5
5. **CURL not found**: Install `libcurl4-openssl-dev`

#### Build Environment Notes
- **WSL Users**: No GUI display available by default
- **X11 Required**: For actual mouse/keyboard sharing functionality
- **Network**: Ensure firewall allows Barrier traffic (default port 24800)

### Platform-Specific Notes

#### Windows Build (Alternative)
If building on Windows instead of Linux:
- Requires Visual Studio 2019/2022
- Requires Qt 5.11.1 at `C:\Qt\5.11.1\msvc2017_64`
- Requires Bonjour SDK at `C:\Program Files\Bonjour SDK`
- Use `clean_build.bat` instead of `clean_build.sh`

#### Linux Desktop Environment
For full functionality, Barrier requires:
- X11 or Wayland display server
- Desktop environment (GNOME, KDE, etc.)
- Proper graphics drivers

### Version Information
- **Barrier Version:** 2.4.0
- **Build System:** CMake + Make
- **Compiler:** GCC 13.3.0
- **Target Platform:** Linux x86_64

### Summary of Changes Made
1. Updated CMake minimum version requirements (3 files)
2. Added missing `#include <cstdint>` headers (2 files)
3. Installed correct Linux development packages
4. Used appropriate package names for Ubuntu 24.04+

This guide should enable successful compilation of Barrier on modern Linux systems.