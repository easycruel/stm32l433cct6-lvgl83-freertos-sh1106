################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/extra/libs/qrcode/lv_qrcode.c \
../Drivers/lvgl/src/extra/libs/qrcode/qrcodegen.c 

OBJS += \
./Drivers/lvgl/src/extra/libs/qrcode/lv_qrcode.o \
./Drivers/lvgl/src/extra/libs/qrcode/qrcodegen.o 

C_DEPS += \
./Drivers/lvgl/src/extra/libs/qrcode/lv_qrcode.d \
./Drivers/lvgl/src/extra/libs/qrcode/qrcodegen.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/extra/libs/qrcode/%.o Drivers/lvgl/src/extra/libs/qrcode/%.su: ../Drivers/lvgl/src/extra/libs/qrcode/%.c Drivers/lvgl/src/extra/libs/qrcode/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.3.0/pullgauge/Drivers/lvgl" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-libs-2f-qrcode

clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-libs-2f-qrcode:
	-$(RM) ./Drivers/lvgl/src/extra/libs/qrcode/lv_qrcode.d ./Drivers/lvgl/src/extra/libs/qrcode/lv_qrcode.o ./Drivers/lvgl/src/extra/libs/qrcode/lv_qrcode.su ./Drivers/lvgl/src/extra/libs/qrcode/qrcodegen.d ./Drivers/lvgl/src/extra/libs/qrcode/qrcodegen.o ./Drivers/lvgl/src/extra/libs/qrcode/qrcodegen.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-libs-2f-qrcode

