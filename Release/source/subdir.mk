################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/delay.c \
../source/gpio.c \
../source/led_sequence.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/system.c \
../source/test.c \
../source/touch.c 

C_DEPS += \
./source/delay.d \
./source/gpio.d \
./source/led_sequence.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/system.d \
./source/test.d \
./source/touch.d 

OBJS += \
./source/delay.o \
./source/gpio.o \
./source/led_sequence.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/system.o \
./source/test.o \
./source/touch.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\board" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\source" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\drivers" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\CMSIS" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\utilities" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/delay.d ./source/delay.o ./source/gpio.d ./source/gpio.o ./source/led_sequence.d ./source/led_sequence.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/system.d ./source/system.o ./source/test.d ./source/test.o ./source/touch.d ./source/touch.o

.PHONY: clean-source

