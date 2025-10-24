package com.sony.fl.utils;
/**
 * @author Masanobu Jimbo
 */

import static org.junit.Assert.assertEquals;

import com.sony.fl.logger.FLLogger;
import com.sony.fl.pb.TaskInfo;

import org.junit.Test;

public class TestPBChecker {
    String charSet = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890-_";
    String invalidCharSet = "!?<>+~^|/\\[]{}:;.,";
    int NUM_OF_LOOP = 100; 
    int MIN_LEN = 1;
    int MAX_LEN = 128;



/*
#######                           ###
   #       ##     ####   #    #    #     #    #  ######   ####
   #      #  #   #       #   #     #     ##   #  #       #    #
   #     #    #   ####   ####      #     # #  #  #####   #    #
   #     ######       #  #  #      #     #  # #  #       #    #
   #     #    #  #    #  #   #     #     #   ##  #       #    #
   #     #    #   ####   #    #   ###    #    #  #        ####
*/
    @Test
    public void testCheckTaskInfoWithValidTaskInfo() {
        for (TaskInfo.TaskType taskType : TaskInfo.TaskType.values()) {
            if (taskType == TaskInfo.TaskType.Train) {
                FLLogger.d("createValidTaskInfoForTrain()");
                assertEquals(0, PBChecker.checkPBTaskInfo(
                        CreatePBForTest.createValidTaskInfoForTrain()));
            } else if (taskType == TaskInfo.TaskType.Evaluation) {
                FLLogger.d("createValidTaskInfoForEvaluation()");
                assertEquals(0, PBChecker.checkPBTaskInfo(
                        CreatePBForTest.createValidTaskInfoForEvaluation()));
            } else if (taskType == TaskInfo.TaskType.Deploy) {
                FLLogger.d("createValidTaskInfoForDeploy()");
                assertEquals(0, PBChecker.checkPBTaskInfo(
                        CreatePBForTest.createValidTaskInfoForDeploy()));
            } else if (taskType == TaskInfo.TaskType.Delete) {
                FLLogger.d("createValidTaskInfoForDelete()");
                assertEquals(0, PBChecker.checkPBTaskInfo(
                        CreatePBForTest.createValidTaskInfoForDelete()));
            } else if (taskType == TaskInfo.TaskType.Stop) {
                FLLogger.d("createValidTaskInfoForStop()");
                assertEquals(0, PBChecker.checkPBTaskInfo(
                        CreatePBForTest.createValidTaskInfoForStop()));
            } else if (taskType == TaskInfo.TaskType.UnknownTaskType) {
                continue;
            } else {
                FLLogger.i("forget to create a unit test for new task type.");
                assertEquals(0, 1);
            }
        }
    }

    @Test
    public void testCheckTaskInfoWithInvalidTaskInfo() {
        assertEquals(1, PBChecker.checkPBTaskInfo(
                CreatePBForTest.createInValidTaskInfoWithInvalidTaskID()));
        assertEquals(1, PBChecker.checkPBTaskInfo(
                CreatePBForTest.createInValidTaskInfoWithInvalidFLID()));
        assertEquals(1, PBChecker.checkPBTaskInfo(
                CreatePBForTest.createInValidTaskInfoWithoutTaskType()));
        assertEquals(1, PBChecker.checkPBTaskInfo(
                CreatePBForTest.createInValidTaskInfoWithoutTaskInfo()));
        assertEquals(1, PBChecker.checkPBTaskInfo(
                CreatePBForTest.createInValidTaskInfoWithoutSNEInfo()));
        assertEquals(1, PBChecker.checkPBTaskInfo(null));
    }

/*
#######                                   ###
   #     #####     ##       #    #    #    #     #    #  ######   ####
   #     #    #   #  #      #    ##   #    #     ##   #  #       #    #
   #     #    #  #    #     #    # #  #    #     # #  #  #####   #    #
   #     #####   ######     #    #  # #    #     #  # #  #       #    #
   #     #   #   #    #     #    #   ##    #     #   ##  #       #    #
   #     #    #  #    #     #    #    #   ###    #    #  #        ####
*/

