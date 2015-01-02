################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FSXP_Proxy.cpp 

LINK_OBJ += \
./FSXP_Proxy.cpp.o 

CPP_DEPS += \
./FSXP_Proxy.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
FSXP_Proxy.cpp.o: ../FSXP_Proxy.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Users/F/Applications/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=156-r2 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ -mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON '-DUSB_MANUFACTURER="Unknown"' '-DUSB_PRODUCT="Arduino Due"' "-IC:/Users/F/Applications/Arduino/hardware/arduino/sam/system/libsam" "-IC:/Users/F/Applications/Arduino/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Users/F/Applications/Arduino/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Users\F\Applications\Arduino\hardware\arduino\sam\cores\arduino" -I"C:\Users\F\Applications\Arduino\hardware\arduino\sam\variants\arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


