cmake_minimum_required(VERSION 3.27)
project(lab2_4_dinamic_refacut C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic")

add_executable(lab2_4_dinamic_refacut main.c
        utils/utils.c
        utils/utils.h
        domain/models.c
        domain/models.h
        domain/validators.c
        domain/validators.h
        tests/tests.c
        tests/tests.h
        tests/validatorsTest.c
        tests/validatorsTest.h
        tests/validatorsTest.c
        repos/repos.c
        repos/repos.h
        tests/repoTests.c
        tests/repoTests.h
        tests/utilsTests.c
        tests/utilsTests.h
        controllers/controllers.c
        controllers/controllers.h
        tests/controllerTests.c
        tests/controllerTests.h
        ui/ui.c
        ui/ui.h)
