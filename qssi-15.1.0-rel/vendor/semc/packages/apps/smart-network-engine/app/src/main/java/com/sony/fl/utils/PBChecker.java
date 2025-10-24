package com.sony.fl.utils;

import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.pb.LinearHLCR.PBLinearHLCRGlobalModel;
import com.sony.fl.pb.LinearHLCR.PBLinearHLCRLocalModel;
import com.sony.fl.pb.LinearHLCR.PBLinearHLCRTrainInfo;
import com.sony.fl.pb.NNHLCR.PBNNHLCRModel;
import com.sony.fl.pb.NNHLCR.PBNNHLCRTrainInfo;
import com.sony.fl.pb.TaskInfo.*;
import com.sony.fl.pb.TaskResult.PBEvaluationResult;
import com.sony.fl.pb.TaskResult.PBTaskResult;
import com.sony.fl.pb.TaskResult.PBTrainResult;

/**
 * @author Masanobu Jimbo
 */


public class PBChecker {
    private final static int MIN_ID_LEN = 1;
    private final static int MAX_ID_LEN = 128;
    private final static int MIN_EXTENSION_NAME_LEN = 1;
    private final static int MAX_EXTENSION_NAME_LEN = 10;
    private final static Pattern pattern = Pattern.compile("^[a-zA-Z0-9_-]+$");
    private final static Pattern simplePattern = Pattern.compile("^[a-zA-Z0-9]+$");

/*
#######                           ###
   #       ##     ####   #    #    #     #    #  ######   ####
   #      #  #   #       #   #     #     ##   #  #       #    #
   #     #    #   ####   ####      #     # #  #  #####   #    #
   #     ######       #  #  #      #     #  # #  #       #    #
   #     #    #  #    #  #   #     #     #   ##  #       #    #
   #     #    #   ####   #    #   ###    #    #  #        ####
*/

