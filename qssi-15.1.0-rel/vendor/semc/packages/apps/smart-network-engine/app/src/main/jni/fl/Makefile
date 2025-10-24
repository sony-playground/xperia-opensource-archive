LFLAG=-shared --coverage
#CFLAG=-fPIC -std=c++11 -DNDEBUG --coverage -DDEBUG
CFLAG=-fPIC -std=c++11 -DNDEBUG --coverage
JDK_PATH=${arg1}
DEPENDENCY_PATH=${arg2}
NNABLA_PATH=-L${DEPENDENCY_PATH}lib/
INCLUDE_PATH_FOR_LINUX=-I $(JDK_PATH)include/ -I $(JDK_PATH)include/linux/
INCLUDE_PATH_FOR_NNABLA=-I ${DEPENDENCY_PATH}include/
INCLUDE_PATH_FOR_NLOHMANN=-I.
NNABLA_FLAG=-lnnabla -lnnabla_utils
INSTALL_PATH=../../../libs

.PHONY: all
all: install

.cpp.o:
	$(CXX) $(CFLAG) -o $@ -c $< $(INCLUDE_PATH_FOR_LINUX) $(INCLUDE_PATH_FOR_NNABLA) $(INCLUDE_PATH_FOR_NLOHMANN)

LinearHLCR/LinearHLCR.o: \
	FLException.h \
	LinearHLCR/LinearHLCR.h \
	LinearHLCR/LinearRegression.h \
	LinearHLCR/MatrixAndVector.h \
	LinearHLCR/NormalDistribution.h \
	tensor/data_deserializer.h \
	tensor/data_metadata.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
LinearHLCR/LinearHLCR_JNIF.o: \
	FLException.h \
	LinearHLCR/LinearHLCR.h \
	LinearHLCR/LinearHLCR_JNIF.h \
	LinearHLCR/LinearRegression.h \
	LinearHLCR/MatrixAndVector.h \
	LinearHLCR/NormalDistribution.h \
	evaluation/evaluation.h \
	tensor/data_deserializer.h \
	tensor/data_metadata.h \
	tensor/data_serializer.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
LinearHLCR/LinearRegression.o: \
	FLException.h \
	LinearHLCR/LinearRegression.h \
	LinearHLCR/MatrixAndVector.h \
	tensor/tensor.h \
	tensor/tensor_shape.h
LinearHLCR/MatrixAndVector.o: \
	FLException.h \
	LinearHLCR/MatrixAndVector.h \
	tensor/tensor.h \
	tensor/tensor_shape.h
LinearHLCR/NormalDistribution.o: \
	LinearHLCR/NormalDistribution.h
NNHLCR/NNHLCR_JNIF.o: \
	FLException.h \
	NNHLCR/NNHLCR_JNIF.h \
	NNHLCR/NNHLCR_file_IO.h \
	NNHLCR/data_normalizer.h \
	NNHLCR/lstm_lcr_model_nnabla.h \
	NNHLCR/lstm_model_nnabla.h \
	tensor/data_deserializer.h \
	tensor/data_metadata.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
NNHLCR/data_normalizer.o: \
	NNHLCR/data_normalizer.h
NNHLCR/lstm_lcr_model_nnabla.o: \
	NNHLCR/lstm_lcr_model_nnabla.h \
	NNHLCR/lstm_model_nnabla.h
NNHLCR/lstm_model_nnabla.o: \
	NNHLCR/lstm_model_nnabla.h
NNHLCR/NNHLCR_file_IO.o: \
	NNHLCR/NNHLCR_file_IO.h \
	tensor/data_deserializer.h \
	tensor/data_metadata.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
