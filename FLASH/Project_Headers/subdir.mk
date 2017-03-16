################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Project_Headers/pushb_inc.s \
../Project_Headers/tpm_inc.s \

S_SRCS_QUOTED += \
"../Project_Headers/pushb_inc.s" \
"../Project_Headers/tpm_inc.s" \

S_DEPS_QUOTED += \
"./Project_Headers/pushb_inc.d" \
"./Project_Headers/tpm_inc.d" \

OBJS += \
./Project_Headers/pushb_inc.o \
./Project_Headers/tpm_inc.o \

S_DEPS += \
./Project_Headers/pushb_inc.d \
./Project_Headers/tpm_inc.d \

OBJS_QUOTED += \
"./Project_Headers/pushb_inc.o" \
"./Project_Headers/tpm_inc.o" \

OBJS_OS_FORMAT += \
./Project_Headers/pushb_inc.o \
./Project_Headers/tpm_inc.o \


# Each subdirectory must supply rules for building sources it contributes
Project_Headers/pushb_inc.o: ../Project_Headers/pushb_inc.s
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Headers/pushb_inc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Headers/pushb_inc.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Headers/tpm_inc.o: ../Project_Headers/tpm_inc.s
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Headers/tpm_inc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Headers/tpm_inc.o"
	@echo 'Finished building: $<'
	@echo ' '