    @Test
    public void testCheckTrainInfoWithValidTrainInfo() {
        for (TaskInfo.ModelType modelType : TaskInfo.ModelType.values()) {
            if (modelType == TaskInfo.ModelType.LinerHLCR) {
                assertEquals(0, PBChecker.checkPBTrainInfo(
                        CreatePBForTest.createValidTrainInfoForLinearHLCR()));
            } else if (modelType == TaskInfo.ModelType.NNHLCR) {
                assertEquals(0, PBChecker.checkPBTrainInfo(
                        CreatePBForTest.createValidTrainInfoForNNHLCR()));
            } else if (modelType == TaskInfo.ModelType.UnknownModelType) {
                continue;
            } else {
                assertEquals(0, 1);
            }
        }
    }

    @Test
    public void testCheckTrainInfoWithInvalidTrainInfo() {
        assertEquals(1, PBChecker.checkPBTrainInfo(
                CreatePBForTest.createInValidTrainInfoWithoutModelType()));
        assertEquals(1, PBChecker.checkPBTrainInfo(
                CreatePBForTest.createInValidTrainInfoWithoutTrainInfo()));
        assertEquals(1, PBChecker.checkPBTrainInfo(
                CreatePBForTest.createInValidTrainInfoWithoutModelInfo()));
        assertEquals(1, PBChecker.checkPBTrainInfo(null));
    }

/*
#######                           ###
#        #    #    ##    #         #     #    #  ######   ####
#        #    #   #  #   #         #     ##   #  #       #    #
#####    #    #  #    #  #         #     # #  #  #####   #    #
#        #    #  ######  #         #     #  # #  #       #    #
#         #  #   #    #  #         #     #   ##  #       #    #
#######    ##    #    #  ######   ###    #    #  #        ####
*/
    @Test
    public void testCheckEvaluationInfoWithValidEvaluationInfo() {
        for (TaskInfo.ModelType modelType : TaskInfo.ModelType.values()) {
            if (modelType == TaskInfo.ModelType.LinerHLCR) {
                assertEquals(0, PBChecker.checkPBEvaluationInfo(
                        CreatePBForTest.createValidEvaluationInfoForLinearHLCR()));
            } else if (modelType == TaskInfo.ModelType.NNHLCR) {
                assertEquals(0, PBChecker.checkPBEvaluationInfo(
                        CreatePBForTest.createValidEvaluationInfoForNNHLCR()));
            } else if (modelType == TaskInfo.ModelType.UnknownModelType) {
                continue;
            } else {
                assertEquals(0, 1);
            }
        }
    }

    @Test
    public void testCheckEvaluationInfoWithInvalidEvaluationInfo() {
        assertEquals(1, PBChecker.checkPBEvaluationInfo(
                CreatePBForTest.createInValidEvaluationInfoWithoutModelType()));
        assertEquals(1, PBChecker.checkPBEvaluationInfo(
                CreatePBForTest.createInValidEvaluationInfoWithoutModelInfo()));
        assertEquals(1, PBChecker.checkPBEvaluationInfo(null));
    }

/*
######                                            ###
#     #  ######  #####   #        ####    #   #    #     #    #  ######   ####
#     #  #       #    #  #       #    #    # #     #     ##   #  #       #    #
#     #  #####   #    #  #       #    #     #      #     # #  #  #####   #    #
#     #  #       #####   #       #    #     #      #     #  # #  #       #    #
#     #  #       #       #       #    #     #      #     #   ##  #       #    #
######   ######  #       ######   ####      #     ###    #    #  #        ####
*/
    @Test
    public void testCheckDeployInfoWithValidDeployInfo() {
        for (TaskInfo.ModelType modelType : TaskInfo.ModelType.values()) {
            if (modelType == TaskInfo.ModelType.LinerHLCR) {
                assertEquals(0, PBChecker.checkPBDeployInfo(
                        CreatePBForTest.createValidDeployInfoForLinearHLCR()));
            } else if (modelType == TaskInfo.ModelType.NNHLCR) {
                assertEquals(0, PBChecker.checkPBDeployInfo(
                        CreatePBForTest.createValidDeployInfoForNNHLCR()));
            } else if (modelType == TaskInfo.ModelType.UnknownModelType) {
                continue;
            } else {
                assertEquals(0, 1);
            }
        }
    }

