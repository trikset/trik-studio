# STM32F429I-Disco Makefile for GNU toolchain and openocd
#
# This Makefile fetches the Cube firmware package from ST's' website.
# This includes: CMSIS, STM32 HAL, BSPs, USB drivers and examples.
#
# Usage:
#	make program		Flash the board with OpenOCD
#	make openocd		Start OpenOCD
#	make debug		Start GDB and attach to OpenOCD
#	make dirs		Create subdirs like obj, dep, ..
#
# Copyright	2015 Steffen Vogel, 2016 Roman Belkov, 2017 Stanislav Prikhodko
# License	http://www.gnu.org/licenses/gpl.txt GNU Public License
# Authors	Steffen Vogel <post@steffenvogel.de>
#           Roman Belkov  <roman.belkov@gmail.com>
#           Stanislav Prikhodko <prikhodko-stanislav@yandex.ru>
# Link		http://www.steffenvogel.de

# A name common to all output files (elf, map, hex, bin, lst)
TARGET     = demo

# Take a look into $(CUBE_DIR)/Drivers/BSP for available BSPs
# name needed in upper case and lower case
BOARD      = STM32F429I-Discovery
BOARD_UC   = STM32F429I-Discovery
BOARD_LC   = stm32f429i_discovery
BSP_BASE   = $(BOARD_LC)

OPENOCD_FLAGS = -f board/stm32f429discovery.cfg
GDBFLAGS   =

EXAMPLE    = Examples/GPIO/GPIO_EXTI

# MCU family and type in various capitalizations o_O
MCU_FAMILY = stm32f4xx
MCU_LC     = stm32f429xx
MCU_MC     = STM32F429xx
MCU_UC     = STM32F429ZI

MCU_HAL = $(MCU_FAMILY)_hal

LIBRARIES ?= .

SOURCES_DIR = $(LIBRARIES)/Src
INC_DIR     = $(LIBRARIES)/Include
OBJECTS_DIR = Obj
DEP_DIR     = Dep
SUPPORT_DIR = $(LIBRARIES)/Support
TM_LIBRARIES_DIR = $(LIBRARIES)/TM_LIBRARIES
TM_LIBRARIES_SRC = $(TM_LIBRARIES_DIR)/Src
TM_LIBRARIES_Peripherals = $(TM_LIBRARIES_DIR)/StdPeriph

# path to the ld file 
LDFILE     = $(SUPPORT_DIR)/$(MCU_UC)Tx_FLASH.ld

START_ASM  = $(SUPPORT_DIR)/startup_$(MCU_LC).s

# http://stackoverflow.com/a/12959694
# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))


#CPP_SOURCES := $(notdir $(shell find $(SOURCES_DIR) -name '*.cpp'))

#DEPS    = $(patsubst $(SOURCES_DIR)/%.c, $(DEP_DIR)/%.d, $(SOURCES))

# Basic HAL libraries
#SOURCES += $(MCU_HAL)_rcc.c $(MCU_HAL)_rcc_ex.c $(MCU_HAL).c $(MCU_HAL)_cortex.c $(MCU_HAL)_gpio.c $(MCU_HAL)_pwr_ex.c $(BSP_BASE).c \
           $(MCU_HAL)_dma.c $(MCU_HAL)_dma_ex.c $(MCU_HAL)_dma2d.c $(MCU_HAL)_gpio.c $(MCU_HAL)_ltdc.c $(MCU_HAL)_ltdc_ex.c $(MCU_FAMILY)_ll_fmc.c \
           $(MCU_HAL)_spi.c

#TM_LIBRARIES_INC = $(TM_LIBRARIES_DIR)/Inc

#SOURCES := $(notdir $(call rwildcard,.,*.c))
SOURCES := $(notdir $(call rwildcard,$(SOURCES_DIR),*.c))
SOURCES += $(notdir $(call rwildcard,$(TM_LIBRARIES_SRC),*.c))
SOURCES += $(notdir $(call rwildcard,$(TM_LIBRARIES_Peripherals)/Src,*.c))

SOURCES += $(notdir $(wildcard *.cpp))
SOURCES += $(notdir $(call rwildcard,$(SOURCES_DIR),*.cpp))
SOURCES += $(notdir $(call rwildcard,$(TM_LIBRARIES_SRC),*.cpp))
SOURCES += $(notdir $(call rwildcard,$(TM_LIBRARIES_Peripherals)/Src,*.cpp))
# Directories

# TODO hardcode
OPENOCD_DIR         ?= ~/install/openocd-0.10.0
OPENOCD_BIN_DIR     ?= $(OPENOCD_DIR)/bin
OPENOCD_SCRIPTS_DIR  = $(OPENOCD_DIR)/scripts
OPENOCD             ?= $(OPENOCD_BIN_DIR)/openocd.exe

#CUBE_DIR   = cube
#BSP_DIR    = $(CUBE_DIR)/Drivers/BSP/$(BOARD_UC)
#HAL_DIR    = $(CUBE_DIR)/Drivers/STM32F4xx_HAL_Driver
#$(CUBE_DIR)/Drivers/CMSIS

# $(TM_LIBRARIES_DIR)/CMSIS
CMSIS_DIR  =  $(TM_LIBRARIES_DIR)/CMSIS
DEV_DIR    = $(CMSIS_DIR)/Device/ST/STM32F4xx

# that's it, no need to change anything below this line!

###############################################################################
# Compiler toolchain

