################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/containers/CompanyInfo.cpp \
../TouchGFX/gui/src/containers/DataCollect_Element.cpp \
../TouchGFX/gui/src/containers/LeftBar.cpp \
../TouchGFX/gui/src/containers/TableHead.cpp 

OBJS += \
./TouchGFX/gui/src/containers/CompanyInfo.o \
./TouchGFX/gui/src/containers/DataCollect_Element.o \
./TouchGFX/gui/src/containers/LeftBar.o \
./TouchGFX/gui/src/containers/TableHead.o 

CPP_DEPS += \
./TouchGFX/gui/src/containers/CompanyInfo.d \
./TouchGFX/gui/src/containers/DataCollect_Element.d \
./TouchGFX/gui/src/containers/LeftBar.d \
./TouchGFX/gui/src/containers/TableHead.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/containers/%.o TouchGFX/gui/src/containers/%.su: ../TouchGFX/gui/src/containers/%.cpp TouchGFX/gui/src/containers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-containers

clean-TouchGFX-2f-gui-2f-src-2f-containers:
	-$(RM) ./TouchGFX/gui/src/containers/CompanyInfo.d ./TouchGFX/gui/src/containers/CompanyInfo.o ./TouchGFX/gui/src/containers/CompanyInfo.su ./TouchGFX/gui/src/containers/DataCollect_Element.d ./TouchGFX/gui/src/containers/DataCollect_Element.o ./TouchGFX/gui/src/containers/DataCollect_Element.su ./TouchGFX/gui/src/containers/LeftBar.d ./TouchGFX/gui/src/containers/LeftBar.o ./TouchGFX/gui/src/containers/LeftBar.su ./TouchGFX/gui/src/containers/TableHead.d ./TouchGFX/gui/src/containers/TableHead.o ./TouchGFX/gui/src/containers/TableHead.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-containers