    @Test
    public void testCheckTrainInfoWithInvalidDeployInfo() {
        assertEquals(1, PBChecker.checkPBDeployInfo(
                CreatePBForTest.createInValidDeployInfoWithoutModelType()));
        assertEquals(1, PBChecker.checkPBDeployInfo(
                CreatePBForTest.createInValidDeployInfoWithoutModelInfo()));
        assertEquals(1, PBChecker.checkPBDeployInfo(
                CreatePBForTest.createInValidDeployInfoWithInvalidAppID()));
        assertEquals(1, PBChecker.checkPBDeployInfo(null));
    }

/*
######                                            ###
#     #  ######  #       ######   #####  ######    #     #    #  ######   ####
#     #  #       #       #          #    #         #     ##   #  #       #    #
#     #  #####   #       #####      #    #####     #     # #  #  #####   #    #
#     #  #       #       #          #    #         #     #  # #  #       #    #
#     #  #       #       #          #    #         #     #   ##  #       #    #
######   ######  ######  ######     #    ######   ###    #    #  #        ####
*/
    @Test
    public void testCheckDeleteInfoWithValidDeleteInfo() {

    }

    @Test
    public void testCheckDeleteInfoWithInvalidDeleteInfo() {
        assertEquals(1, PBChecker.checkPBDeleteInfo(null));
    }

/*
 #####                            ###
#     #   #####   ####   #####     #     #    #  ######   ####
#           #    #    #  #    #    #     ##   #  #       #    #
 #####      #    #    #  #    #    #     # #  #  #####   #    #
      #     #    #    #  #####     #     #  # #  #       #    #
#     #     #    #    #  #         #     #   ##  #       #    #
 #####      #     ####   #        ###    #    #  #        ####
*/
    @Test
    public void testCheckStopInfoWithValidStopInfo() {
        assertEquals(0, PBChecker.checkPBStopInfo(
                CreatePBForTest.createValidStopInfo()));
    }

    @Test
    public void testCheckTrainInfoWithInvalidStopInfo() {
        assertEquals(1, PBChecker.checkPBStopInfo(
                CreatePBForTest.createInValidStopInfoWithInvalidAppID()));
        assertEquals(1, PBChecker.checkPBStopInfo(null));
    }

/*
######                            ###
#     #    ##     #####    ##      #     #    #  ######   ####
#     #   #  #      #     #  #     #     ##   #  #       #    #
#     #  #    #     #    #    #    #     # #  #  #####   #    #
#     #  ######     #    ######    #     #  # #  #       #    #
#     #  #    #     #    #    #    #     #   ##  #       #    #
######   #    #     #    #    #   ###    #    #  #        ####
*/
    @Test
    public void testCheckDataIntoWithValidDataInto() {
        assertEquals(0, PBChecker.checkPBDataInfo(
            CreatePBForTest.createValidDataInfo()
        ));
    }

    @Test
    public void testCheckDataIntoWithInvalidDataInto() {
        assertEquals(1, PBChecker.checkPBDataInfo(
            CreatePBForTest.createInvalidDataInfoWithInvalidPreprocessParamFile()
        ));
        assertEquals(1, PBChecker.checkPBDataInfo(null));
    }

/*
                       #     # #        #####  ######  #     #
#           #    #    # #     # #       #     # #     # ##   ##   ####   #####
#           #    ##   # #     # #       #       #     # # # # #  #    #  #    #
#           #    # #  # ####### #       #       ######  #  #  #  #    #  #    #
#           #    #  # # #     # #       #       #   #   #     #  #    #  #    #
#           #    #   ## #     # #       #     # #    #  #     #  #    #  #    #
#######     #    #    # #     # #######  #####  #     # #     #   ####   #####
*/

    @Test
    public void testCheckLinearHLCRGlobalModelWithValidLinearHLCRGlobalModel() {
        assertEquals(0, PBChecker.checkPBLinearHLCRGlobalModel(
            CreatePBForTest.createValidLinearHLCRGlobalModel()
        ));
    }