PREFIX     = arm-none-eabi
CC         = $(PREFIX)-gcc
CXX        = $(PREFIX)-gcc
AR         = $(PREFIX)-ar
OBJCOPY    = $(PREFIX)-objcopy
OBJDUMP    = $(PREFIX)-objdump
SIZE       = $(PREFIX)-size
GDB        = $(PREFIX)-gdb


###############################################################################
# Options

# Defines
DEFS       = -D$(MCU_MC) -DUSE_STDPERIPH_DRIVER -DKEIL_IDE -DSTM32F429_439xx
#-DUSE_HAL_DRIVER

# Debug specific definitions for semihosting
DEFS       += -DUSE_DBPRINTF

# Include search paths (-I)
#INCS       = -Isrc
INCS       = -I.
INCS      += -I$(INC_DIR)
#INCS      += -I$(BSP_DIR)
INCS      += -I$(CMSIS_DIR)/Include
INCS      += -I$(DEV_DIR)/Include
#INCS      += -I$(HAL_DIR)/Inc
INCS      += -I$(TM_LIBRARIES_DIR)/Include
INCS      += -I$(TM_LIBRARIES_Peripherals)/Include
#INCS      += -I$(CUBE_DIR)/Drivers/CMSIS/Include
#INCS      += -I$(CUBE_DIR)/Drivers/CMSIS/Device/ST/STM32F4xx/Include

# Library search paths
LIBS       = -L$(CMSIS_DIR)/Lib

# Compiler flags
CFLAGS     = -Wall -g -std=c99 -Os
CFLAGS    += -mcpu=cortex-m4 -mthumb
CFLAGS    += -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
CFLAGS    += -ffunction-sections -fdata-sections
CFLAGS    += $(INCS) $(DEFS)

CXXFLAGS   = $(CFLAGS) -std=gnu++11

# Linker flags
LDFLAGS    = -Wl,--gc-sections -Wl,-Map=$(TARGET).map $(LIBS) -T$(LDFILE)

# Enable Semihosting
LDFLAGS   += --specs=rdimon.specs -lc -lrdimon

# Source search paths
VPATH      = .
VPATH     += $(SOURCES_DIR)
#VPATH     += $(BSP_DIR)
VPATH     += $(HAL_DIR)/Src
VPATH     += $(DEV_DIR)/Source/
VPATH     += $(TM_LIBRARIES_SRC)
VPATH     += $(TM_LIBRARIES_Peripherals)/Src

OBJECTS := $(addprefix $(OBJECTS_DIR)/,$(addsuffix .o,$(basename $(SOURCES))))
DEPS    := $(addprefix $(DEP_DIR)/,$(addsuffix .d,$(basename $(SOURCES))))

# Prettify output
V = 0
ifeq ($V, 0)
	Q = @
	P = > /dev/null
endif

###################################################

.PHONY: all dirs program clean # debug template

all: $(TARGET).bin

-include $(DEPS)

dirs: Dep Obj
Dep Obj src:
	@echo "[MKDIR]   $@"
	$Qmkdir -p $@

$(OBJECTS_DIR)/%.o : %.c | dirs
	@echo "[CC]      $(notdir $<)"
	$(CC) $(CFLAGS) -c -o $@ $< -MMD -MF dep/$(*F).d

$(OBJECTS_DIR)/%.o : %.cpp | dirs
	@echo "[CC]      $(notdir $<)"
	$(CXX) $(CXXFLAGS) -c -o $@ $< -MMD -MF dep/$(*F).d

$(TARGET).elf: $(OBJECTS) 
	@echo "[LD]      $(TARGET).elf"
	$(CC) $(CFLAGS) $(LDFLAGS) $(START_ASM) $^ -o $@
	@echo "[OBJDUMP] $(TARGET).lst"
	$Q$(OBJDUMP) -St $(TARGET).elf >$(TARGET).lst
	@echo "[SIZE]    $(TARGET).elf"
	$(SIZE) $(TARGET).elf

$(TARGET).bin: $(TARGET).elf
	@echo "[OBJCOPY] $(TARGET).bin"
	$Q$(OBJCOPY) -O binary $< $@

openocd:
	$(OPENOCD) -s $(OPENOCD_SCRIPTS_DIR) $(OPENOCD_FLAGS)

program: #all
	$(OPENOCD) -s $(OPENOCD_SCRIPTS_DIR) $(OPENOCD_FLAGS) \
	           -c "program $(TARGET).elf verify reset" \
	           -c "shutdown"

# TODO currently does not tested
debug:
	@if ! nc -z localhost 3333; then \
		echo "\n\t[Error] OpenOCD is not running! Start it with: 'make openocd'\n"; exit 1; \
	else \
		$(GDB)  -ex "target extended localhost:3333" \
			-ex "monitor arm semihosting enable" \
			-ex "monitor reset halt" \
			-ex "load" \
			-ex "monitor reset init" \
			$(GDBFLAGS) $(TARGET).elf; \
	fi

clean:
	@echo "$(LIBRARIES)"
	@echo "$(SOURCES)"
	@echo "$(OBJECTS)"
	@echo "[RM]      $(TARGET).bin"; rm -f $(TARGET).bin
	@echo "[RM]      $(TARGET).elf"; rm -f $(TARGET).elf
	@echo "[RM]      $(TARGET).map"; rm -f $(TARGET).map
	@echo "[RM]      $(TARGET).lst"; rm -f $(TARGET).lst
	@echo "[RMDIR]   dep"          ; rm -rf $(DEP_DIR)
	@echo "[RMDIR]   obj"          ; rm -rf $(OBJECTS_DIR)

