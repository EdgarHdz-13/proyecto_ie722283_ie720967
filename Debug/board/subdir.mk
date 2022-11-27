################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\board" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\source" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\freertos\freertos_kernel\include" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\drivers" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\device" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\CMSIS" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\component\uart" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\component\serial_manager" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\utilities" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_embebidos_2\component\lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/peripherals.d ./board/peripherals.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

