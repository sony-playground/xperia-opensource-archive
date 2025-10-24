cmake_minimum_required(VERSION 3.14)
project(cpptest)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  native_test
  TestFLException.cpp
  tensor/TestTensor.cpp
  tensor/TestTensorMap.cpp
  tensor/TestTensorShape.cpp
  tensor/TestDataSerializer.cpp
  tensor/TestDataDeserializer.cpp
  NNHLCR/TestNNHLCR.cpp
  NNHLCR/TestNNHLCRFileIO.cpp
  NNHLCR/TestLstmNNabla.cpp
  LinearHLCR/TestFLExceptionForJNIF.cpp
  LinearHLCR/TestFLExceptionForLinearHLCR.cpp
  LinearHLCR/TestFLExceptionForLinearRegression.cpp
  LinearHLCR/TestFLExceptionForMatrixAndVector.cpp
  LinearHLCR/TestLinearHLCR.cpp
  LinearHLCR/TestLinearRegression.cpp
  LinearHLCR/TestMatrixAndVector.cpp
  LinearHLCR/TestNormalDistribution.cpp
  evaluation/TestEvaluation.cpp
)

target_link_libraries(
  native_test
  $ENV{FL_LIBS_DIR}/libNNHLCRNative.so
  $ENV{FL_LIBS_DIR}/libLinearHLCRNative.so
  $ENV{FL_DEPENDENCY_LIBS_DIR}/libnnabla_utils.so
  $ENV{FL_DEPENDENCY_LIBS_DIR}/libnnabla.so
  gtest_main
  gmock_main
)

target_include_directories(
  native_test PUBLIC $ENV{FL_SRC_DIR}/main/jni
  $ENV{FL_DEPENDENCY_INCL_DIR}
)

include(GoogleTest)
gtest_discover_tests(native_test)
