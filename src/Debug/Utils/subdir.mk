################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Utils/Camera.cpp \
../Utils/forOpenGL.cpp \
../Utils/forSDL.cpp \
../Utils/tinyxml2.cpp 

OBJS += \
./Utils/Camera.o \
./Utils/forOpenGL.o \
./Utils/forSDL.o \
./Utils/tinyxml2.o 

CPP_DEPS += \
./Utils/Camera.d \
./Utils/forOpenGL.d \
./Utils/forSDL.d \
./Utils/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
Utils/%.o: ../Utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/chao/usr/local/include -I"/home/chao/usr/local/include/bullet" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


