################################################################################
# \file Makefile
# \version 1.0
#
# \brief
# Top-level application make file.
#
################################################################################
# \copyright
# Copyright 2018-2022, Cypress Semiconductor Corporation (an Infineon company)
# SPDX-License-Identifier: Apache-2.0
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################


################################################################################
# Basic Configuration
################################################################################

# Type of ModusToolbox Makefile Options include:
#
# COMBINED    -- Top Level Makefile usually for single standalone application
# APPLICATION -- Top Level Makefile usually for multi project application
# PROJECT     -- Project Makefile under Application
#
MTB_TYPE=COMBINED

# Target board/hardware (BSP).
# To change the target, it is recommended to use the Library manager
# ('make modlibs' from command line), which will also update Eclipse IDE launch
# configurations. If TARGET is manually edited, ensure TARGET_<BSP>.mtb with a
# valid URL exists in the application, run 'make getlibs' to fetch BSP contents
# and update or regenerate launch configurations for your IDE.
TARGET=APP_CY8CPROTO-063-BLE

# Name of application (used to derive name of final linked file).
#
# If APPNAME is edited, ensure to update or regenerate launch
# configurations for your IDE.
APPNAME=mtb-ppg-edu-kit-ei

# Name of toolchain to use. Options include:
#
# GCC_ARM -- GCC provided with ModusToolbox IDE
# ARM     -- ARM Compiler (must be installed separately)
# IAR     -- IAR Compiler (must be installed separately)
#
# See also: CY_COMPILER_PATH below
TOOLCHAIN=GCC_ARM

# Default build configuration. Options include:
#
# Debug -- build with minimal optimizations, focus on debugging.
# Release -- build with full optimizations
# Custom -- build with custom configuration, set the optimization flag in CFLAGS
#
# If CONFIG is manually edited, ensure to update or regenerate launch configurations
# for your IDE.
CONFIG=Debug

# If set to "true" or "1", display full command-lines when building.
VERBOSE=


################################################################################
# Advanced Configuration
################################################################################

# Enable optional code that is ordinarily disabled by default.
#
# Available components depend on the specific targeted hardware and firmware
# in use. In general, if you have
#
#    COMPONENTS=foo bar
#
# ... then code in directories named COMPONENT_foo and COMPONENT_bar will be
# added to the build
#
COMPONENTS=

# Like COMPONENTS, but disable optional code that was enabled by default.
DISABLE_COMPONENTS=


#PPG_APP_EI_INFERENCE_HARDCODED_DATA=0
#PPG_APP_EI_INFERENCE_ACQUIRED_DATA=1
#PPG_APP_EI_STREAM_DATA=2

MAIN_APP_TYPE=2

################################################################################
# Edge Impulse Specific and PPG EduKit Platform files
################################################################################

# By default the build system automatically looks in the Makefile's directory
# tree for source code and builds it. The SOURCES variable can be used to
# manually add source code to the build process from a location not searched
# by default, or otherwise not found by the build system.

# Include Edge Impulse specific source files

