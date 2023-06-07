################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/misc/lv_anim.c \
../Drivers/lvgl/src/misc/lv_anim_timeline.c \
../Drivers/lvgl/src/misc/lv_area.c \
../Drivers/lvgl/src/misc/lv_async.c \
../Drivers/lvgl/src/misc/lv_bidi.c \
../Drivers/lvgl/src/misc/lv_color.c \
../Drivers/lvgl/src/misc/lv_fs.c \
../Drivers/lvgl/src/misc/lv_gc.c \
../Drivers/lvgl/src/misc/lv_ll.c \
../Drivers/lvgl/src/misc/lv_log.c \
../Drivers/lvgl/src/misc/lv_lru.c \
../Drivers/lvgl/src/misc/lv_math.c \
../Drivers/lvgl/src/misc/lv_mem.c \
../Drivers/lvgl/src/misc/lv_printf.c \
../Drivers/lvgl/src/misc/lv_style.c \
../Drivers/lvgl/src/misc/lv_style_gen.c \
../Drivers/lvgl/src/misc/lv_templ.c \
../Drivers/lvgl/src/misc/lv_timer.c \
../Drivers/lvgl/src/misc/lv_tlsf.c \
../Drivers/lvgl/src/misc/lv_txt.c \
../Drivers/lvgl/src/misc/lv_txt_ap.c \
../Drivers/lvgl/src/misc/lv_utils.c 

OBJS += \
./Drivers/lvgl/src/misc/lv_anim.o \
./Drivers/lvgl/src/misc/lv_anim_timeline.o \
./Drivers/lvgl/src/misc/lv_area.o \
./Drivers/lvgl/src/misc/lv_async.o \
./Drivers/lvgl/src/misc/lv_bidi.o \
./Drivers/lvgl/src/misc/lv_color.o \
./Drivers/lvgl/src/misc/lv_fs.o \
./Drivers/lvgl/src/misc/lv_gc.o \
./Drivers/lvgl/src/misc/lv_ll.o \
./Drivers/lvgl/src/misc/lv_log.o \
./Drivers/lvgl/src/misc/lv_lru.o \
./Drivers/lvgl/src/misc/lv_math.o \
./Drivers/lvgl/src/misc/lv_mem.o \
./Drivers/lvgl/src/misc/lv_printf.o \
./Drivers/lvgl/src/misc/lv_style.o \
./Drivers/lvgl/src/misc/lv_style_gen.o \
./Drivers/lvgl/src/misc/lv_templ.o \
./Drivers/lvgl/src/misc/lv_timer.o \
./Drivers/lvgl/src/misc/lv_tlsf.o \
./Drivers/lvgl/src/misc/lv_txt.o \
./Drivers/lvgl/src/misc/lv_txt_ap.o \
./Drivers/lvgl/src/misc/lv_utils.o 

C_DEPS += \
./Drivers/lvgl/src/misc/lv_anim.d \
./Drivers/lvgl/src/misc/lv_anim_timeline.d \
./Drivers/lvgl/src/misc/lv_area.d \
./Drivers/lvgl/src/misc/lv_async.d \
./Drivers/lvgl/src/misc/lv_bidi.d \
./Drivers/lvgl/src/misc/lv_color.d \
./Drivers/lvgl/src/misc/lv_fs.d \
./Drivers/lvgl/src/misc/lv_gc.d \
./Drivers/lvgl/src/misc/lv_ll.d \
./Drivers/lvgl/src/misc/lv_log.d \
./Drivers/lvgl/src/misc/lv_lru.d \
./Drivers/lvgl/src/misc/lv_math.d \
./Drivers/lvgl/src/misc/lv_mem.d \
./Drivers/lvgl/src/misc/lv_printf.d \
./Drivers/lvgl/src/misc/lv_style.d \
./Drivers/lvgl/src/misc/lv_style_gen.d \
./Drivers/lvgl/src/misc/lv_templ.d \
./Drivers/lvgl/src/misc/lv_timer.d \
./Drivers/lvgl/src/misc/lv_tlsf.d \
./Drivers/lvgl/src/misc/lv_txt.d \
./Drivers/lvgl/src/misc/lv_txt_ap.d \
./Drivers/lvgl/src/misc/lv_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/misc/%.o Drivers/lvgl/src/misc/%.su: ../Drivers/lvgl/src/misc/%.c Drivers/lvgl/src/misc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Administrator/STM32CubeIDE/workspace_1.3.0/pullgauge/Drivers/lvgl" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-misc

