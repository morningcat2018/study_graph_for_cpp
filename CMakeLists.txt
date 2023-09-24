cmake_minimum_required(VERSION 3.15)
project(study163_weng)

set(CMAKE_CXX_STANDARD 14)

add_executable(study163_weng main.cpp
        course1/course1.cpp course1/course1.h
        course2/course_2.c course2/Point3d.cpp course2/Point3d.h
        cs50/HelloCs50.cpp cs50/HelloCs50.h cs50/lesson11/FileTest.cpp cs50/lesson11/FileTest.h cs50/lesson13/test13.cpp
        cs50/lesson13/test13.h
        thread/my_thread.cpp thread/my_thread.h
        test/test1.cpp test/test1.h test/test2.c course2/test.cpp course2/test.h course3/test.c)