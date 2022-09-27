################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/test.c 

C_DEPS += \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/test.d 

OBJS += \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/test.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\board" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\source" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\drivers" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\CMSIS" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\utilities" -I"D:\CU BOULDER\Coursework\Sem 1 - PES\test\startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/test.d ./source/test.o

.PHONY: clean-source

