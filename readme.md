# Quantum Mechanical Keyboard Firmware

Personal [fork}(https://github.com/qmk/qmk_firmware) contains only relevant keyboards and keymaps
 
## TL;DR

1. Install qmk `curl -fsSL https://install.qmk.fm | sh`
2. Configure qmk `qmk setup` 
3. Compile `qmk compile -kb ferris/0_2/high -km mini-ryoku`
4. Flash `qmk flash XXX.bin`



## Trouble shooting

### fatal error: chlib.h: No such file or directory

fixed by
```shell
$nvim keyboards/ferris/0_2/rules.mk

EXTRAINCDIRS += $(CHIBIOS)/os/oslib/include
```


```shell
pentan 17:00 ➜  qmk_firmware git:(master) ✗ qmk compile -kb ferris/0_2/high -km mini-ryoku
Ψ Compiling keymap with gmake -r -R -f builddefs/build_keyboard.mk -s KEYBOARD=ferris/0_2/high KEYMAP=mini-ryoku KEYBOARD_FILESAFE=ferris_0_2_high TARGET=ferris_0_2_high_mini-ryoku VERBOSE=false COLOR=true SILENT=false QMK_BIN="qmk"


Generating: .build/obj_ferris_0_2_high_mini-ryoku/src/info_deps.d                                   [OK]
arm-none-eabi-gcc (crosstool-NG 1.27.0.82_7f9d704 - qmk/qmk_toolchains @ a55a2b0) 15.2.0
Copyright (C) 2025 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Generating: .build/obj_ferris_0_2_high_mini-ryoku/src/info_config.h                                 [OK]
Generating: .build/obj_ferris_0_2_high_mini-ryoku/src/default_keyboard.c                            [OK]
Generating: .build/obj_ferris_0_2_high_mini-ryoku/src/default_keyboard.h                            [OK]
Compiling: keyboards/ferris/0_2/matrix.c                                                           In file included from ./lib/chibios/os/hal/osal/rt-nil/osal.h:32,
                 from ./lib/chibios/os/hal/include/hal.h:30,
                 from platforms/chibios/gpio.h:18,
                 from platforms/gpio.h:21,
                 from quantum/matrix.h:22,
                 from keyboards/ferris/0_2/matrix.c:26:
./lib/chibios/os/rt/include/ch.h:125:10: fatal error: chlib.h: No such file or directory
  125 | #include "chlib.h"
      |          ^~~~~~~~~
compilation terminated.
 [ERRORS]
 |
 |
 |

gmake: *** [builddefs/common_rules.mk:362: .build/obj_ferris_0_2_high_mini-ryoku/matrix.o] 
```