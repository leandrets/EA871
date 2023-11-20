################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC.c" \
"../Sources/GPIO_latch_lcd.c" \
"../Sources/GPIO_switches.c" \
"../Sources/ISR.c" \
"../Sources/TPM.c" \
"../Sources/cactus.c" \
"../Sources/dino.c" \
"../Sources/game.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \
"../Sources/timers.c" \
"../Sources/util.c" \

C_SRCS += \
../Sources/ADC.c \
../Sources/GPIO_latch_lcd.c \
../Sources/GPIO_switches.c \
../Sources/ISR.c \
../Sources/TPM.c \
../Sources/cactus.c \
../Sources/dino.c \
../Sources/game.c \
../Sources/main.c \
../Sources/sa_mtb.c \
../Sources/timers.c \
../Sources/util.c \

OBJS += \
./Sources/ADC.o \
./Sources/GPIO_latch_lcd.o \
./Sources/GPIO_switches.o \
./Sources/ISR.o \
./Sources/TPM.o \
./Sources/cactus.o \
./Sources/dino.o \
./Sources/game.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/timers.o \
./Sources/util.o \

C_DEPS += \
./Sources/ADC.d \
./Sources/GPIO_latch_lcd.d \
./Sources/GPIO_switches.d \
./Sources/ISR.d \
./Sources/TPM.d \
./Sources/cactus.d \
./Sources/dino.d \
./Sources/game.d \
./Sources/main.d \
./Sources/sa_mtb.d \
./Sources/timers.d \
./Sources/util.d \

OBJS_QUOTED += \
"./Sources/ADC.o" \
"./Sources/GPIO_latch_lcd.o" \
"./Sources/GPIO_switches.o" \
"./Sources/ISR.o" \
"./Sources/TPM.o" \
"./Sources/cactus.o" \
"./Sources/dino.o" \
"./Sources/game.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \
"./Sources/timers.o" \
"./Sources/util.o" \

C_DEPS_QUOTED += \
"./Sources/ADC.d" \
"./Sources/GPIO_latch_lcd.d" \
"./Sources/GPIO_switches.d" \
"./Sources/ISR.d" \
"./Sources/TPM.d" \
"./Sources/cactus.d" \
"./Sources/dino.d" \
"./Sources/game.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \
"./Sources/timers.d" \
"./Sources/util.d" \

OBJS_OS_FORMAT += \
./Sources/ADC.o \
./Sources/GPIO_latch_lcd.o \
./Sources/GPIO_switches.o \
./Sources/ISR.o \
./Sources/TPM.o \
./Sources/cactus.o \
./Sources/dino.o \
./Sources/game.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/timers.o \
./Sources/util.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC.o: ../Sources/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/GPIO_latch_lcd.o: ../Sources/GPIO_latch_lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/GPIO_latch_lcd.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/GPIO_latch_lcd.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/GPIO_switches.o: ../Sources/GPIO_switches.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/GPIO_switches.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/GPIO_switches.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ISR.o: ../Sources/ISR.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ISR.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ISR.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TPM.o: ../Sources/TPM.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TPM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TPM.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/cactus.o: ../Sources/cactus.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/cactus.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/cactus.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/dino.o: ../Sources/dino.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/dino.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/dino.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/game.o: ../Sources/game.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/game.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/game.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/timers.o: ../Sources/timers.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/timers.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/timers.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/util.o: ../Sources/util.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/util.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/util.o"
	@echo 'Finished building: $<'
	@echo ' '