    @Test
    public void testCheckLinearHLCRGlobalModelWithInvalidLinearHLCRGlobalModel() {
        assertEquals(1, PBChecker.checkPBLinearHLCRGlobalModel(null));
    }

    @Test
    public void testCheckLinearHLCRLocalModelWithValidLinearHLCRLocalModel() {
        assertEquals(0, PBChecker.checkPBLinearHLCRLocalModel(
            CreatePBForTest.createValidLinearHLCRLocalModel()
        ));
    }

    @Test
    public void testCheckLinearHLCRLocalModelWithInvalidLinearHLCRLocalModel() {
        assertEquals(1, PBChecker.checkPBLinearHLCRLocalModel(null));
    }

/*
#     # #     # #     # #        #####  ######  #     #
##    # ##    # #     # #       #     # #     # ##   ##   ####   #####   ######
# #   # # #   # #     # #       #       #     # # # # #  #    #  #    #  #
#  #  # #  #  # ####### #       #       ######  #  #  #  #    #  #    #  #####
#   # # #   # # #     # #       #       #   #   #     #  #    #  #    #  #
#    ## #    ## #     # #       #     # #    #  #     #  #    #  #    #  #
#     # #     # #     # #######  #####  #     # #     #   ####   #####   ######
*/

    @Test
    public void testCheckNNHLCRModelWithValidNNHLCRModel() {
        assertEquals(0, PBChecker.checkPBNNHLCRModel(
            CreatePBForTest.createValidNNHLCRModel()
        ));
    }

    @Test
    public void testCheckNNHLCRModelWithInvalidNNHLCRModel() {
        assertEquals(1, PBChecker.checkPBNNHLCRModel(
            CreatePBForTest.createInvalidNNHLCRModelWithInvalidNNFile()
        ));
        assertEquals(1, PBChecker.checkPBNNHLCRModel(
            CreatePBForTest.createInvalidNNHLCRModelWithInvalidParamFile()
        ));
        assertEquals(1, PBChecker.checkPBNNHLCRModel(null));
    }

/*
#                       #     # #        #####  ######  #######
#           #    #    # #     # #       #     # #     #    #     #####     ##
#           #    ##   # #     # #       #       #     #    #     #    #   #  #
#           #    # #  # ####### #       #       ######     #     #    #  #    #
#           #    #  # # #     # #       #       #   #      #     #####   ######
#           #    #   ## #     # #       #     # #    #     #     #   #   #    #
#######     #    #    # #     # #######  #####  #     #    #     #    #  #    #
*/

    @Test
    public void testCheckPBLinearHLCRTrainInfoWithValidLinearHLCRTrainInfo() {
        assertEquals(0, PBChecker.checkPBLinearHLCRTrainInfo(
            CreatePBForTest.createValidLinearHLCRTrainInfo()
        ));
    }

    @Test
    public void testCheckPBLinearHLCRTrainInfoWithInvalidHLCRTrainInfo() {
        assertEquals(1, PBChecker.checkPBLinearHLCRTrainInfo(null));
    }

/*
#     # #     # #     # #        #####  ######  #######
##    # ##    # #     # #       #     # #     #    #     #####     ##       #
# #   # # #   # #     # #       #       #     #    #     #    #   #  #      #
#  #  # #  #  # ####### #       #       ######     #     #    #  #    #     #
#   # # #   # # #     # #       #       #   #      #     #####   ######     #
#    ## #    ## #     # #       #     # #    #     #     #   #   #    #     #
#     # #     # #     # #######  #####  #     #    #     #    #  #    #     #
*/

    @Test
    public void testCheckPBNNHLCRTrainInfoWithValidNNHLCRTrainInfo() {
        assertEquals(0, PBChecker.checkPBNNHLCRTrainInfo(
            CreatePBForTest.createValidNNHLCRTrainInfo()
        ));
    }

