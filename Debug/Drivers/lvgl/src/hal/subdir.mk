################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/hal/lv_hal_disp.c \
../Drivers/lvgl/src/hal/lv_hal_indev.c \
../Drivers/lvgl/src/hal/lv_hal_tick.c 

OBJS += \
./Drivers/lvgl/src/hal/lv_hal_disp.o \
./Drivers/lvgl/src/hal/lv_hal_indev.o \
./Drivers/lvgl/src/hal/lv_hal_tick.o 

C_DEPS += \
./Drivers/lvgl/src/hal/lv_hal_disp.d \
./Drivers/lvgl/src/hal/lv_hal_indev.d \
./Drivers/lvgl/src/hal/lv_hal_tick.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/hal/%.o Drivers/lvgl/src/hal/%.su: ../Drivers/lvgl/src/hal/%.c Drivers/lvgl/src/hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.3.0/pullgauge/Drivers/lvgl" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-hal

clean-Drivers-2f-lvgl-2f-src-2f-hal:
	-$(RM) ./Drivers/lvgl/src/hal/lv_hal_disp.d ./Drivers/lvgl/src/hal/lv_hal_disp.o ./Drivers/lvgl/src/hal/lv_hal_disp.su ./Drivers/lvgl/src/hal/lv_hal_indev.d ./Drivers/lvgl/src/hal/lv_hal_indev.o ./Drivers/lvgl/src/hal/lv_hal_indev.su ./Drivers/lvgl/src/hal/lv_hal_tick.d ./Drivers/lvgl/src/hal/lv_hal_tick.o ./Drivers/lvgl/src/hal/lv_hal_tick.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-hal