clean-Drivers-2f-lvgl-2f-src-2f-misc:
	-$(RM) ./Drivers/lvgl/src/misc/lv_anim.d ./Drivers/lvgl/src/misc/lv_anim.o ./Drivers/lvgl/src/misc/lv_anim.su ./Drivers/lvgl/src/misc/lv_anim_timeline.d ./Drivers/lvgl/src/misc/lv_anim_timeline.o ./Drivers/lvgl/src/misc/lv_anim_timeline.su ./Drivers/lvgl/src/misc/lv_area.d ./Drivers/lvgl/src/misc/lv_area.o ./Drivers/lvgl/src/misc/lv_area.su ./Drivers/lvgl/src/misc/lv_async.d ./Drivers/lvgl/src/misc/lv_async.o ./Drivers/lvgl/src/misc/lv_async.su ./Drivers/lvgl/src/misc/lv_bidi.d ./Drivers/lvgl/src/misc/lv_bidi.o ./Drivers/lvgl/src/misc/lv_bidi.su ./Drivers/lvgl/src/misc/lv_color.d ./Drivers/lvgl/src/misc/lv_color.o ./Drivers/lvgl/src/misc/lv_color.su ./Drivers/lvgl/src/misc/lv_fs.d ./Drivers/lvgl/src/misc/lv_fs.o ./Drivers/lvgl/src/misc/lv_fs.su ./Drivers/lvgl/src/misc/lv_gc.d ./Drivers/lvgl/src/misc/lv_gc.o ./Drivers/lvgl/src/misc/lv_gc.su ./Drivers/lvgl/src/misc/lv_ll.d ./Drivers/lvgl/src/misc/lv_ll.o ./Drivers/lvgl/src/misc/lv_ll.su ./Drivers/lvgl/src/misc/lv_log.d ./Drivers/lvgl/src/misc/lv_log.o ./Drivers/lvgl/src/misc/lv_log.su ./Drivers/lvgl/src/misc/lv_lru.d ./Drivers/lvgl/src/misc/lv_lru.o ./Drivers/lvgl/src/misc/lv_lru.su ./Drivers/lvgl/src/misc/lv_math.d ./Drivers/lvgl/src/misc/lv_math.o ./Drivers/lvgl/src/misc/lv_math.su ./Drivers/lvgl/src/misc/lv_mem.d ./Drivers/lvgl/src/misc/lv_mem.o ./Drivers/lvgl/src/misc/lv_mem.su ./Drivers/lvgl/src/misc/lv_printf.d ./Drivers/lvgl/src/misc/lv_printf.o ./Drivers/lvgl/src/misc/lv_printf.su ./Drivers/lvgl/src/misc/lv_style.d ./Drivers/lvgl/src/misc/lv_style.o ./Drivers/lvgl/src/misc/lv_style.su ./Drivers/lvgl/src/misc/lv_style_gen.d ./Drivers/lvgl/src/misc/lv_style_gen.o ./Drivers/lvgl/src/misc/lv_style_gen.su ./Drivers/lvgl/src/misc/lv_templ.d ./Drivers/lvgl/src/misc/lv_templ.o ./Drivers/lvgl/src/misc/lv_templ.su ./Drivers/lvgl/src/misc/lv_timer.d ./Drivers/lvgl/src/misc/lv_timer.o ./Drivers/lvgl/src/misc/lv_timer.su ./Drivers/lvgl/src/misc/lv_tlsf.d ./Drivers/lvgl/src/misc/lv_tlsf.o ./Drivers/lvgl/src/misc/lv_tlsf.su ./Drivers/lvgl/src/misc/lv_txt.d ./Drivers/lvgl/src/misc/lv_txt.o ./Drivers/lvgl/src/misc/lv_txt.su ./Drivers/lvgl/src/misc/lv_txt_ap.d ./Drivers/lvgl/src/misc/lv_txt_ap.o ./Drivers/lvgl/src/misc/lv_txt_ap.su ./Drivers/lvgl/src/misc/lv_utils.d ./Drivers/lvgl/src/misc/lv_utils.o ./Drivers/lvgl/src/misc/lv_utils.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-misc