    @Test
    public void testCheckPBNNHLCRTrainInfoWithInvalidHLCRTrainInfo() {
        assertEquals(1, PBChecker.checkPBNNHLCRTrainInfo(
            CreatePBForTest.createInValidNNHLCRTrainInfoWithInvalidHyperParamFile()
        ));
        assertEquals(1, PBChecker.checkPBNNHLCRTrainInfo(null));
    }   


/*
#######                         ######
   #       ##     ####   #    # #     #  ######   ####   #    #  #        #####
   #      #  #   #       #   #  #     #  #       #       #    #  #          #
   #     #    #   ####   ####   ######   #####    ####   #    #  #          #
   #     ######       #  #  #   #   #    #            #  #    #  #          #
   #     #    #  #    #  #   #  #    #   #       #    #  #    #  #          #
   #     #    #   ####   #    # #     #  ######   ####    ####   ######     #
*/

    @Test
    public void testCheckTaskResultWithValidTaskResult() {
        for (TaskInfo.TaskType taskType : TaskInfo.TaskType.values()) {
            if (taskType == TaskInfo.TaskType.Train) {
                assertEquals(0, PBChecker.checkTaskResult(CreatePBForTest.createValidTaskResultForTrain(), 
                        CreatePBForTest.createValidTaskInfoForTrain()));
            } else if (taskType == TaskInfo.TaskType.Evaluation) {
                assertEquals(0, PBChecker.checkTaskResult(CreatePBForTest.createValidTaskResultForEvaluation(), 
                        CreatePBForTest.createValidTaskInfoForEvaluation()));
            } 
        }
    }

    @Test
    public void testCheckTaskResultWithInvalidTaskResult() {
        assertEquals(1, PBChecker.checkTaskResult(
            CreatePBForTest.createInValidTaskResultForTrainWithInvalidFLID(), 
            CreatePBForTest.createValidTaskInfoForTrain()
        ));
        assertEquals(1, PBChecker.checkTaskResult(
            CreatePBForTest.createInvalidTaskResultForTrainWithInvalidTaskID(), 
            CreatePBForTest.createValidTaskInfoForTrain()
        ));
        assertEquals(1, PBChecker.checkTaskResult(
            CreatePBForTest.createInvalidTaskResultForTrainWithoutTrainResult(),
            CreatePBForTest.createValidTaskInfoForTrain()
        ));
        assertEquals(1, PBChecker.checkTaskResult(
            CreatePBForTest.createInvalidTaskResultForEvaluationWithoutEvaluationResult(),
            CreatePBForTest.createValidTaskInfoForEvaluation()
        ));
        assertEquals(1, PBChecker.checkTaskResult(
            null,
            CreatePBForTest.createValidTaskInfoForEvaluation()
        ));
    }

/*
#######                                 ######
   #     #####     ##       #    #    # #     #  ######   ####   #    #  #
   #     #    #   #  #      #    ##   # #     #  #       #       #    #  #
   #     #    #  #    #     #    # #  # ######   #####    ####   #    #  #
   #     #####   ######     #    #  # # #   #    #            #  #    #  #
   #     #   #   #    #     #    #   ## #    #   #       #    #  #    #  #
   #     #    #  #    #     #    #    # #     #  ######   ####    ####   ######
*/

    @Test
    public void testCheckPBTrainResultWithValidTrainResult() {
        assertEquals(0, PBChecker.checkPBTrainResult(
            CreatePBForTest.createValidTrainTaskResultForNNHLCR(), 
            CreatePBForTest.createValidTrainInfoForNNHLCR()
        ));
    }

    @Test
    public void testCheckPBTrainResultWithInvalidTrainResult() {
        assertEquals(1, PBChecker.checkPBTrainResult(
            CreatePBForTest.createInvalidTrainTaskResultForNNHLCRWithInvalidValidFile(), 
            CreatePBForTest.createValidTrainInfoForNNHLCR()
        ));
        assertEquals(1, PBChecker.checkPBTrainResult(
            CreatePBForTest.createInvalidTrainTaskResultForNNHLCRWithoutNNHLCRModel(),
            CreatePBForTest.createValidTrainInfoForNNHLCR()
        ));
        assertEquals(1, PBChecker.checkPBTrainResult(
            null,
            CreatePBForTest.createValidTrainInfoForNNHLCR()
        ));
    }

/*
#######                         ######
#        #    #    ##    #      #     #  ######   ####   #    #  #        #####
#        #    #   #  #   #      #     #  #       #       #    #  #          #
#####    #    #  #    #  #      ######   #####    ####   #    #  #          #
#        #    #  ######  #      #   #    #            #  #    #  #          #
#         #  #   #    #  #      #    #   #       #    #  #    #  #          #
#######    ##    #    #  ###### #     #  ######   ####    ####   ######     #
*/

