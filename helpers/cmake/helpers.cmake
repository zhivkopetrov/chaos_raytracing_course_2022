cmake_minimum_required(VERSION 3.10.2)

function(set_target_cpp_standard target standard)
set_target_properties(
    ${target}
    PROPERTIES
        CXX_STANDARD ${standard}
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
endfunction()

function(enable_target_warnings target)
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        target_compile_options(
            ${target}
                PRIVATE
                  /W4
                  /WX
        )
        return()
    endif()

    target_compile_options(
        ${target}
            PRIVATE
              -Wall
              -Wextra
              -Werror
              -Wundef
              -Wuninitialized
              -Wshadow
              -Wpointer-arith
              -Wcast-align
              -Wcast-qual
              -Wunused-parameter
              -Wdouble-promotion
              -Wnull-dereference
    )
    
    # append additional GNU specific warnings
    if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        target_compile_options(
          ${target}
              PRIVATE
                -Wlogical-op
                -Wduplicated-cond
                -Wduplicated-branches
        )
    endif()
endfunction()

function(set_target_visibility target)
    if(${CMAKE_BUILD_TYPE} MATCHES Release OR 
       ${CMAKE_BUILD_TYPE} MATCHES MinSizeRel)
        
        # Default to hidden visibility for symbols
        set_target_properties(
            ${target}
             PROPERTIES 
                CXX_VISIBILITY_PRESET hidden
                VISIBILITY_INLINES_HIDDEN TRUE
        )
    endif()
endfunction()

#enable_target_sanitizer(${my_target} "sanitizer_name")
# Available sanitizers
#
# GCC: address, thread, leak, undefined
# CLANG: address, memory, thread, leak, undefined
function(enable_target_sanitizer target sanitizer)
    if(NOT CMAKE_BUILD_TYPE OR NOT ${CMAKE_BUILD_TYPE} MATCHES Debug)
        message(
            FATAL_ERROR
            "Error: Sanitizers can be enabled only with 'Debug' build\n"
            "Hint: Use 'cmake .. -DCMAKE_BUILD_TYPE=Debug'")
        return()
    endif()
    
    target_link_libraries(
        ${target}
            PRIVATE
                -fsanitize=${sanitizer}
    )
    
    if(${sanitizer} STREQUAL "address")
        target_link_libraries(
            ${target}
                PRIVATE
                    -fno-omit-frame-pointer
        )
    endif()
    
    if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        if (${sanitizer} STREQUAL "undefined")
            target_link_libraries(
                ${target}
                    PRIVATE
                        -lubsan
            )
        elseif (${sanitizer} STREQUAL "thread")
            target_link_libraries(
                ${target}
                    PRIVATE
                        -ltsan
            )
        endif()
    endif()
endfunction()