SOURCES += edge-impulse-sdk/tensorflow/lite/c/common.c 
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/BasicMathFunctions/*.c) 
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/FastMathFunctions/*.c) 
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/StatisticsFunctions/*.c) 
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/*fft*.c) 
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/CommonTables/*.c) 
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/*bit*.c)
SOURCES += $(wildcard tflite-model/*.cpp) 
SOURCES += $(wildcard edge-impulse-sdk/dsp/kissfft/*.cpp) 
SOURCES += $(wildcard edge-impulse-sdk/dsp/dct/*.cpp)
SOURCES += $(wildcard edge-impulse-sdk/tensorflow/lite/kernels/*.cc)
SOURCES += $(wildcard edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) 
SOURCES += $(wildcard edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) 
SOURCES += $(wildcard edge-impulse-sdk/tensorflow/lite/micro/*.cc) 
SOURCES += $(wildcard edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) 
SOURCES += $(wildcard edge-impulse-sdk/tensorflow/lite/core/api/*.cc)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/ActivationFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/ConcatenationFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/ConvolutionFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/FullyConnectedFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/NNSupportFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/PoolingFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/ReshapeFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/SoftmaxFunctions/*.c)
SOURCES += $(wildcard edge-impulse-sdk/porting/infineon-psoc62/*.cpp)
SOURCES += $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/MatrixFunctions/*.c)


# Include PPG EduKit platform specific source files
SOURCES += $(wildcard ../ppg-bsp/src/*.c)
SOURCES += $(wildcard ../ppg-bsp/src/*.cpp)

# Like SOURCES, but for include directories. Value should be paths to
# directories (without a leading -I).

# Include Edge Impulse specific header files
INCLUDES += edge-impulse-sdk/CMSIS/NN/Include/
INCLUDES += edge-impulse-sdk/CMSIS/DSP/PrivateInclude/

# Include PPG EduKit platform specific header files
INCLUDES += ./ppg-bsp/inc

# Ignore edge impulse SDK during auto-discovery since it is included in SOURCES
CY_IGNORE=edge-impulse-sdk

################################################################################
# COMPILER DEFINES
################################################################################

# Add additional defines to the build process (without a leading -D).
DEFINES=

DEFINES += MAIN_APP=$(MAIN_APP_TYPE)
#DEFINES += __STACK_SIZE=0x20000
DEFINES += TF_LITE_DISABLE_X86_NEON=1
#DEFINES += EIDSP_SIGNAL_C_FN_POINTER=1
#DEFINES += EI_C_LINKAGE=1
DEFINES += EI_PORTING_INFINEONPSOC62=1
DEFINES += EI_SENSOR_AQ_STREAM=FILE
DEFINES += EIDSP_USE_CMSIS_DSP
DEFINES += EIDSP_QUANTIZE_FILTERBANK=0
#DEFINES += NDEBUG
DEFINES += EI_CLASSIFIER_TFLITE_ENABLE_CMSIS_NN
DEFINES += ARM_MATH_LOOPUNROLL
DEFINES += EIDSP_LOAD_CMSIS_DSP_SOURCES=1
DEFINES += CY_RETARGET_IO_CONVERT_LF_TO_CRLF

# Select softfp or hardfp floating point. Default is softfp.
VFP_SELECT=

# Additional / custom C compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CFLAGS=
CFLAGS += -Wno-strict-aliasing
CFLAGS += -std=c11
CFLAGS += -lstdc++

# Additional / custom C++ compiler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
CXXFLAGS=

# Additional / custom assembler flags.
#
# NOTE: Includes and defines should use the INCLUDES and DEFINES variable
# above.
ASFLAGS=

# Additional / custom linker flags.
LDFLAGS += -specs=nosys.specs

# Additional / custom libraries to link in to the application.
LDLIBS=

# Path to the linker script to use (if empty, use the default linker script).
LINKER_SCRIPT=

# Custom pre-build commands to run.
PREBUILD=

# Custom post-build commands to run.
POSTBUILD=


################################################################################
# Print built application
################################################################################
ifeq ($(MAIN_APP_TYPE), 0)
    $(info PPG Application PPG_APP_EI_INFERENCE_HARDCODED_DATA)
endif
ifeq ($(MAIN_APP_TYPE), 1)
    $(info PPG Application PPG_APP_EI_INFERENCE_ACQUIRED_DATA)
endif
ifeq ($(MAIN_APP_TYPE), 2)
    $(info PPG Application PPG_APP_EI_STREAM_DATA)
endif

################################################################################
# Paths
################################################################################

# Relative path to the project directory (default is the Makefile's directory).
#
# This controls where automatic source code discovery looks for code.
CY_APP_PATH=

# Relative path to the shared repo location.
#
# All .mtb files have the format, <URI>#<COMMIT>#<LOCATION>. If the <LOCATION> field
# begins with $$ASSET_REPO$$, then the repo is deposited in the path specified by
# the CY_GETLIBS_SHARED_PATH variable. The default location is one directory level
# above the current app directory.
# This is used with CY_GETLIBS_SHARED_NAME variable, which specifies the directory name.
CY_GETLIBS_SHARED_PATH=../

# Directory name of the shared repo location.
#
CY_GETLIBS_SHARED_NAME=mtb_shared

# Absolute path to the compiler's "bin" directory.
#
# The default depends on the selected TOOLCHAIN (GCC_ARM uses the ModusToolbox
# IDE provided compiler by default).
CY_COMPILER_PATH=


# Locate ModusToolbox IDE helper tools folders in default installation
# locations for Windows, Linux, and macOS.
CY_WIN_HOME=$(subst \,/,$(USERPROFILE))
CY_TOOLS_PATHS ?= $(wildcard \
    $(CY_WIN_HOME)/ModusToolbox/tools_* \
    $(HOME)/ModusToolbox/tools_* \
    /Applications/ModusToolbox/tools_*)

# If you install ModusToolbox IDE in a custom location, add the path to its
# "tools_X.Y" folder (where X and Y are the version number of the tools
# folder). Make sure you use forward slashes.
CY_TOOLS_PATHS+=

# Default to the newest installed tools folder, or the users override (if it's
# found).
CY_TOOLS_DIR=$(lastword $(sort $(wildcard $(CY_TOOLS_PATHS))))

ifeq ($(CY_TOOLS_DIR),)
$(error Unable to find any of the available CY_TOOLS_PATHS -- $(CY_TOOLS_PATHS). On Windows, use forward slashes.)
endif

$(info Tools Directory: $(CY_TOOLS_DIR))

include $(CY_TOOLS_DIR)/make/start.mk
