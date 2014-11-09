################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BasicApplication.cpp \
../Demo.cpp \
../SDLDemoApplication.cpp \
../main.cpp \
../manager.cpp 

OBJS += \
./BasicApplication.o \
./Demo.o \
./SDLDemoApplication.o \
./main.o \
./manager.o 

CPP_DEPS += \
./BasicApplication.d \
./Demo.d \
./SDLDemoApplication.d \
./main.d \
./manager.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/chao/usr/local/include -I"/home/chao/usr/local/include/bullet" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