    public static int checkPBTaskInfo(PBTaskInfo taskInfo) {
        if (taskInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!taskInfo.hasFLLibVersion()) {
            FLLogger.i("There is no FLLib version.");
            return 1;
        }
        if (!taskInfo.hasTaskID()) {
            FLLogger.i("There is no taskID.");
            return 1;
        }
        if (!isValidID(taskInfo.getTaskID())) {
            FLLogger.i("Task ID is invalid.");
            return 1;
        }
        if (!taskInfo.hasFLID()) {
            FLLogger.i("There is no FLID.");
            return 1;
        }
        if (!isValidID(taskInfo.getFLID())) {
            FLLogger.i("FL ID is invalid.");
            return 1;
        }
        if (!taskInfo.hasTaskType()) {
            FLLogger.i("There is no task type.");
            return 1;
        }
        if (taskInfo.getTaskType() == TaskType.UnknownTaskType) {
            FLLogger.i("Task Type is Unknown.");
            return 1;
        }
        if (taskInfo.getTaskType() == TaskType.Train) {
            if (!taskInfo.hasTrainInfo()) {
                FLLogger.i("There is no TrainInfo.");
                return 1;
            }
            if (checkPBTrainInfo(taskInfo.getTrainInfo()) != 0) {
                FLLogger.i("TrainInfo is invalid.");
                return 1;
            }
            if (!taskInfo.hasAppID()) {
                FLLogger.i("There is no AppID For SNE.");
                return 1;
            }
            if (!isValidID(taskInfo.getAppID())) {
                FLLogger.i("AppID for SNE is invalid.");
                return 1;
            }
        } else if (taskInfo.getTaskType() == TaskType.Evaluation) {
            if (!taskInfo.hasEvaluationInfo()) {
                FLLogger.i("There is no EvaluationInfo.");
                return 1;
            }
            if (checkPBEvaluationInfo(taskInfo.getEvaluationInfo()) != 0) {
                FLLogger.i("EvaluationInfo is invalid.");
                return 1;
            }
            if (!taskInfo.hasAppID()) {
                FLLogger.i("There is no AppID For SNE.");
                return 1;
            }
            if (!isValidID(taskInfo.getAppID())) {
                FLLogger.i("AppID for SNE is invalid.");
                return 1;
            }
        } else if (taskInfo.getTaskType() == TaskType.Deploy) {
            if (!taskInfo.hasDeployInfo()) {
                FLLogger.i("There is no DeployInfo in this TaskInfo.");
                return 1;
            }
            if (checkPBDeployInfo(taskInfo.getDeployInfo()) != 0) {
                FLLogger.i("DeployInfo is invalid.");
                return 1;
            }
            if (!taskInfo.hasAppID()) {
                FLLogger.i("There is no AppID For SNE.");
                return 1;
            }
            if (!isValidID(taskInfo.getAppID())) {
                FLLogger.i("AppID for SNE is invalid.");
                return 1;
            }
        } else if (taskInfo.getTaskType() == TaskType.Delete) {
            if (!taskInfo.hasDeleteInfo()) {
                FLLogger.i("There is no DeleteInfo in this TaskInfo.");
                return 1;
            }
            if (checkPBDeleteInfo(taskInfo.getDeleteInfo()) != 0) {
                FLLogger.i("DeleteInfo is invalid.");
                return 1;
            }
        } else if (taskInfo.getTaskType() == TaskType.Stop) {
            if (!taskInfo.hasStopInfo()) {
                FLLogger.i("There is no StopInfo in this TaskInfo.");
                return 1;
            }
            if (checkPBStopInfo(taskInfo.getStopInfo()) != 0) {
                FLLogger.i("StopInfo is invalid.");
                return 1;
            }
        } else {
            FLLogger.i("Forget to implement check function for a new task.");
            return 1;
        }
        return 0;
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
    public static int checkPBTrainInfo(PBTrainInfo trainInfo) {
        if (trainInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!trainInfo.hasModelType()) {
            FLLogger.i("There is no model type.");
            return 1;
        }
        switch(trainInfo.getModelType()) {
            case LinerHLCR:
                if ((!trainInfo.hasLinearHLCRGlobalModel()) || (!trainInfo.hasLinearHLCRTrainInfo())) {
                    FLLogger.i("There is no LinearHLCRModel or LinearHLCRTrainInfo.");
                    return 1;
                }
                if ((checkPBLinearHLCRGlobalModel(trainInfo.getLinearHLCRGlobalModel()) != 0) || 
                    (checkPBLinearHLCRTrainInfo(trainInfo.getLinearHLCRTrainInfo()) != 0)) {
                    FLLogger.i("LinearHLCRModel or LinearHLCRTrainInfo is invalid.");
                    return 1;
                }
                break;
            case NNHLCR:
                if (!trainInfo.hasDataInfo()) {
                    FLLogger.i("There is no DataInfo.");
                    return 1;
                }
                if (checkPBDataInfo(trainInfo.getDataInfo()) != 0) {
                    FLLogger.i("DataInfo is invalid.");
                    return 1;
                }
                if ((!trainInfo.hasNNHLCRModel()) || (!trainInfo.hasNNHLCRTrainInfo())) {
                    FLLogger.i("There is no NNHLCRModel or LinearNNTrainInfo.");
                    return 1;
                }
                if ((checkPBNNHLCRModel(trainInfo.getNNHLCRModel()) != 0) || 
                    (checkPBNNHLCRTrainInfo(trainInfo.getNNHLCRTrainInfo()) != 0)) {
                    FLLogger.i("NNHLCRModel or NNHLCRTrainInfo is invalid.");
                    return 1;
                }
                break;
            default:
                FLLogger.i(trainInfo.getModelType().toString() + " is invalid modeltype.");
                return 1;
        }
        return 0;
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
    public static int checkPBEvaluationInfo(PBEvaluationInfo evaluationInfo) {
        if (evaluationInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!evaluationInfo.hasModelType()) {
            FLLogger.i("There is no model type.");
            return 1;
        }
        switch(evaluationInfo.getModelType()) {
            case LinerHLCR:
                if (!evaluationInfo.hasLinearHLCRGlobalModel()) {
                    FLLogger.i("There is no LinearHLCRModel.");
                    return 1;
                }
                if (checkPBLinearHLCRGlobalModel(evaluationInfo.getLinearHLCRGlobalModel()) != 0) {
                    FLLogger.i("LinearHLCRModel is invalid.");
                    return 1;
                }
                break;
            case NNHLCR:
                if (!evaluationInfo.hasDataInfo()) {
                    FLLogger.i("There is no DataInfo.");
                    return 1;
                }
                if (checkPBDataInfo(evaluationInfo.getDataInfo()) != 0) {
                    FLLogger.i("DataInfo is invalid.");
                    return 1;
                }
                if (!evaluationInfo.hasNNHLCRModel()) {
                    FLLogger.i("There is no NNHLCRModel.");
                    return 1;
                }
                if (checkPBNNHLCRModel(evaluationInfo.getNNHLCRModel()) != 0) {
                    FLLogger.i("NNHLCRModel is invalid.");
                    return 1;
                }
                break;
            default:
                FLLogger.i(evaluationInfo.getModelType().toString() + " is invalid modeltype.");
                return 1;
        }
        return 0;
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
    public static int checkPBDeployInfo(PBDeployInfo deployInfo) {
        if (deployInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!deployInfo.hasAppID()) {
            FLLogger.i("There is no appID.");
            return 1;
        }
        if (!isValidID(deployInfo.getAppID())) {
            FLLogger.i("AppID is invalid.");
            return 1;
        }
        if (!deployInfo.hasModelType()) {
            FLLogger.i("There is no model type.");
            return 1;
        }
        switch(deployInfo.getModelType()) {
            case LinerHLCR:
                if (!deployInfo.hasLinearHLCRGlobalModel()) {
                    FLLogger.i("There is no LinearHLCRModel.");
                    return 1;
                }
                if (checkPBLinearHLCRGlobalModel(deployInfo.getLinearHLCRGlobalModel()) != 0) {
                    FLLogger.i("LinearHLCRModel is invalid.");
                    return 1;
                }
                break;
            case NNHLCR:
                if (!deployInfo.hasDataInfo()) {
                    FLLogger.i("There is no DataInfo.");
                    return 1;
                }
                if (checkPBDataInfo(deployInfo.getDataInfo()) != 0) {
                    FLLogger.i("DataInfo is invalid.");
                    return 1;
                }
                if (!deployInfo.hasNNHLCRModel()) {
                    FLLogger.i("There is no NNHLCRModel.");
                    return 1;
                }
                if (checkPBNNHLCRModel(deployInfo.getNNHLCRModel()) != 0) {
                    FLLogger.i("NNHLCRModel is invalid.");
                    return 1;
                }
                break;
            default:
                FLLogger.i(deployInfo.getModelType().toString() + " is invalid modeltype.");
                return 1;
        }
        return 0;
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

    public static int checkPBDeleteInfo(PBDeleteInfo deleteInfo) {
        if (deleteInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        return 0;
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
    public static int checkPBStopInfo(PBStopInfo stopInfo) {
        if (stopInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!stopInfo.hasAppID()) {
            FLLogger.i("There is no appID.");
            return 1;
        }
        if (!isValidID(stopInfo.getAppID())) {
            FLLogger.i("AppID is invalid.");
            return 1;
        }
        return 0;
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
    public static int checkPBDataInfo(PBDataInfo dataInfo) {
        if (dataInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!dataInfo.hasPreprocessParamsFileName()) {
            FLLogger.i("There is no preprocess params file name.");
            return 1;
        }
        String fileName = dataInfo.getPreprocessParamsFileName();
        if (!isValidFileName(fileName)) {
            FLLogger.i(fileName + " is an invalid file name.");
            return 1;
        }
        return 0;
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
    // out of scope in FY21
    public static int checkPBLinearHLCRGlobalModel(PBLinearHLCRGlobalModel linearHLCRGlobalModel) {
        if (linearHLCRGlobalModel == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        return 0;
    }
    public static int checkPBLinearHLCRLocalModel(PBLinearHLCRLocalModel linearHLCRLocalModel) {
        if (linearHLCRLocalModel == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        return 0;
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
    public static int checkPBNNHLCRModel(PBNNHLCRModel NNHLCRModel) {
        if (NNHLCRModel == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        List<String> weightFiles = NNHLCRModel.getNNWeightsFileNamesList();
        for (String fileName : weightFiles) {
            if (!isValidFileName(fileName)) {
                FLLogger.i(fileName + " is an invalid file name.");
                return 1;
            }
        }
        List<String> graphFiles = NNHLCRModel.getNNGraphFileNamesList();
        for (String fileName : graphFiles) {
            if (!isValidFileName(fileName)) {
                FLLogger.i(fileName + " is an invalid file name.");
                return 1;
            }
        }
        if (!NNHLCRModel.hasHLCRParamsFileName()) {
            FLLogger.i("There is no HLCR params file name.");
            return 1;
        }
        String fileName = NNHLCRModel.getHLCRParamsFileName();
        if (!isValidFileName(fileName)) {
            FLLogger.i(fileName + " is an invalid file name.");
            return 1;
        }
        return 0;
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
    // out of scope in FY21
    public static int checkPBLinearHLCRTrainInfo(PBLinearHLCRTrainInfo linearHLCRTrainInfo) {
        if (linearHLCRTrainInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        return 0;
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
    public static int checkPBNNHLCRTrainInfo(PBNNHLCRTrainInfo NNHLCRTrainInfo) {
        if (NNHLCRTrainInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!NNHLCRTrainInfo.hasHyperparamsFileName()) {
            FLLogger.i("There is no hyper params file name.");
            return 1;
        }
        String fileName = NNHLCRTrainInfo.getHyperparamsFileName();
        if (!isValidFileName(fileName)) {
            FLLogger.i(fileName + " is an invalid file name.");
            return 1;
        }
        return 0;
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

    public static int checkTaskResult(PBTaskResult taskResult, PBTaskInfo taskInfo) {
        if (taskResult == null || taskInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!taskResult.hasFLLibVersion()) {
            FLLogger.i("There is no FLLib version.");
            return 1;
        }
        if (!taskResult.getFLLibVersion().equals(taskInfo.getFLLibVersion())) {
            FLLogger.i("FLLib version is invalid.");
            return 1;
        }
        if (!taskResult.hasFLID()) {
            FLLogger.i("There is no FL ID.");
            return 1;
        }
        if ((!isValidID(taskResult.getFLID())) || taskResult.getFLID() != taskInfo.getFLID()) {
            FLLogger.i("FL ID is invalid.");
            return 1;
        }
        if (!taskResult.hasTaskID()) {
            FLLogger.i("There is no Task ID.");
            return 1;
        }
        if ((!isValidID(taskResult.getTaskID())) || taskResult.getTaskID() != taskInfo.getTaskID()) {
            FLLogger.i("Task ID is invalid.");
            return 1;
        }
        if (taskInfo.getTaskType() == TaskType.Train) {
            if (!taskResult.hasTrainResult()) {
                FLLogger.i("Train result is not found");
                return 1;
            }
            if (checkPBTrainResult(taskResult.getTrainResult(), taskInfo.getTrainInfo()) != 0) {
                FLLogger.i("Train result is invalid");
                return 1;
            }
        } else if (taskInfo.getTaskType() == TaskType.Evaluation) {
            if (!taskResult.hasEvaluationResult()) {
                FLLogger.i("Evaluation result is not found");
                return 1;
            }
            if (checkPBEvaluationResult(taskResult.getEvaluationResult(), taskInfo.getEvaluationInfo()) != 0) {
                FLLogger.i("Evaluation result is invalid");
                return 1;
            }
        }
        return 0;
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
    public static int checkPBTrainResult(PBTrainResult trainResult, PBTrainInfo trainInfo) {
        if (trainResult == null || trainInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (trainInfo.getModelType() == TaskInfo.ModelType.LinerHLCR) {
            if (!trainResult.hasLinearHLCRLocalModel()) {
                FLLogger.i("LinearHLCR result is not found");
                return 1;
            }
            if (checkPBLinearHLCRLocalModel(trainResult.getLinearHLCRLocalModel()) != 0) {
                FLLogger.i("LinearHLCR result is invalid");
                return 1;
            }
        } else if (trainInfo.getModelType() == TaskInfo.ModelType.NNHLCR) {
            if (!trainResult.hasNNHLCRModel()) {
                FLLogger.i("NNHLCR result is not found");
                return 1;
            }
            if (checkPBNNHLCRModel(trainResult.getNNHLCRModel()) != 0) {
                FLLogger.i("NNHLCR result is invalid");
                return 1;
            }
        }
        if (!trainResult.hasValidationMetrixFileName()) {
            FLLogger.i("There is no validation metrix file name.");
            return 1;
        }
        String fileName = trainResult.getValidationMetrixFileName();
        if (!isValidFileName(fileName)) {
            FLLogger.i(fileName + " is an invalid file name.");
            return 1;
        }
        return 0;
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

    public static int checkPBEvaluationResult(PBEvaluationResult evaluationResult, 
            PBEvaluationInfo evaluationInfo) {
        if (evaluationResult == null || evaluationInfo == null) {
            FLLogger.i("Input is null.");
            return 1;
        }
        if (!evaluationResult.hasEvaluationResultFileName()) {
            FLLogger.i("There is no evaluation result file name.");
            return 1;
        }
        String fileName = evaluationResult.getEvaluationResultFileName();
        if (!isValidFileName(fileName)) {
            FLLogger.i(fileName + " is an invalid file name.");
            return 1;
        }
        return 0;
    }

/*
  ####    #####  #    #  ######  #####    ####
 #    #     #    #    #  #       #    #  #
 #    #     #    ######  #####   #    #   ####
 #    #     #    #    #  #       #####        #
 #    #     #    #    #  #       #   #   #    #
  ####      #    #    #  ######  #    #   ####
*/

    public static boolean isValidID(String id) {
        if (id == null) {
            return false;
        }
        if (id.length() < MIN_ID_LEN || id.length() > MAX_ID_LEN) {
            return false;            
        }
        if (!isValidStr(id)) {
            return false;
        }
        return true;
    }

    public static boolean isValidStr(String str) {
        if (str == null) {
            return false;
        }
        Matcher m = pattern.matcher(str);
        return m.find();
    }

    public static boolean isValidFileName(String str) {
        if (str == null) {
            FLLogger.d("input is null");
            return false;
        }
        String[] strs = str.split(Pattern.quote("."));
        if (strs.length != 2) {
            FLLogger.d("Input was not split correctly. strs.length = " + strs.length);
            return false;
        }
        if (!isValidID(strs[0])) {
            FLLogger.d("File name is invalid.");
            return false;
        }
        if (strs[1].length() < MIN_EXTENSION_NAME_LEN || strs[1].length() > MAX_EXTENSION_NAME_LEN) {
            FLLogger.d("Length of extension is invalid.");
            return false;
        }
        Matcher m = simplePattern.matcher(strs[1]);
        return m.find();
    }
}
