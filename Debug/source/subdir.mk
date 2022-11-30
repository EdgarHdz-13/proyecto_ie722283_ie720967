################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/BMI160_i2c.c \
../source/FTM_pwm.c \
../source/GPIO_ctrl.c \
../source/LCD_nokia.c \
../source/LCD_nokia_images.c \
../source/MUSIC_album.c \
../source/MUSIC_gen.c \
../source/NVIC.c \
../source/SPI.c \
../source/Tamagotchi_char.c \
../source/Tamagotchi_skin.c \
../source/i2c_tools.c \
../source/mahony.c \
../source/main.c \
../source/semihost_hardfault.c 

OBJS += \
./source/BMI160_i2c.o \
./source/FTM_pwm.o \
./source/GPIO_ctrl.o \
./source/LCD_nokia.o \
./source/LCD_nokia_images.o \
./source/MUSIC_album.o \
./source/MUSIC_gen.o \
./source/NVIC.o \
./source/SPI.o \
./source/Tamagotchi_char.o \
./source/Tamagotchi_skin.o \
./source/i2c_tools.o \
./source/mahony.o \
./source/main.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/BMI160_i2c.d \
./source/FTM_pwm.d \
./source/GPIO_ctrl.d \
./source/LCD_nokia.d \
./source/LCD_nokia_images.d \
./source/MUSIC_album.d \
./source/MUSIC_gen.d \
./source/NVIC.d \
./source/SPI.d \
./source/Tamagotchi_char.d \
./source/Tamagotchi_skin.d \
./source/i2c_tools.d \
./source/mahony.d \
./source/main.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Embebidos 2\Tareas\PROYECTO\board" -I"C:\Embebidos 2\Tareas\PROYECTO\source" -I"C:\Embebidos 2\Tareas\PROYECTO\freertos\freertos_kernel\include" -I"C:\Embebidos 2\Tareas\PROYECTO\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Embebidos 2\Tareas\PROYECTO\drivers" -I"C:\Embebidos 2\Tareas\PROYECTO\device" -I"C:\Embebidos 2\Tareas\PROYECTO\CMSIS" -I"C:\Embebidos 2\Tareas\PROYECTO\component\uart" -I"C:\Embebidos 2\Tareas\PROYECTO\component\serial_manager" -I"C:\Embebidos 2\Tareas\PROYECTO\utilities" -I"C:\Embebidos 2\Tareas\PROYECTO\component\lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


