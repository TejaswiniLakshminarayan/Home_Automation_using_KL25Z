################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/TSI.c \
../source/cbfifo.c \
../source/colors.c \
../source/commandline.c \
../source/home_state.c \
../source/i2c.c \
../source/led.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sht21.c \
../source/sysclock.c \
../source/test_cbfifo.c \
../source/timer_systick.c \
../source/uart.c 

OBJS += \
./source/TSI.o \
./source/cbfifo.o \
./source/colors.o \
./source/commandline.o \
./source/home_state.o \
./source/i2c.o \
./source/led.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sht21.o \
./source/sysclock.o \
./source/test_cbfifo.o \
./source/timer_systick.o \
./source/uart.o 

C_DEPS += \
./source/TSI.d \
./source/cbfifo.d \
./source/colors.d \
./source/commandline.d \
./source/home_state.d \
./source/i2c.d \
./source/led.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sht21.d \
./source/sysclock.d \
./source/test_cbfifo.d \
./source/timer_systick.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"C:\Users\Tejas\Documents\MCUXpressoIDE_11.2.0_4120\workspace12\MKL25Z128xxx4_Project\board" -I"C:\Users\Tejas\Documents\MCUXpressoIDE_11.2.0_4120\workspace12\MKL25Z128xxx4_Project\source" -I"C:\Users\Tejas\Documents\MCUXpressoIDE_11.2.0_4120\workspace12\MKL25Z128xxx4_Project" -I"C:\Users\Tejas\Documents\MCUXpressoIDE_11.2.0_4120\workspace12\MKL25Z128xxx4_Project\drivers" -I"C:\Users\Tejas\Documents\MCUXpressoIDE_11.2.0_4120\workspace12\MKL25Z128xxx4_Project\CMSIS" -I"C:\Users\Tejas\Documents\MCUXpressoIDE_11.2.0_4120\workspace12\MKL25Z128xxx4_Project\utilities" -I"C:\Users\Tejas\Documents\MCUXpressoIDE_11.2.0_4120\workspace12\MKL25Z128xxx4_Project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


