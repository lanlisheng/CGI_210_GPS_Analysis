################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/data_collector_screen/Data_CollectorPresenter.cpp \
../TouchGFX/gui/src/data_collector_screen/Data_CollectorView.cpp 

OBJS += \
./TouchGFX/gui/src/data_collector_screen/Data_CollectorPresenter.o \
./TouchGFX/gui/src/data_collector_screen/Data_CollectorView.o 

CPP_DEPS += \
./TouchGFX/gui/src/data_collector_screen/Data_CollectorPresenter.d \
./TouchGFX/gui/src/data_collector_screen/Data_CollectorView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/data_collector_screen/%.o TouchGFX/gui/src/data_collector_screen/%.su: ../TouchGFX/gui/src/data_collector_screen/%.cpp TouchGFX/gui/src/data_collector_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-data_collector_screen

clean-TouchGFX-2f-gui-2f-src-2f-data_collector_screen:
	-$(RM) ./TouchGFX/gui/src/data_collector_screen/Data_CollectorPresenter.d ./TouchGFX/gui/src/data_collector_screen/Data_CollectorPresenter.o ./TouchGFX/gui/src/data_collector_screen/Data_CollectorPresenter.su ./TouchGFX/gui/src/data_collector_screen/Data_CollectorView.d ./TouchGFX/gui/src/data_collector_screen/Data_CollectorView.o ./TouchGFX/gui/src/data_collector_screen/Data_CollectorView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-data_collector_screen

