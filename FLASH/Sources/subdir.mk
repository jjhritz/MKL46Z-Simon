################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/global.c" \
"../Sources/gpio.c" \
"../Sources/led.c" \
"../Sources/main.c" \
"../Sources/port.c" \
"../Sources/rand.c" \
"../Sources/sim.c" \
"../Sources/simon.c" \
"../Sources/systick.c" \

C_SRCS += \
../Sources/global.c \
../Sources/gpio.c \
../Sources/led.c \
../Sources/main.c \
../Sources/port.c \
../Sources/rand.c \
../Sources/sim.c \
../Sources/simon.c \
../Sources/systick.c \

S_SRCS += \
../Sources/pushb.s \
../Sources/tpm.s \

S_SRCS_QUOTED += \
"../Sources/pushb.s" \
"../Sources/tpm.s" \

S_DEPS_QUOTED += \
"./Sources/pushb.d" \
"./Sources/tpm.d" \

OBJS += \
./Sources/global.o \
./Sources/gpio.o \
./Sources/led.o \
./Sources/main.o \
./Sources/port.o \
./Sources/pushb.o \
./Sources/rand.o \
./Sources/sim.o \
./Sources/simon.o \
./Sources/systick.o \
./Sources/tpm.o \

C_DEPS += \
./Sources/global.d \
./Sources/gpio.d \
./Sources/led.d \
./Sources/main.d \
./Sources/port.d \
./Sources/rand.d \
./Sources/sim.d \
./Sources/simon.d \
./Sources/systick.d \

S_DEPS += \
./Sources/pushb.d \
./Sources/tpm.d \

OBJS_QUOTED += \
"./Sources/global.o" \
"./Sources/gpio.o" \
"./Sources/led.o" \
"./Sources/main.o" \
"./Sources/port.o" \
"./Sources/pushb.o" \
"./Sources/rand.o" \
"./Sources/sim.o" \
"./Sources/simon.o" \
"./Sources/systick.o" \
"./Sources/tpm.o" \

C_DEPS_QUOTED += \
"./Sources/global.d" \
"./Sources/gpio.d" \
"./Sources/led.d" \
"./Sources/main.d" \
"./Sources/port.d" \
"./Sources/rand.d" \
"./Sources/sim.d" \
"./Sources/simon.d" \
"./Sources/systick.d" \

OBJS_OS_FORMAT += \
./Sources/global.o \
./Sources/gpio.o \
./Sources/led.o \
./Sources/main.o \
./Sources/port.o \
./Sources/pushb.o \
./Sources/rand.o \
./Sources/sim.o \
./Sources/simon.o \
./Sources/systick.o \
./Sources/tpm.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/global.o: ../Sources/global.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/global.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/global.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/gpio.o: ../Sources/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/gpio.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/led.o: ../Sources/led.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/led.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/led.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/port.o: ../Sources/port.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/port.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/port.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/pushb.o: ../Sources/pushb.s
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/pushb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/pushb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/rand.o: ../Sources/rand.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/rand.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/rand.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sim.o: ../Sources/sim.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sim.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sim.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/simon.o: ../Sources/simon.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/simon.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/simon.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/systick.o: ../Sources/systick.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/systick.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/systick.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/tpm.o: ../Sources/tpm.s
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/tpm.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/tpm.o"
	@echo 'Finished building: $<'
	@echo ' '


