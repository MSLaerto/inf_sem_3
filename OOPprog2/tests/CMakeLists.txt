
# ищем в системе пакет Catch2 для тестирования
# необходимо предварительно установить через пакетный менеджер (напр. sudo apt install catch2),
# или скачать из гит-репозитория https://github.com/catchorg/Catch2
find_package(Catch2 2 REQUIRED)

# создание исполняемого файла для программы тестирования
add_executable(train_testing testing.cpp)

# подключение библиотек circle и Catch2 к тесту
target_link_libraries(train_testing train Catch2::Catch2)