com_sony_fl_jni_LinearHLCRNativeJNI.o: \
	FLException.h \
	LinearHLCR/LinearHLCR.h \
	LinearHLCR/LinearHLCR_JNIF.h \
	LinearHLCR/LinearRegression.h \
	LinearHLCR/MatrixAndVector.h \
	LinearHLCR/NormalDistribution.h \
	com_sony_fl_jni_LinearHLCRNativeJNI.h \
	evaluation/evaluation.h \
	tensor/data_deserializer.h \
	tensor/data_metadata.h \
	tensor/data_serializer.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
com_sony_fl_jni_NNHLCRNativeJNI.o: \
	NNHLCR/NNHLCR_JNIF.h \
	NNHLCR/lstm_lcr_model_nnabla.h \
	NNHLCR/lstm_model_nnabla.h \
	com_sony_fl_jni_NNHLCRNativeJNI.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
evaluation/evaluation.o: \
	evaluation/evaluation.h \
	tensor/data_deserializer.h \
	tensor/data_metadata.h \
	tensor/data_serializer.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h

.cc.o:
	$(CXX) $(CFLAG) -o $@ -c $< ${INCLUDE_PATH_FOR_NLOHMANN}

tensor/data_deserializer.o: \
	FLException.h \
	tensor/data_deserializer.h \
	tensor/data_metadata.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
tensor/data_metadata.o: \
	tensor/data_metadata.h
tensor/data_serializer.o: \
	FLException.h \
	tensor/data_metadata.h \
	tensor/data_serializer.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
tensor/tensor.o: \
	FLException.h \
	tensor/tensor.h \
	tensor/tensor_shape.h
tensor/tensor_map.o: \
	FLException.h \
	tensor/tensor.h \
	tensor/tensor_map.h \
	tensor/tensor_shape.h
tensor/tensor_shape.o: \
	FLException.h \
	tensor/tensor_shape.h

libNNHLCRNative.so: \
		com_sony_fl_jni_NNHLCRNativeJNI.o \
		tensor/data_deserializer.o \
		tensor/data_metadata.o \
		tensor/data_serializer.o \
		tensor/tensor.o \
		tensor/tensor_map.o \
		tensor/tensor_shape.o \
		NNHLCR/NNHLCR_JNIF.o \
		NNHLCR/NNHLCR_file_IO.o \
		NNHLCR/data_normalizer.o \
		NNHLCR/lstm_lcr_model_nnabla.o \
		NNHLCR/lstm_model_nnabla.o
	$(CXX) $(LFLAG) -o $@ $^ $(NNABLA_PATH) $(NNABLA_FLAG)

libLinearHLCRNative.so: \
		com_sony_fl_jni_LinearHLCRNativeJNI.o \
		tensor/data_deserializer.o \
		tensor/data_metadata.o \
		tensor/data_serializer.o \
		tensor/tensor.o \
		tensor/tensor_map.o \
		tensor/tensor_shape.o \
		LinearHLCR/LinearHLCR.o \
		LinearHLCR/LinearHLCR_JNIF.o \
		LinearHLCR/LinearRegression.o \
		LinearHLCR/MatrixAndVector.o \
		LinearHLCR/NormalDistribution.o \
		evaluation/evaluation.o
	$(CXX) $(LFLAG) -o $@ $^

.PHONY: install
install: libNNHLCRNative.so libLinearHLCRNative.so
	mkdir -p $(INSTALL_PATH)
	cp -p libNNHLCRNative.so $(INSTALL_PATH)
	cp -p libLinearHLCRNative.so $(INSTALL_PATH)

.PHONY: clean
clean:
	rm -f libNNHLCRNative.so libLinearHLCRNative.so
	rm -f ./*.o ./*.gcno ./*.gcda
	rm -f tensor/*.o tensor/*.gcno tensor/*.gcda
	rm -f evaluation/*.o evaluation/*.gcno evaluation/*.gcda
	rm -f NNHLCR/*.o NNHLCR/*.gcno NNHLCR/*.gcda
	rm -f LinearHLCR/*.o LinearHLCR/*.gcno LinearHLCR/*.gcda
