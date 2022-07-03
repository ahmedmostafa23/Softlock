set(SOURCE_FILES AES.cpp)

add_library(AESLib ${SOURCE_FILES})

target_link_libraries(AESLib PUBLIC ${lib1})
target_link_libraries(AESLib PUBLIC ${lib2})