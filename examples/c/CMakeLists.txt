add_executable(test_app main.c)

# 添加头文件搜索路径
target_include_directories(test_app PRIVATE 
    ../../install/include  # 指定kuzu.h所在目录
    ${CMAKE_CURRENT_SOURCE_DIR}  # 可选：添加当前源码目录
)

target_link_directories(test_app PRIVATE ../..//install/lib)
target_link_options(test_app PRIVATE "-Wl,-rpath,/install/lib")
target_link_libraries(test_app PRIVATE kuzu)  # 注意库名应为kuzu_shared
