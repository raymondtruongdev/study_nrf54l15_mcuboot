# Guide: Add a Pre-Jump Hook to MCUboot

This guide adds a custom hook that executes **immediately before MCUboot jumps to the application**, without modifying the overall MCUboot boot flow.

---

## Step 1 - Update MCUboot CMakeLists.txt

Open: `/opt/nordic/ncs/v3.4.0/bootloader/mcuboot/boot/zephyr/CMakeLists.txt`


Append the following code to the **end of the file**:

```cmake
set(MCUBOOT_HOOK_DIR ${APP_DIR}/mcuboot_hooks)
message(STATUS "APP_DIR            = ${APP_DIR}")
message(STATUS "MCUBOOT_HOOK_DIR  = ${MCUBOOT_HOOK_DIR}")
if(EXISTS "${MCUBOOT_HOOK_DIR}/boot_hooks.c")
    message(STATUS "Found: ${MCUBOOT_HOOK_DIR}/boot_hooks.c")
    target_sources(app PRIVATE
        ${MCUBOOT_HOOK_DIR}/boot_hooks.c
    )
    target_include_directories(app PRIVATE
        ${MCUBOOT_HOOK_DIR}
    )
    target_compile_definitions(app PRIVATE
        CONFIG_MCUBOOT_PRE_JUMP_HOOK
    )
else()
    message(STATUS "Not found: ${MCUBOOT_HOOK_DIR}/boot_hooks.c")
endif()
```

### What this does

- Adds `boot_hooks.c` to the MCUboot build.
- Adds the include path for `boot_hooks.h`.
- Defines `CONFIG_MCUBOOT_PRE_JUMP_HOOK` only when the hook exists.
- Projects without `mcuboot_hooks` continue to build normally.

---

## Step 2 - Update MCUboot main.c

Open:
`opt/nordic/ncs/v3.4.0/bootloader/mcuboot/boot/zephyr/main.c`

### Step 2.1 - Add the header

Near the other `#include` statements, add:

```c
#ifdef CONFIG_MCUBOOT_PRE_JUMP_HOOK
#include "boot_hooks.h"
#endif
```

---

### Step 2.2 - Call the hook before booting the application

Locate:

```c
do_boot(&rsp);
```

Replace it with:

```c
#ifdef CONFIG_MCUBOOT_PRE_JUMP_HOOK
    mcuboot_pre_jump_hook();
#endif

do_boot(&rsp);
```
---
## Directory Structure
Example:

```text
atls/
├── boards/
├── document/
├── mcuboot_hooks/
│   ├── boot_hooks.c
│   └── boot_hooks.h
├── src/
├── sysbuild/
│   ├── mcuboot.conf
├── ATLS_NRF54L15_nrf54l15_cpuapp.overlay
├── CMakeLists.txt
├── prj.conf
├── sysbuild.conf
└── ...
```
---

## Boot Flow
```text
MCUboot
    │
    ▼
Verify Image
    │
    ▼
mcuboot_pre_jump_hook()
    │
    ▼
do_boot(&rsp)
    │
    ▼
Application
```

---

## Advantages

- No modification to the MCUboot boot flow.
- The hook is executed immediately before jumping to the application.
- Projects without `mcuboot_hooks` build normally.
- Only two MCUboot files are modified:
  - `boot/zephyr/CMakeLists.txt`
  - `boot/zephyr/main.c`