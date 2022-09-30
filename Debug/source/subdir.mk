################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/FTM_pwm.c \
../source/PWM.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/FTM_pwm.d \
./source/PWM.d \
./source/semihost_hardfault.d 

OBJS += \
./source/FTM_pwm.o \
./source/PWM.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\board" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\source" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\drivers" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\device" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\CMSIS" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\component\uart" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\component\serial_manager" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\utilities" -I"C:\Users\Edgar\Documents\MCUXpressoIDE_11.6.0_8187\Embebidos 2\Tareas\Proyecto_Embebidos_2\component\lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/FTM_pwm.d ./source/FTM_pwm.o ./source/PWM.d ./source/PWM.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

