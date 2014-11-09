################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Dynamics/Solver.cpp 

OBJS += \
./Dynamics/Solver.o 

CPP_DEPS += \
./Dynamics/Solver.d 


# Each subdirectory must supply rules for building sources it contributes
Dynamics/%.o: ../Dynamics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/chao/usr/local/include -I"/home/chao/usr/local/include/bullet" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


