package com.sony.fl.utils;
/**
 * @author Masanobu Jimbo
 */

import com.sony.fl.pb.TaskInfo;
import com.sony.fl.pb.TaskResult;
import com.sony.fl.pb.LinearHLCR;
import com.sony.fl.pb.NNHLCR;

public class CreatePBForTest {

/*
#######                           ###
   #       ##     ####   #    #    #     #    #  ######   ####
   #      #  #   #       #   #     #     ##   #  #       #    #
   #     #    #   ####   ####      #     # #  #  #####   #    #
   #     ######       #  #  #      #     #  # #  #       #    #
   #     #    #  #    #  #   #     #     #   ##  #       #    #
   #     #    #   ####   #    #   ###    #    #  #        ####
*/

    public static TaskInfo.PBTaskInfo createValidTaskInfoForTrain() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-train");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.Train);
        builder.setTrainInfo(createValidTrainInfoForNNHLCR());
        builder.setAppID("appID-ExitProblem");
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createValidTaskInfoForEvaluation() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-evaluation");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.Evaluation);
        builder.setEvaluationInfo(createValidEvaluationInfoForNNHLCR());
        builder.setAppID("appID-ExitProblem");
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createValidTaskInfoForDeploy() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-deploy");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.Deploy);
        builder.setDeployInfo(createValidDeployInfoForNNHLCR());
        builder.setAppID("appID-ExitProblem");
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createValidTaskInfoForDelete() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-delete");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.Delete);
        builder.setDeleteInfo(createValidDeleteInfo());
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createValidTaskInfoForStop() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-stop");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.Stop);
        builder.setStopInfo(createValidStopInfo());
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createInValidTaskInfoWithInvalidTaskID() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-train><");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.Train);
        builder.setTrainInfo(createValidTrainInfoForNNHLCR());
        builder.setAppID("appID-ExitProblem");
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createInValidTaskInfoWithInvalidFLID() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-train");
        builder.setFLID("fl><");
        builder.setTaskType(TaskInfo.TaskType.Train);
        builder.setTrainInfo(createValidTrainInfoForNNHLCR());
        builder.setAppID("appID-ExitProblem");
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createInValidTaskInfoWithoutTaskType() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-train");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.UnknownTaskType);
        builder.setTrainInfo(createValidTrainInfoForNNHLCR());
        builder.setAppID("appID-ExitProblem");
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createInValidTaskInfoWithoutTaskInfo() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-evaluation");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.Evaluation);
        builder.setAppID("appID-ExitProblem");
        return builder.build();
    }

    public static TaskInfo.PBTaskInfo createInValidTaskInfoWithoutSNEInfo() {
        TaskInfo.PBTaskInfo.Builder builder = TaskInfo.PBTaskInfo.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-evaluation");
        builder.setFLID("fl");
        builder.setTaskType(TaskInfo.TaskType.Evaluation);
        builder.setEvaluationInfo(createValidEvaluationInfoForNNHLCR());
        return builder.build();
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

    public static TaskInfo.PBTrainInfo createValidTrainInfoForLinearHLCR() {
        TaskInfo.PBTrainInfo.Builder builder = TaskInfo.PBTrainInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.LinerHLCR);
        builder.setLinearHLCRGlobalModel(createValidLinearHLCRGlobalModel());
        builder.setLinearHLCRTrainInfo(createValidLinearHLCRTrainInfo());
        return builder.build();
    }

    public static TaskInfo.PBTrainInfo createValidTrainInfoForLinearHLCRForSNE() {
        TaskInfo.PBTrainInfo.Builder builder = TaskInfo.PBTrainInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.LinerHLCR);
        builder.setLinearHLCRGlobalModel(createValidLinearHLCRGlobalModelForSNE());
        builder.setLinearHLCRTrainInfo(createValidLinearHLCRTrainInfo());
        return builder.build();
    }

    public static TaskInfo.PBTrainInfo createValidTrainInfoForNNHLCR() {
        TaskInfo.PBTrainInfo.Builder builder = TaskInfo.PBTrainInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.NNHLCR);
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setNNHLCRTrainInfo(createValidNNHLCRTrainInfo());
        builder.setDataInfo(createValidDataInfo());
        return builder.build();
    }

    public static TaskInfo.PBTrainInfo createInValidTrainInfoWithoutModelType() {
        TaskInfo.PBTrainInfo.Builder builder = TaskInfo.PBTrainInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.UnknownModelType);
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setNNHLCRTrainInfo(createValidNNHLCRTrainInfo());
        builder.setDataInfo(createValidDataInfo());
        return builder.build();
    }

    public static TaskInfo.PBTrainInfo createInValidTrainInfoWithoutTrainInfo() {
        TaskInfo.PBTrainInfo.Builder builder = TaskInfo.PBTrainInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.NNHLCR);
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setDataInfo(createValidDataInfo());
        return builder.build();
    }

    public static TaskInfo.PBTrainInfo createInValidTrainInfoWithoutModelInfo() {
        TaskInfo.PBTrainInfo.Builder builder = TaskInfo.PBTrainInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.NNHLCR);
        builder.setNNHLCRTrainInfo(createValidNNHLCRTrainInfo());
        builder.setDataInfo(createValidDataInfo());
        return builder.build();
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

    public static TaskInfo.PBEvaluationInfo createValidEvaluationInfoForLinearHLCR() {
        TaskInfo.PBEvaluationInfo.Builder builder = TaskInfo.PBEvaluationInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.LinerHLCR);
        builder.setLinearHLCRGlobalModel(createValidLinearHLCRGlobalModel());
        return builder.build();
    }

    public static TaskInfo.PBEvaluationInfo createValidEvaluationInfoForLinearHLCRForSNE() {
        TaskInfo.PBEvaluationInfo.Builder builder = TaskInfo.PBEvaluationInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.LinerHLCR);
        builder.setLinearHLCRGlobalModel(createValidLinearHLCRGlobalModelForSNE());
        return builder.build();
    }

    public static TaskInfo.PBEvaluationInfo createValidEvaluationInfoForNNHLCR() {
        TaskInfo.PBEvaluationInfo.Builder builder = TaskInfo.PBEvaluationInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.NNHLCR);
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setDataInfo(createValidDataInfo());
        return builder.build();
    }


    public static TaskInfo.PBEvaluationInfo createInValidEvaluationInfoWithoutModelType() {
        TaskInfo.PBEvaluationInfo.Builder builder = TaskInfo.PBEvaluationInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.UnknownModelType);
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setDataInfo(createValidDataInfo());
        return builder.build();
    }

    public static TaskInfo.PBEvaluationInfo createInValidEvaluationInfoWithoutModelInfo() {
        TaskInfo.PBEvaluationInfo.Builder builder = TaskInfo.PBEvaluationInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.NNHLCR);
        builder.setDataInfo(createValidDataInfo());
        return builder.build();
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

    public static TaskInfo.PBDeployInfo createValidDeployInfoForLinearHLCR() {
        TaskInfo.PBDeployInfo.Builder builder = TaskInfo.PBDeployInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.LinerHLCR);
        builder.setLinearHLCRGlobalModel(createValidLinearHLCRGlobalModel());
        // builder.setDataInfo(createValidDataInfo());
        builder.setAppID("valid-deploy-info-for-linearHLCR");
        return builder.build();
    }

    public static TaskInfo.PBDeployInfo createValidDeployInfoForLinearHLCRForSNE() {
        TaskInfo.PBDeployInfo.Builder builder = TaskInfo.PBDeployInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.LinerHLCR);
        builder.setLinearHLCRGlobalModel(createValidLinearHLCRGlobalModelForSNE());
        // builder.setDataInfo(createValidDataInfo());
        builder.setAppID("valid-deploy-info-for-linearHLCR");
        return builder.build();
    }

    public static TaskInfo.PBDeployInfo createValidDeployInfoForLinearHLCRForSNE_python_test_case() {
        TaskInfo.PBDeployInfo.Builder builder = TaskInfo.PBDeployInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.LinerHLCR);
        builder.setLinearHLCRGlobalModel(createValidLinearHLCRGlobalModelForSNE_python_test_case());
        // builder.setDataInfo(createValidDataInfo());
        builder.setAppID("valid-deploy-info-for-linearHLCR");
        return builder.build();
    }

    public static TaskInfo.PBDeployInfo createValidDeployInfoForNNHLCR() {
        TaskInfo.PBDeployInfo.Builder builder = TaskInfo.PBDeployInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.NNHLCR);
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setDataInfo(createValidDataInfo());
        builder.setAppID("valid-deploy-info-for-NNHLCR");
        return builder.build();
    }

    public static TaskInfo.PBDeployInfo createInValidDeployInfoWithoutModelType() {
        TaskInfo.PBDeployInfo.Builder builder = TaskInfo.PBDeployInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.UnknownModelType);
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setDataInfo(createValidDataInfo());
        builder.setAppID("valid-deploy-info-for-NNHLCR");
        return builder.build();
    }

    public static TaskInfo.PBDeployInfo createInValidDeployInfoWithoutModelInfo() {
        TaskInfo.PBDeployInfo.Builder builder = TaskInfo.PBDeployInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.NNHLCR);
        builder.setDataInfo(createValidDataInfo());
        builder.setAppID("valid-deploy-info-for-NNHLCR");
        return builder.build();
    }

    public static TaskInfo.PBDeployInfo createInValidDeployInfoWithInvalidAppID() {
        TaskInfo.PBDeployInfo.Builder builder = TaskInfo.PBDeployInfo.newBuilder();
        builder.setModelType(TaskInfo.ModelType.NNHLCR);
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setDataInfo(createValidDataInfo());
        builder.setAppID("valid-deploy-info-for-NNHLCR!!!");
        return builder.build();
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

    public static TaskInfo.PBDeleteInfo createValidDeleteInfo() {
        TaskInfo.PBDeleteInfo.Builder builder = TaskInfo.PBDeleteInfo.newBuilder();
        return builder.build();
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
    // cf : createValidDeployInfoForNNHLCR
    public static TaskInfo.PBStopInfo createValidStopInfo() {
        TaskInfo.PBStopInfo.Builder builder = TaskInfo.PBStopInfo.newBuilder();
        builder.setAppID("valid-deploy-info-for-NNHLCR");
        return builder.build();
    }

    public static TaskInfo.PBStopInfo createInValidStopInfoWithInvalidAppID() {
        TaskInfo.PBStopInfo.Builder builder = TaskInfo.PBStopInfo.newBuilder();
        builder.setAppID("invalid-stop-info!!!");
        return builder.build();
    }

/*
#                                               #     # #        #####  ######
#           #    #    #  ######    ##    #####  #     # #       #     # #     #
#           #    ##   #  #        #  #   #    # #     # #       #       #     #
#           #    # #  #  #####   #    #  #    # ####### #       #       ######
#           #    #  # #  #       ######  #####  #     # #       #       #   #
#           #    #   ##  #       #    #  #   #  #     # #       #     # #    #
#######     #    #    #  ######  #    #  #    # #     # #######  #####  #     #
*/
    public static LinearHLCR.PBLinearHLCRGlobalModel createValidLinearHLCRGlobalModelForSNE() {
        LinearHLCR.PBLinearHLCRGlobalModel.Builder builder = LinearHLCR.PBLinearHLCRGlobalModel.newBuilder();
        builder.setHLCRParamsFileName("LinearHLCRGlobalWeight.json");               // server.globalWeight
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel0.json");  // server.linearModels[0]
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel1.json");  // server.linearModels[1]
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel2.json");  // server.linearModels[2]
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel3.json");  // server.linearModels[3]
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel4.json");  // server.linearModels[4]
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel5.json");  // server.linearModels[5]
        return builder.build();
    }
    public static LinearHLCR.PBLinearHLCRGlobalModel createValidLinearHLCRGlobalModelForSNE_python_test_case() {
        LinearHLCR.PBLinearHLCRGlobalModel.Builder builder = LinearHLCR.PBLinearHLCRGlobalModel.newBuilder();
        builder.setHLCRParamsFileName("LinearHLCRGlobalWeight.json");               // server.globalWeight
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel0.json");  // server.linearModels[0]
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel1.json");  // server.linearModels[1]
        return builder.build();
    }
    public static LinearHLCR.PBLinearHLCRGlobalModel createValidLinearHLCRGlobalModel() {
        LinearHLCR.PBLinearHLCRGlobalModel.Builder builder = LinearHLCR.PBLinearHLCRGlobalModel.newBuilder();
        builder.setHLCRParamsFileName("LinearHLCRGlobalWeight.json");               // server.globalWeight
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel.json");   // server.linearModels[0]
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel.json");   // server.linearModels[1]
        return builder.build();
    }
    public static LinearHLCR.PBLinearHLCRLocalModel createValidLinearHLCRLocalModel() {
        LinearHLCR.PBLinearHLCRLocalModel.Builder builder = LinearHLCR.PBLinearHLCRLocalModel.newBuilder();
        return builder.build();
    }
    
    // TODO : additional implementation
    public static LinearHLCR.PBLinearHLCRTrainInfo createValidLinearHLCRTrainInfo() {
        LinearHLCR.PBLinearHLCRTrainInfo.Builder builder = LinearHLCR.PBLinearHLCRTrainInfo.newBuilder();
        builder.setHyperparamsFileName("LinearHLCRTrainHyperParams.json");
        return builder.build();
    }

/*
#     # #     # #     # #        #####  ######
##    # ##    # #     # #       #     # #     #
# #   # # #   # #     # #       #       #     #
#  #  # #  #  # ####### #       #       ######
#   # # #   # # #     # #       #       #   #
#    ## #    ## #     # #       #     # #    #
#     # #     # #     # #######  #####  #     #
*/    

    public static NNHLCR.PBNNHLCRModel createValidNNHLCRModel() {
        NNHLCR.PBNNHLCRModel.Builder builder = NNHLCR.PBNNHLCRModel.newBuilder();
        builder.setHLCRParamsFileName("HLCR_Param.dat");
        builder.addNNWeightsFileNames("cluster1.protobuf");
        builder.addNNWeightsFileNames("cluster2.protobuf");
        builder.addNNGraphFileNames("graph.nntxt");
        builder.addNNGraphFileNames("graph.nntxt");
        return builder.build();
    }

    public static NNHLCR.PBNNHLCRModel createInvalidNNHLCRModelWithInvalidParamFile() {
        NNHLCR.PBNNHLCRModel.Builder builder = NNHLCR.PBNNHLCRModel.newBuilder();
        builder.setHLCRParamsFileName("bad file name");
        builder.addNNWeightsFileNames("cluster1.protobuf");
        builder.addNNWeightsFileNames("cluster2.protobuf");
        builder.addNNGraphFileNames("graph.nntxt");
        builder.addNNGraphFileNames("graph.nntxt");
        return builder.build();
    }

    public static NNHLCR.PBNNHLCRModel createInvalidNNHLCRModelWithInvalidNNFile() {
        NNHLCR.PBNNHLCRModel.Builder builder = NNHLCR.PBNNHLCRModel.newBuilder();
        builder.setHLCRParamsFileName("HLCR_Param.dat");
        builder.addNNWeightsFileNames("cluster1.protobuf");
        builder.addNNWeightsFileNames("bad file name");
        builder.addNNGraphFileNames("graph.nntxt");
        builder.addNNGraphFileNames("graph.nntxt");
        return builder.build();
    }

    public static NNHLCR.PBNNHLCRTrainInfo createValidNNHLCRTrainInfo() {
        NNHLCR.PBNNHLCRTrainInfo.Builder builder = NNHLCR.PBNNHLCRTrainInfo.newBuilder();
        builder.setHyperparamsFileName("Hyper_Param.dat");
        return builder.build();
    }

    public static NNHLCR.PBNNHLCRTrainInfo createInValidNNHLCRTrainInfoWithInvalidHyperParamFile() {
        NNHLCR.PBNNHLCRTrainInfo.Builder builder = NNHLCR.PBNNHLCRTrainInfo.newBuilder();
        builder.setHyperparamsFileName("bad file name");
        return builder.build();
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

    public static TaskInfo.PBDataInfo createValidDataInfo() {
        TaskInfo.PBDataInfo.Builder builder = TaskInfo.PBDataInfo.newBuilder();
        builder.setPreprocessParamsFileName("preprocess_params.dat");
        return builder.build();
    }

    public static TaskInfo.PBDataInfo createInvalidDataInfoWithInvalidPreprocessParamFile() {
        TaskInfo.PBDataInfo.Builder builder = TaskInfo.PBDataInfo.newBuilder();
        builder.setPreprocessParamsFileName("bad file name");
        return builder.build();
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
    // createValidTaskInfoForTrain()
    public static TaskResult.PBTaskResult createValidTaskResultForTrain() {
        TaskResult.PBTaskResult.Builder builder = TaskResult.PBTaskResult.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-train");
        builder.setFLID("fl");
        builder.setTrainResult(createValidTrainTaskResultForNNHLCR());
        return builder.build();
    }

    public static TaskResult.PBTaskResult createInvalidTaskResultForTrainWithInvalidTaskID() {
        TaskResult.PBTaskResult.Builder builder = TaskResult.PBTaskResult.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("bad taskID");
        builder.setFLID("fl");
        builder.setTrainResult(createValidTrainTaskResultForNNHLCR());
        return builder.build();
    }

    public static TaskResult.PBTaskResult createInValidTaskResultForTrainWithInvalidFLID() {
        TaskResult.PBTaskResult.Builder builder = TaskResult.PBTaskResult.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-train");
        builder.setFLID("bad FLID");
        builder.setTrainResult(createValidTrainTaskResultForNNHLCR());
        return builder.build();
    }

    public static TaskResult.PBTaskResult createInvalidTaskResultForTrainWithoutTrainResult() {
        TaskResult.PBTaskResult.Builder builder = TaskResult.PBTaskResult.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-train");
        builder.setFLID("fl");
        return builder.build();
    }

    // createValidTaskInfoForEvaluation()
    public static TaskResult.PBTaskResult createValidTaskResultForEvaluation() {
        TaskResult.PBTaskResult.Builder builder = TaskResult.PBTaskResult.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-evaluation");
        builder.setFLID("fl");
        builder.setEvaluationResult(createValidEvaluationTaskResultWithValidEvaluationTask());
        return builder.build();
    }

    public static TaskResult.PBTaskResult createInvalidTaskResultForEvaluationWithoutEvaluationResult() {
        TaskResult.PBTaskResult.Builder builder = TaskResult.PBTaskResult.newBuilder();
        builder.setFLLibVersion("0.0.1");
        builder.setTaskID("task-info-for-evaluation");
        builder.setFLID("fl");
        return builder.build();
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
    // createValidTrainInfoForLinearHLCR()
    public static TaskResult.PBTrainResult createValidTrainTaskResultForLinearHLCR() {
        TaskResult.PBTrainResult.Builder builder = TaskResult.PBTrainResult.newBuilder();
        builder.setLinearHLCRLocalModel(createValidLinearHLCRLocalModel());
        builder.setValidationMetrixFileName("validatation_metirix.dat");
        return builder.build();
    }

    // createValidTrainInfoForNNHLCR()
    public static TaskResult.PBTrainResult createValidTrainTaskResultForNNHLCR() {
        TaskResult.PBTrainResult.Builder builder = TaskResult.PBTrainResult.newBuilder();
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setValidationMetrixFileName("validatation_metirix.dat");
        return builder.build();
    }

    public static TaskResult.PBTrainResult createInvalidTrainTaskResultForNNHLCRWithInvalidValidFile() {
        TaskResult.PBTrainResult.Builder builder = TaskResult.PBTrainResult.newBuilder();
        builder.setNNHLCRModel(createValidNNHLCRModel());
        builder.setValidationMetrixFileName("bad file name");
        return builder.build();
    }

    public static TaskResult.PBTrainResult createInvalidTrainTaskResultForNNHLCRWithoutNNHLCRModel() {
        TaskResult.PBTrainResult.Builder builder = TaskResult.PBTrainResult.newBuilder();
        builder.setLinearHLCRLocalModel(createValidLinearHLCRLocalModel()); // wrong type model
        builder.setValidationMetrixFileName("validatation_metirix.dat");
        return builder.build();
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

    public static TaskResult.PBEvaluationResult createValidEvaluationTaskResultWithValidEvaluationTask() {
        TaskResult.PBEvaluationResult.Builder builder = TaskResult.PBEvaluationResult.newBuilder();
        builder.setEvaluationResultFileName("Evaluation_Result.dat");
        return builder.build();
    }

    public static TaskResult.PBEvaluationResult createInvalidEvaluationTaskResultWithInvalidFileName() {
        TaskResult.PBEvaluationResult.Builder builder = TaskResult.PBEvaluationResult.newBuilder();
        builder.setEvaluationResultFileName("bad file name");
        return builder.build();
    }

}
