/*
 * Copyright 2019 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.util;

import static com.sonymobile.smartnetworkengine.Constants.PROP_NN_DIR_OVERRIDE;
import static com.sonymobile.smartnetworkengine.SneUtils.isDebugBuild;

import static java.nio.file.StandardCopyOption.REPLACE_EXISTING;

import android.content.Context;
import android.os.SystemProperties;
import android.text.TextUtils;

import androidx.annotation.NonNull;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Properties;

/**
 * This class reads neural network configuration from specific path and return them to caller.
 */
public class NeuralNetworkConfiguration {

    private static final String TAG = NeuralNetworkConfiguration.class.getSimpleName();

    private static final String NNP_FILENAME = "smartnet.nnp";
    private static final String MEAN_FILENAME = "mean.csv";
    private static final String STD_FILENAME = "std.csv";
    private static final String THRESHOLD_FILENAME = "threshold.txt";

    /** The directory path from which neural network configuration is read */
    private final Path mNnDirPath;

    /** The filename of the copied version of nnp file */
    private final String mCopiedNnpFilename;

    private final Context mContext;

    private Path mCopiedNnpFullPath;
    private List<Float> mMean;
    private List<Float> mStd;
    private Float mThreshold;
    private Float mThresholdMoveRatio;

    public NeuralNetworkConfiguration(@NonNull Context context, @NonNull String nnIdentifier) {
        mNnDirPath = getNnDirectoryPath(nnIdentifier);
        mCopiedNnpFilename = String.format("%s.nnp", nnIdentifier);
        mContext = context;
        Log.v(TAG, "NN data directory: " + mNnDirPath);
    }

    /**
     * Return an absolute path to nnp file.
     */
    @NonNull
    public Path getNnpPath() {
        // To be able to access the nnp file without asset manager, it needs to be copied to
        // the place under application specific 'files' directory. If 'mCopiedNnpFullPath' is
        // null, it indicates that copy is not performed yet.
        if (mCopiedNnpFullPath == null || !Files.exists(mCopiedNnpFullPath)) {
            Path sourcePath = mNnDirPath.resolve(NNP_FILENAME);
            Path destinationPath = mContext.getFilesDir().toPath().resolve(mCopiedNnpFilename);
            try (InputStream in = getInputStream(sourcePath)) {
                Files.copy(in, destinationPath, REPLACE_EXISTING);
            } catch (IOException e) {
                Log.e(TAG, "Failed to copy nnp file from assets: " + e);
                throw new RuntimeException(e);
            }
            mCopiedNnpFullPath = destinationPath;
        }
        return mCopiedNnpFullPath;
    }

    /**
     * Return mean of each parameter.
     */
    @NonNull
    public List<Float> getMean() {
        if (mMean == null) {
            mMean = readFloatValues(mNnDirPath.resolve(MEAN_FILENAME));
        }
        return new ArrayList<>(mMean);
    }

    /**
     * Return standard deviation of each parameter.
     */
    @NonNull
    public List<Float> getStd() {
        if (mStd == null) {
            mStd = readFloatValues(mNnDirPath.resolve(STD_FILENAME));
        }
        return new ArrayList<>(mStd);
    }

    /**
     * Return threshold of inference result for judging network switch.
     */
    public float getThreshold() {
        if (mThreshold == null) {
            loadThresholdParameters();
        }
        return mThreshold;
    }

    /**
     * Return threshold ratio which is supposed to be multiplied by threshold when 'moving'.
     */
    public float getThresholdMoveRatio() {
        if (mThresholdMoveRatio == null) {
            loadThresholdParameters();
        }
        return mThresholdMoveRatio;
    }

    /**
     * Return a directory path from which neural network configuration is read.
     */
    private Path getNnDirectoryPath(String nnIdentifier) {
        String overrideDirName = SystemProperties.get(PROP_NN_DIR_OVERRIDE);
        if (isDebugBuild() && !TextUtils.isEmpty(overrideDirName)) {
            return Paths.get(overrideDirName, nnIdentifier);
        }
        return Paths.get(nnIdentifier);
    }

    /**
     * Whether a path points to application's raw asset files.
     */
    private boolean isAssetPath(Path path) {
        // In the asset files, the number of elements in the path is 2.
        // (cf. getNnDirectoryPath method implementation)
        return path.getNameCount() == 2;
    }

    /**
     * Return an input stream.
     */
    private InputStream getInputStream(Path path) throws IOException {
        if (isAssetPath(path)) {
            return mContext.getResources().getAssets().open(path.toString());
        } else {
            return new FileInputStream(mContext.getFilesDir().toPath().resolve(path).toFile());
        }
    }

    private List<Float> readFloatValues(Path path) {
        List<Float> values = new ArrayList<>();
        try (InputStream in = getInputStream(path);
             InputStreamReader reader = new InputStreamReader(in);
             BufferedReader bufferedReader = new BufferedReader(reader)) {
            // Skip first line as it's a csv header.
            bufferedReader.readLine();
            String line = bufferedReader.readLine();
            if (line != null) {
                Arrays.stream(line.split(","))
                        .forEach(v -> values.add(Float.valueOf(v)));
            }
        } catch (IOException | NumberFormatException e) {
            Log.e(TAG, "Failed to read float values: " + e);
            throw new RuntimeException(e);
        }
        return values;
    }

    private void loadThresholdParameters() {
        try (InputStream in = getInputStream(mNnDirPath.resolve(THRESHOLD_FILENAME));
             InputStreamReader reader = new InputStreamReader(in);
             BufferedReader bufferedReader = new BufferedReader(reader)) {
            Properties props = new Properties();
            props.load(bufferedReader);
            mThreshold = Float.valueOf(props.getProperty("default", ""));
            mThresholdMoveRatio = Float.valueOf(props.getProperty("move_ratio", ""));
        } catch (IOException | NumberFormatException e) {
            Log.e(TAG, "Failed to read threshold file: " + e);
            throw new RuntimeException(e);
        }
    }
}
