cmake_minimum_required(VERSION 3.16)
project(AppleCheck LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Aurora SDK typically ships Qt5.15; adjust if environment provides Qt6
find_package(Qt5 5.15 COMPONENTS Core Gui Qml Quick QuickControls2 Multimedia REQUIRED)

find_package(OpenCV REQUIRED)
find_package(ncnn REQUIRED)
find_package(Torch QUIET)
find_package(mlpack REQUIRED)
find_package(TensorFlowLite REQUIRED)

set(SOURCES
    src/main.cpp
    src/core/AppController.cpp
    src/core/CameraHandler.cpp
    src/core/ImageProcessor.cpp
    src/core/NcnnInference.cpp
    src/core/TfliteInference.cpp
    src/core/MlPackTrainer.cpp
    src/core/AppleClassifier.cpp
    src/core/AppSettings.cpp
)

set(HEADERS
    src/core/AppController.h
    src/core/CameraHandler.h
    src/core/ImageProcessor.h
    src/core/NcnnInference.h
    src/core/TfliteInference.h
    src/core/MlPackTrainer.h
    src/core/AppleClassifier.h
    src/core/AppSettings.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} qml/qml.qrc)

target_include_directories(${PROJECT_NAME} PRIVATE src src/core)

# Link libraries
set(EXTRA_LIBS
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Multimedia
    ${OpenCV_LIBS}
    ncnn
    mlpack
)

if(TensorFlowLite_FOUND)
    list(APPEND EXTRA_LIBS TensorFlowLite::TensorFlowLite)
endif()

if(Torch_FOUND)
    list(APPEND EXTRA_LIBS Torch::Torch)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTRA_LIBS})

# Deploy QML
set(QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/qml)
set(QML2_IMPORT_PATH ${QML_IMPORT_PATH})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY qml/ DESTINATION share/${PROJECT_NAME}/qml)
install(DIRECTORY res/ DESTINATION share/${PROJECT_NAME}/res)
install(FILES src/models/labels.txt src/models/initial_weights.bin DESTINATION share/${PROJECT_NAME}/models)
