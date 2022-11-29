################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
<<<<<<< HEAD
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\DimensionB\SE II\PROYECTO\board" -I"C:\DimensionB\SE II\PROYECTO\source" -I"C:\DimensionB\SE II\PROYECTO\freertos\freertos_kernel\include" -I"C:\DimensionB\SE II\PROYECTO\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\DimensionB\SE II\PROYECTO\drivers" -I"C:\DimensionB\SE II\PROYECTO\device" -I"C:\DimensionB\SE II\PROYECTO\CMSIS" -I"C:\DimensionB\SE II\PROYECTO\component\uart" -I"C:\DimensionB\SE II\PROYECTO\component\serial_manager" -I"C:\DimensionB\SE II\PROYECTO\utilities" -I"C:\DimensionB\SE II\PROYECTO\component\lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
=======
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Embebidos 2\Tareas\PROYECTO\board" -I"C:\Embebidos 2\Tareas\PROYECTO\source" -I"C:\Embebidos 2\Tareas\PROYECTO\freertos\freertos_kernel\include" -I"C:\Embebidos 2\Tareas\PROYECTO\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Embebidos 2\Tareas\PROYECTO\drivers" -I"C:\Embebidos 2\Tareas\PROYECTO\device" -I"C:\Embebidos 2\Tareas\PROYECTO\CMSIS" -I"C:\Embebidos 2\Tareas\PROYECTO\component\uart" -I"C:\Embebidos 2\Tareas\PROYECTO\component\serial_manager" -I"C:\Embebidos 2\Tareas\PROYECTO\utilities" -I"C:\Embebidos 2\Tareas\PROYECTO\component\lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
>>>>>>> main
	@echo 'Finished building: $<'
	@echo ' '