    @Test
    public void testCheckPBEvaluationResultWithValidEvaluationResult() {
        assertEquals(0, PBChecker.checkPBEvaluationResult(
            CreatePBForTest.createValidEvaluationTaskResultWithValidEvaluationTask(), 
            CreatePBForTest.createValidEvaluationInfoForNNHLCR()
        ));
    }

    @Test
    public void testCheckPBEvaluationResultWithInvalidEvaluationResult() {
        assertEquals(1, PBChecker.checkPBEvaluationResult(
            CreatePBForTest.createInvalidEvaluationTaskResultWithInvalidFileName(), 
            CreatePBForTest.createValidEvaluationInfoForNNHLCR()
        ));
        assertEquals(1, PBChecker.checkPBEvaluationResult(
            null,
            CreatePBForTest.createValidEvaluationInfoForNNHLCR()
        ));
    }


/*
  ####    #####  #    #  ######  #####    ####
 #    #     #    #    #  #       #    #  #
 #    #     #    ######  #####   #    #   ####
 #    #     #    #    #  #       #####        #
 #    #     #    #    #  #       #   #   #    #
  ####      #    #    #  ######  #    #   ####
*/

    @Test 
    public void testLenOfCharSet() {
        assertEquals(26*2+10+2, charSet.length());
    }

    @Test
    public void testIsValidIDWithValidIDs() {
        StringBuilder builder;
        for (int i = 0; i < NUM_OF_LOOP; i++) {
            int length = (int)((MAX_LEN - MAX_LEN + 1) * Math.random()) + 1;
            builder = new StringBuilder(length);
            for (int l = 0; l < length; l++) {
                int index = (int)(charSet.length() * Math.random());
                builder.append(charSet.charAt(index));
            }
            assertEquals(true, PBChecker.isValidID(builder.toString()));
        }
        builder = new StringBuilder(MIN_LEN);
        for (int l = 0; l < MIN_LEN; l++) {
            int index = (int)(charSet.length() * Math.random());
            builder.append(charSet.charAt(index));
        }
        assertEquals(true, PBChecker.isValidID(builder.toString()));
        builder = new StringBuilder(MAX_LEN);
        for (int l = 0; l < MAX_LEN; l++) {
            int index = (int)(charSet.length() * Math.random());
            builder.append(charSet.charAt(index));
        }
        assertEquals(true, PBChecker.isValidID(builder.toString()));
    }

    @Test
    public void testIsValidIDWithTooLongID() {
        StringBuilder builder;
        builder = new StringBuilder(MAX_LEN + 1);
        for (int l = 0; l <= MAX_LEN; l++) {
            int index = (int)(charSet.length() * Math.random());
            builder.append(charSet.charAt(index));
        }
        assertEquals(false, PBChecker.isValidID(builder.toString()));
    }

    @Test
    public void testIsValidStrWithNull() {
        assertEquals(false, PBChecker.isValidStr(null));
    }

    @Test
    public void testIsValidIDWithIDIncludeInvalidChar() {
        for (int i = 0; i < invalidCharSet.length(); i++) {
            assertEquals(false, PBChecker.isValidID("test-" + invalidCharSet.charAt(i)));
        }
        assertEquals(false, PBChecker.isValidID(null));
    }

    @Test
    public void testIsValidFileName() {
        assertEquals(true, PBChecker.isValidFileName("p1.mp4"));
        assertEquals(false, PBChecker.isValidFileName(null));
        assertEquals(false, PBChecker.isValidFileName("XXX=XXX.XXX"));
        assertEquals(false, PBChecker.isValidFileName("ABC.XXXXXXXXXXXXXXXXXXXXXX"));
        assertEquals(false, PBChecker.isValidFileName("ABC.3~4"));
    }

}
