################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F7xx_HAL_Driver/subdir.mk
-include Drivers/Components/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/subdir.mk
-include Application/User/gui/subdir.mk
-include Application/User/generated/subdir.mk
-include Application/User/TouchGFX/target/generated/subdir.mk
-include Application/User/TouchGFX/target/subdir.mk
-include Application/User/TouchGFX/App/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/Core/subdir.mk
-include subdir.mk
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
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
hw01_calc.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
hw01_calc.list \

OBJCOPY_BIN += \
hw01_calc.bin \


# All Target
all: hw01_calc.elf secondary-outputs

# Tool invocations
hw01_calc.elf: $(OBJS) $(USER_OBJS) D:\USER\desktop\floating\projectS\MCU\ARM\stm32f7_discovery\embeded_system_lab\hw01_calc\STM32CubeIDE\STM32F746NGHX_FLASH.ld
	arm-none-eabi-g++ -o "hw01_calc.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"D:\USER\desktop\floating\projectS\MCU\ARM\stm32f7_discovery\embeded_system_lab\hw01_calc\STM32CubeIDE\STM32F746NGHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="hw01_calc.map" -Wl,--gc-sections -static -LD:/USER/desktop/floating/projectS/MCU/ARM/stm32f7_discovery/embeded_system_lab/hw01_calc/Middlewares/ST/touchgfx/lib/core/cortex_m7/gcc --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

hw01_calc.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "hw01_calc.list"
	@echo 'Finished building: $@'
	@echo ' '

hw01_calc.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "hw01_calc.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
