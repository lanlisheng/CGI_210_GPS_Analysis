################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include TouchGFX/target/generated/subdir.mk
-include TouchGFX/target/subdir.mk
-include TouchGFX/gui/src/model/subdir.mk
-include TouchGFX/gui/src/data_collector_screen/subdir.mk
-include TouchGFX/gui/src/containers/subdir.mk
-include TouchGFX/gui/src/common/subdir.mk
-include TouchGFX/generated/texts/src/subdir.mk
-include TouchGFX/generated/images/src/__designer/subdir.mk
-include TouchGFX/generated/images/src/subdir.mk
-include TouchGFX/generated/gui_generated/src/data_collector_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/containers/subdir.mk
-include TouchGFX/generated/gui_generated/src/common/subdir.mk
-include TouchGFX/generated/fonts/src/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/touchgfx/framework/source/platform/hal/simulator/sdl2/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/touchgfx/framework/source/platform/driver/touch/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/simulator/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/gui/src/model/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/gui/src/data_collector_screen/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/gui/src/containers/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/gui/src/common/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/texts/src/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/simulator/src/video/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/simulator/src/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/images/src/__designer/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/images/src/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/gui_generated/src/data_collector_screen/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/gui_generated/src/containers/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/gui_generated/src/common/subdir.mk
-include TouchGFX/build/MINGW32_NT-6.2/generated/fonts/src/subdir.mk
-include TouchGFX/App/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ATK_S1216F8_GPS
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ATK_S1216F8_GPS.elf \

MAP_FILES += \
ATK_S1216F8_GPS.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ATK_S1216F8_GPS.list \


# All Target
all: main-build

# Main-build Target
main-build: ATK_S1216F8_GPS.elf secondary-outputs

# Tool invocations
ATK_S1216F8_GPS.elf ATK_S1216F8_GPS.map: $(OBJS) $(USER_OBJS) E:\Study\ATK_S1216F8_GPS\STM32F767IGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "ATK_S1216F8_GPS.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"E:\Study\ATK_S1216F8_GPS\STM32F767IGTX_FLASH.ld" -Wl,-Map="ATK_S1216F8_GPS.map" -Wl,--gc-sections -static -L"E:\Study\ATK_S1216F8_GPS\Middlewares\ST\touchgfx\lib\core\cortex_m7\gcc" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ATK_S1216F8_GPS.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ATK_S1216F8_GPS.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ATK_S1216F8_GPS.elf ATK_S1216F8_GPS.list ATK_S1216F8_GPS.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
