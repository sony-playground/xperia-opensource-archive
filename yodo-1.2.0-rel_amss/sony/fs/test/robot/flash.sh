# Unpack the zip files in ANDROID_SW_DIR into EXTRACT_DIR
export EXTRACT_DIR=$OUT_ROBOT_DIR/extract
export IMAGE_DIR=$OUT_ROBOT_DIR/images

if [ ! -d $EXTRACT_DIR ]; then
	mkdir $EXTRACT_DIR
fi

# Remove any previous files
if [ "$(ls -A $EXTRACT_DIR)" ]; then
	rm -r $EXTRACT_DIR/*
fi

for FILE in $ANDROID_SW_DIR/*; do
	unzip -o $FILE -d $EXTRACT_DIR;
done

# Unzip extracted zip files
for FILE in $EXTRACT_DIR/*.zip; do
	unzip -o $FILE -d $EXTRACT_DIR;
done

# Extract images from the sin files into IMAGE_DIR
if [ ! -d $IMAGE_DIR ]; then
	mkdir $IMAGE_DIR
fi

# Remove any previous files
if [ "$(ls -A $IMAGE_DIR)" ]; then
	rm -r $IMAGE_DIR/*
fi

# tar extracts into current directory
cd $IMAGE_DIR
for FILE in $EXTRACT_DIR/*.sin; do
	tar -xvf $FILE --exclude=*.cms;
done
cd $EXEC_DIR

# Flash each file
for FILE in $IMAGE_DIR/*; do
	PARTITION=$(basename "${FILE%.*}")
	if [ "$PARTITION" == "partitionimage_0" ]; then
		PARTITION="0"
	fi
	if [ "$PARTITION" == "partitionimage_1" ]; then
		PARTITION="1"
	fi
	if [ "$PARTITION" == "partitionimage_2" ]; then
		PARTITION="2"
	fi

	HAS_SLOT=$(python fastboot.py getvar has-slot:$PARTITION)
	if [ "$HAS_SLOT" == "OKAYyes" ]; then
		echo Flash $PARTITION"_a with" $FILE
		echo $(python fastboot.py flash $PARTITION"_a" $FILE)
	else
		echo Flash $PARTITION" with" $FILE
		echo $(python fastboot.py flash $PARTITION $FILE)
	fi
done



