cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# cmake -DCMAKE_PREFIX_PATH="." -DCMAKE_TOOLCHAIN_FILE="../cmake/gcc.cmake" -DARM_CPU="cortex-m33" -G "Ninja" ..


project(AP1G28AACXWA)

# USER CODE BEGIN start

# USER CODE END start

set(PROJ_DIR ${CMAKE_SOURCE_DIR})
set(SDK_VER 1_4_0)
set(SDK_DIR C:/Users/Administrator/AppData/Roaming/yt_config_tool/sdk/YTM32B1ME0_1_4_0)

include(${CMAKE_SOURCE_DIR}/cmake/config.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/targets/GENERATED_CONFIG_TARGET.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/targets/GENERATED_SDK_TARGET.cmake)

# USER CODE BEGIN include
# include(...)
# USER CODE END include

set(project_elf AP1G28AACXWA.elf)
add_executable(${project_elf} app/main.c)
#add app as include path
target_include_directories(${project_elf} PRIVATE app)
#add all source files in app folder 
file(GLOB dir_sources "app/*.c" "app/*.cpp" "app/*.S")
if(dir_sources)
    foreach(src ${dir_sources})
        target_sources(${project_elf} PRIVATE ${src})
    endforeach()
endif()

# USER CODE BEGIN add_executable
# target_include_directories()
target_include_directories(${project_elf} PRIVATE app/DSP/Include)
target_include_directories(${project_elf} PRIVATE app/DSP/Include/dsp)
target_include_directories(${project_elf} PRIVATE include)
# target_sources(${project_elf} PRIVATE ..)
# USER CODE END add_executable

configcore(${project_elf} ${CMAKE_SOURCE_DIR})


# USER CODE BEGIN target_compile_definitions
# target_compile_definitions(...)
# USER CODE END target_compile_definitions

target_compile_definitions(${project_elf} PUBLIC
    "YTM32B1ME0"
    "CPU_YTM32B1ME0"
)

# USER CODE BEGIN target_compile_options
# target_compile_options(...)
# USER CODE END target_compile_options


target_link_libraries(${project_elf} "-Wl,--whole-archive" GENERATED_CONFIG_TARGET GENERATED_SDK_TARGET  "-Wl,--no-whole-archive")

# USER CODE BEGIN target_link_libraries
target_link_directories(${project_elf} PRIVATE "app")
target_link_libraries(${project_elf} -l:libmotor.a)
# USER CODE END target_link_libraries


if (CORTEXM)
    compilerSpecificPlatformConfigAppForM(${project_elf} ${CMAKE_SOURCE_DIR} )
elseif(CORTEXA)
    compilerSpecificPlatformConfigAppForA(${project_elf} ${CMAKE_SOURCE_DIR} )
else()
    compilerSpecificPlatformConfigAppForR(${project_elf} ${CMAKE_SOURCE_DIR} )
endif()

target_link_libraries(${project_elf} "--entry=Reset_Handler;-T${PROJ_DIR}/board/yt_linker.ld")
target_link_libraries(${project_elf} "-Wl,-Map=AP1G28AACXWA.map;-Wl,--end-group")
add_custom_command(TARGET ${project_elf} POST_BUILD COMMAND arm-none-eabi-size --format=berkeley ${project_elf})
add_custom_target(genbin
    DEPENDS ${project_elf}
    COMMAND ${CMAKE_OBJCOPY} -F elf32-littlearm -O binary ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
)
add_custom_target(genhex
    DEPENDS ${project_elf}
    COMMAND ${CMAKE_OBJCOPY} -F elf32-littlearm -O ihex ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
)
add_custom_command(
    TARGET ${project_elf} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -F elf32-littlearm -O ihex ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
)
add_custom_target(gens19
    DEPENDS ${project_elf}
    COMMAND ${CMAKE_OBJCOPY} -F elf32-littlearm -O srec ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.s19
)
add_custom_target(genlist
    DEPENDS ${project_elf}
    COMMAND ${CMAKE_OBJDUMP}  --source --all-headers --demangle --line-numbers --wide ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf > ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.lst
)



# yct file as depend
file(GLOB yct_files "${CMAKE_SOURCE_DIR}/*.yct")
if(yct_files)
    list(APPEND CMAKE_CONFIGURE_DEPENDS ${yct_files})
endif()

# USER CODE BEGIN others

# USER CODE END others