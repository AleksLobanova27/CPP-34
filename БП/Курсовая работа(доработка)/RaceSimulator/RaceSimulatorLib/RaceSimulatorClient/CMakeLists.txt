project(RaceSimulatorClient)

# Исходные файлы
set(SOURCES main.cpp)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Связываем с нашей библиотекой
target_link_libraries(${PROJECT_NAME} PRIVATE RaceSimulatorLib)

# Устанавливаем путь к заголовочным файлам библиотеки
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/RaceSimulatorLib
)