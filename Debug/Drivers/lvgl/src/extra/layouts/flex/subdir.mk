################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/extra/layouts/flex/lv_flex.c 

OBJS += \
./Drivers/lvgl/src/extra/layouts/flex/lv_flex.o 

C_DEPS += \
./Drivers/lvgl/src/extra/layouts/flex/lv_flex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/extra/layouts/flex/%.o Drivers/lvgl/src/extra/layouts/flex/%.su: ../Drivers/lvgl/src/extra/layouts/flex/%.c Drivers/lvgl/src/extra/layouts/flex/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.3.0/pullgauge/Drivers/lvgl" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-layouts-2f-flex

clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-layouts-2f-flex:
	-$(RM) ./Drivers/lvgl/src/extra/layouts/flex/lv_flex.d ./Drivers/lvgl/src/extra/layouts/flex/lv_flex.o ./Drivers/lvgl/src/extra/layouts/flex/lv_flex.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-layouts-2f-flex

