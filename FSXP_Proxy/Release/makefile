################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/variant/subdir.mk
-include arduino/core/avr/subdir.mk
-include arduino/core/USB/subdir.mk
-include arduino/core/subdir.mk
-include Libraries/aJson-master/utility/subdir.mk
-include Libraries/aJson-master/subdir.mk
-include Libraries/Timer-master/subdir.mk
-include Libraries/SPI/subdir.mk
-include Libraries/SD/src/utility/subdir.mk
-include Libraries/SD/src/subdir.mk
-include Libraries/Ethernet/src/utility/subdir.mk
-include Libraries/Ethernet/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/arduino.ar \

ELF += \
FSXP_Proxy.elf \

EEP += \
FSXP_Proxy.eep \

FLASH_IMAGE += \
FSXP_Proxy.bin \


# All Target
all: FSXP_Proxy

# Tool invocations
FSXP_Proxy: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Users/F/Applications/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-size" -A "C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/FSXP_Proxy.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Users/F/Applications/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-ar" rcs "C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

FSXP_Proxy.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Users/F/Applications/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -Os -Wl,--gc-sections -mcpu=cortex-m3 "-T/C:/Users/F/Applications/Arduino/hardware/arduino/sam/variants/arduino_due_x/linker_scripts/gcc/flash.ld" "-Wl,-Map,C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/FSXP_Proxy.map" -o "C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/FSXP_Proxy.elf" "-LC:/Users/F/git/FSXP_Project/FSXP_Proxy/Release" -lm -lgcc -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group "C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/arduino/syscalls_sam3.c.o"   $(LINK_OBJ) $(AR)  "/C:/Users/F/Applications/Arduino/hardware/arduino/sam/variants/arduino_due_x/libsam_sam3x8e_gcc_rel.a" "C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/arduino.ar" -Wl,--end-group
	@echo 'Finished building: $@'
	@echo ' '

FSXP_Proxy.eep: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

FSXP_Proxy.bin: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:/Users/F/Applications/Arduino/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-objcopy" -O binary "C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/FSXP_Proxy.elf" "C:/Users/F/git/FSXP_Project/FSXP_Proxy/Release/FSXP_Proxy.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(SIZEDUMMY)$(ELF)$(CPP_DEPS) FSXP_Proxy
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
