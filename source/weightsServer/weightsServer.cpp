// ---------------------------------------------------------------------
//
//  weightsServer.cpp
//
//  Created by ingo on 01/01/18.
//  Copyright (c) 2018 Ingo Clemens. All rights reserved.
//
// ---------------------------------------------------------------------

#include "weightsServer.h"

MTypeId weightsServer::id(0x0011C1C9);

MObject weightsServer::active;
MObject weightsServer::alpha;
MObject weightsServer::colorR;
MObject weightsServer::colorG;
MObject weightsServer::colorB;
MObject weightsServer::colorA;
MObject weightsServer::curve;
MObject weightsServer::curveRamp;
MObject weightsServer::curveRampUVal;
MObject weightsServer::flood;
MObject weightsServer::globalInfluenceScale;
MObject weightsServer::globalRadius;
MObject weightsServer::globalScale;
MObject weightsServer::influence;
MObject weightsServer::inputComponentsList;
MObject weightsServer::inputComponents;
MObject weightsServer::inputTransfer;
MObject weightsServer::invert;
MObject weightsServer::invertList;
MObject weightsServer::matrix;
MObject weightsServer::matrixList;
MObject weightsServer::mesh;
MObject weightsServer::outputTransfer;
MObject weightsServer::radius;
MObject weightsServer::restParentMatrix;
MObject weightsServer::scale;
MObject weightsServer::texture;
MObject weightsServer::transferWeights;
MObject weightsServer::useShape;
MObject weightsServer::useTransfer;
MObject weightsServer::useUV;
MObject weightsServer::weights;
MObject weightsServer::weightList;
MObject weightsServer::worldSpace;

// ---------------------------------------------------------------------
// creator
// ---------------------------------------------------------------------

weightsServer::weightsServer()
{}

weightsServer::~weightsServer()
{}

void* weightsServer::creator()
{
    return new weightsServer();
}

// ---------------------------------------------------------------------
// initialize the attributes
// ---------------------------------------------------------------------

MStatus weightsServer::initialize()
{
    //
    // MFnNumericAttribute
    //

    MFnNumericAttribute nAttr;

    active = nAttr.create("active", "ac", MFnNumericData::kBoolean);

    alpha = nAttr.create("alpha", "a", MFnNumericData::kDouble);
    nAttr.setKeyable(false);

    colorR = nAttr.create("colorR", "cr", MFnNumericData::kBoolean);
    nAttr.setDefault(true);
    nAttr.setKeyable(true);

    colorG = nAttr.create("colorG", "cg", MFnNumericData::kBoolean);
    nAttr.setDefault(true);
    nAttr.setKeyable(true);

    colorB = nAttr.create("colorB", "cb", MFnNumericData::kBoolean);
    nAttr.setDefault(true);
    nAttr.setKeyable(true);

    colorA = nAttr.create("colorA", "ca", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setKeyable(true);

    flood = nAttr.create("flood", "f", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setHidden(true);

    globalInfluenceScale = nAttr.create("globalInfluenceScale", "gis", MFnNumericData::kDouble);
    nAttr.setDefault(1.0);
    nAttr.setKeyable(true);
    nAttr.setSoftMin(0.0);
    nAttr.setSoftMax(1.0);

    globalRadius = nAttr.create("globalRadius", "gr", MFnNumericData::kDouble);
    nAttr.setDefault(1.0);
    nAttr.setKeyable(true);
    nAttr.setSoftMin(0);
    nAttr.setSoftMax(50);

    globalScale = nAttr.create("globalScale", "gs", MFnNumericData::kDouble);
    nAttr.setDefault(1.0);
    nAttr.setKeyable(true);
    nAttr.setSoftMin(0.0);
    nAttr.setSoftMax(1.0);

    invert = nAttr.create("invert", "iv", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setKeyable(true);

    invertList = nAttr.create("invertList", "ivl", MFnNumericData::kBoolean);
    nAttr.setArray(true);
    nAttr.setUsesArrayDataBuilder(true);

    radius = nAttr.create("radius", "rad", MFnNumericData::kDouble);

    scale = nAttr.create("scale", "sc", MFnNumericData::kDouble);

    texture = nAttr.createColor("texture", "tx");
    nAttr.setKeyable(true);

    transferWeights = nAttr.create("transferWeights", "tw", MFnNumericData::kDouble, 0.0);
    nAttr.setHidden(true);
    nAttr.setArray(true);
    nAttr.setUsesArrayDataBuilder(true);

    useShape = nAttr.create("useShape", "us", MFnNumericData::kBoolean);

    useTransfer = nAttr.create("useTransfer", "ut", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setKeyable(true);

    useUV = nAttr.create("useUV", "uv", MFnNumericData::kBoolean);
    nAttr.setDefault(true);
    nAttr.setKeyable(true);

    weights = nAttr.create("weights", "w", MFnNumericData::kFloat, 0.0);
    nAttr.setHidden(true);
    nAttr.setArray(true);
    nAttr.setUsesArrayDataBuilder(true);

    worldSpace = nAttr.create("worldSpace", "ws", MFnNumericData::kBoolean);

    //
    // MFnMatrixAttribute
    //

    MFnMatrixAttribute mAttr;

    matrix = mAttr.create("matrix", "m");
    mAttr.setHidden(true);

    matrixList = mAttr.create("matrixList", "ml");
    mAttr.setHidden(true);
    mAttr.setArray(true);

    restParentMatrix = mAttr.create("restParentMatrix", "rpm");
    mAttr.setHidden(true);

    //
    // MFnTypedAttribute
    //

    MFnTypedAttribute tAttr;

    inputComponents = tAttr.create("inputComponents", "ic", MFnComponentListData::kComponentList);

    curve = tAttr.create("curve", "crv", MFnData::kNurbsCurve);
    tAttr.setHidden(true);
    tAttr.setArray(true);
    tAttr.setUsesArrayDataBuilder(true);

    inputTransfer = tAttr.create("inputTransfer", "it", MFnData::kPluginGeometry);
    tAttr.setHidden(true);

    mesh = tAttr.create("mesh", "msh", MFnData::kMesh);
    tAttr.setHidden(true);
    tAttr.setArray(true);
    tAttr.setUsesArrayDataBuilder(true);

    //
    // MFnCompoundAttribute
    //

    MFnCompoundAttribute cAttr;

    influence = cAttr.create("influence", "inf");
    cAttr.setArray(true);
    cAttr.setUsesArrayDataBuilder(true);
    cAttr.addChild(matrix);
    cAttr.addChild(restParentMatrix);
    cAttr.addChild(active);
    cAttr.addChild(radius);
    cAttr.addChild(scale);
    cAttr.addChild(worldSpace);
    cAttr.addChild(useShape);

    inputComponentsList = cAttr.create("inputComponentsList", "icl");
    cAttr.setHidden(true);
    cAttr.setArray(true);
    cAttr.setUsesArrayDataBuilder(true);
    cAttr.addChild(inputComponents);

    outputTransfer = cAttr.create("outputTransfer", "ot");
    cAttr.setHidden(true);
    cAttr.setArray(true);
    cAttr.setUsesArrayDataBuilder(true);
    cAttr.addChild(transferWeights);

    weightList = cAttr.create("weightList", "wl");
    cAttr.setHidden(true);
    cAttr.setArray(true);
    cAttr.setUsesArrayDataBuilder(true);
    cAttr.addChild(weights);

    //
    // MRampAttribute
    //

    MRampAttribute rAttr;

    curveRamp = rAttr.createCurveRamp("falloff", "fo");

    curveRampUVal = rAttr.createCurveRamp("curveFalloff", "cfo");

    // -----------------------------------------------------------------
    // add attributes (order matters)
    // -----------------------------------------------------------------

    addAttribute(globalRadius);
    addAttribute(globalScale);
    addAttribute(globalInfluenceScale);
    addAttribute(invert);
    addAttribute(flood);
    addAttribute(curveRamp);
    addAttribute(curveRampUVal);
    addAttribute(texture);
    addAttribute(alpha);
    addAttribute(useUV);
    addAttribute(colorR);
    addAttribute(colorG);
    addAttribute(colorB);
    addAttribute(colorA);
    addAttribute(mesh);
    addAttribute(curve);
    addAttribute(inputComponentsList);
    addAttribute(inputComponents);
    addAttribute(weightList);
    addAttribute(weights);
    addAttribute(matrixList);
    addAttribute(invertList);
    addAttribute(influence);
    addAttribute(matrix);
    addAttribute(restParentMatrix);
    addAttribute(active);
    addAttribute(radius);
    addAttribute(scale);
    addAttribute(worldSpace);
    addAttribute(useShape);
    addAttribute(useTransfer);
    addAttribute(inputTransfer);
    addAttribute(outputTransfer);
    addAttribute(transferWeights);

    // -----------------------------------------------------------------
    // affects
    // -----------------------------------------------------------------

    attributeAffects(active, weightList);
    attributeAffects(alpha, weightList);
    attributeAffects(colorR, weightList);
    attributeAffects(colorG, weightList);
    attributeAffects(colorB, weightList);
    attributeAffects(colorA, weightList);
    attributeAffects(curve, weightList);
    attributeAffects(curveRamp, weightList);
    attributeAffects(curveRampUVal, weightList);
    attributeAffects(flood, weightList);
    attributeAffects(globalInfluenceScale, weightList);
    attributeAffects(globalRadius, weightList);
    attributeAffects(globalScale, weightList);
    attributeAffects(influence, weightList);
    attributeAffects(invert, weightList);
    attributeAffects(invertList, weightList);
    attributeAffects(matrix, weightList);
    attributeAffects(matrixList, weightList);
    attributeAffects(mesh, weightList);
    attributeAffects(radius, weightList);
    attributeAffects(scale, weightList);
    attributeAffects(texture, weightList);
    attributeAffects(useShape, weightList);
    attributeAffects(useUV, weightList);
    attributeAffects(worldSpace, weightList);

    attributeAffects(inputTransfer, transferWeights);
    attributeAffects(useTransfer, transferWeights);

    return MS::kSuccess;
}


// ---------------------------------------------------------------------
// initialize the ramp attribute
// ---------------------------------------------------------------------

void weightsServer::postConstructor()
{
    MStatus status;
    MObject thisNode = this->thisMObject();

    postConstructor_init_curveRamp(thisNode, curveRamp, 0, 0.0f, 1.0f, 2);
    postConstructor_init_curveRamp(thisNode, curveRamp, 1, 1.0f, 0.0f, 2);

    postConstructor_init_curveRamp(thisNode, curveRampUVal, 0, 0.0f, 0.0f, 2);
    postConstructor_init_curveRamp(thisNode, curveRampUVal, 1, 0.5f, 1.0f, 2);
    postConstructor_init_curveRamp(thisNode, curveRampUVal, 2, 1.0f, 0.0f, 2);
}

MStatus weightsServer::postConstructor_init_curveRamp(MObject& nodeObj,
                                                      MObject& rampObj,
                                                      int index,
                                                      float position,
                                                      float value,
                                                      int interpolation)
{
    MStatus status;

    MPlug rampPlug(nodeObj, rampObj);
    MPlug elementPlug = rampPlug.elementByLogicalIndex((unsigned)index, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MPlug positionPlug = elementPlug.child(0, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    status = positionPlug.setFloat(position);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MPlug valuePlug = elementPlug.child(1);
    status = valuePlug.setFloat(value);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MPlug interpolationPlug = elementPlug.child(2);
    interpolationPlug.setInt(interpolation);

    return MS::kSuccess;
}


// ---------------------------------------------------------------------
// compute
// ---------------------------------------------------------------------

MStatus weightsServer::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status = MS::kSuccess;

    unsigned int i, j, k;

    MObject thisNode = this->thisMObject();

    // -----------------------------------------------------------------
    // attributes
    // -----------------------------------------------------------------

    MDataHandle alphaData = data.inputValue(alpha, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double alphaVal = alphaData.asDouble();

    MDataHandle colorRData = data.inputValue(colorR, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool colorRVal = colorRData.asBool();

    MDataHandle colorGData = data.inputValue(colorG, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool colorGVal = colorGData.asBool();

    MDataHandle colorBData = data.inputValue(colorB, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool colorBVal = colorBData.asBool();

    MDataHandle colorAData = data.inputValue(colorA, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool colorAVal = colorAData.asBool();

    MArrayDataHandle curveArrayDataHandle = data.inputArrayValue(curve, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MRampAttribute curveAttr(thisNode, curveRamp, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MRampAttribute curveUAttr(thisNode, curveRampUVal, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    /* MDataHandle floodData = data.inputValue(flood, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool floodVal = floodData.asBool(); */

    MDataHandle globalInfluenceScaleData = data.inputValue(globalInfluenceScale, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double globalInfluenceScaleVal = globalInfluenceScaleData.asDouble();

    MDataHandle globalRadiusData = data.inputValue(globalRadius, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double globalRadiusVal = globalRadiusData.asDouble();

    MDataHandle globalScaleData = data.inputValue(globalScale, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double globalScaleVal = globalScaleData.asDouble();

    MArrayDataHandle influenceArrayDataHandle = data.inputArrayValue(influence, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MArrayDataHandle inputComponentsListArrayDataHandle = data.inputArrayValue(inputComponentsList, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle invertData = data.inputValue(invert, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool invertVal = invertData.asBool();

    MArrayDataHandle invertListArrayDataHandle = data.inputArrayValue(invertList, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MArrayDataHandle matrixListArrayDataHandle = data.inputArrayValue(matrixList, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MArrayDataHandle meshArrayDataHandle = data.inputArrayValue(mesh, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle textureData = data.inputValue(texture, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MFloatVector textureVec = textureData.asFloatVector();

    MDataHandle useTransferData = data.inputValue(useTransfer, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool useTransferVal = useTransferData.asBool();

    MDataHandle useUVData = data.inputValue(useUV, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool useUV = useUVData.asBool();

    // -------------------------------------------------------------
    // switch if transfer mode is used
    // -------------------------------------------------------------

    if (useTransferVal && (plug == transferWeights || plug == outputTransfer))
    {
        // Check for the type of connected input deformer to define
        // how to retrieve the weights.
        MPlug inputTransferPlug(thisNode, inputTransfer);
        MPlugArray inputPlugArray;
        inputTransferPlug.connectedTo(inputPlugArray, true, false, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MObject inDeformerObj;
        // Check for the array length to prevent a crash when
        // deleting the node without removing any connections to the
        // network first.
        if (inputPlugArray.length())
            inDeformerObj = inputPlugArray[0].node();
        MFnDependencyNode inDeformerFn(inDeformerObj);

        //
        // skin cluster
        //
        if (inDeformerFn.typeName() == "skinCluster")
        {
            // Find the dagPath of the deformed mesh to get the skin
            // cluster weights.
            // The easiest way would be to search downstream from
            // the input deformer but since it's connected to the
            // weights server the target mesh for the transfer
            // weights is found which is usally a different mesh.
            // Therefore it's better to go upstream, find the
            // intermediate shape node and the deformed shape as
            // it's sibling under the same transform node.
            MDagPath skinDag;
            unsigned int numVertices = 0;

            MItDependencyGraph dependIter(inDeformerObj, MFn::kMesh,
                                          MItDependencyGraph::kUpstream,
                                          MItDependencyGraph::kDepthFirst,
                                          MItDependencyGraph::kNodeLevel);

            // Iterate through the history to find the intermediate
            // shape.
            for (; !dependIter.isDone(); dependIter.next())
            {
                MObject currentObj = dependIter.currentItem();
                MFnDagNode currentFn(currentObj, &status);
                if (status && currentFn.isIntermediateObject())
                {
                    // The intermediate shape cannot be used to
                    // define the skin cluster. Instead go to the
                    // transform node and then get the deformed
                    // shape.
                    MDagPath::getAPathTo(currentObj, skinDag);
                    MDagPath::getAPathTo(skinDag.transform(), skinDag);
                    skinDag.extendToShape();
                    MFnMesh skinMeshFn(skinDag);
                    numVertices = (unsigned)skinMeshFn.numVertices();
                }
            }

            MDoubleArray skinWeights;
            unsigned int influenceCount;

            // Create the object for all mesh indices.
            MFnSingleIndexedComponent compFn;
            MObject vtxCompObj = compFn.create(MFn::kMeshVertComponent);
            MFnMesh meshFn(skinDag);
            compFn.setCompleteData((int)numVertices);

            MFnSkinCluster skinFn(inDeformerObj, &status);
            skinFn.getWeights(skinDag, vtxCompObj, skinWeights, influenceCount);

            // Pass the weights for each influence to the according
            // transfer output index.
            for (j = 0; j < influenceCount; j ++)
            {
                MPlug weightsPlug(thisNode, transferWeights);
                weightsPlug.selectAncestorLogicalIndex(j, outputTransfer);

                // Create the handles and array builder for the weights
                // plug. Using the MArrayBuilder to collect the weights
                // and then set the output weights array in a single
                // step is much faster than setting the value for each
                // weight index individually.
                MDataHandle weightsHandle = weightsPlug.constructHandle(data);
                MArrayDataHandle weightsArrayHandle(weightsHandle);
                MArrayDataBuilder weightsBuilder = weightsArrayHandle.builder(&status);
                CHECK_MSTATUS_AND_RETURN_IT(status);

                for (k = 0; k < numVertices; k ++)
                {
                    MDataHandle weightsIdHandle = weightsBuilder.addElement(k);
                    weightsIdHandle.set(skinWeights[k * influenceCount + j]);
                }

                weightsArrayHandle.set(weightsBuilder);
                weightsPlug.setValue(weightsHandle);
                weightsPlug.destructHandle(weightsHandle);

                data.setClean(weightsPlug);
            }
        }

        return status;
    }

    // -----------------------------------------------------------------
    // get the data set for each influence
    // -----------------------------------------------------------------

    MDataHandle influenceDataHandle;

    // Get the number of influences and their indices.
    MPlug influencePlug(thisNode, influence);
    MIntArray influenceIndices;
    influencePlug.getExistingArrayAttributeIndices(influenceIndices);
    unsigned int influenceCount = influenceIndices.length();

    // Prepare the arrays holding the data for each influence.
    MIntArray usedElements(influenceCount, 0);
    MDoubleArray radiusArray(influenceCount, -1);
    MDoubleArray scaleArray(influenceCount, 1);
    MIntArray useWorldSpace(influenceCount, 0);
    MIntArray useShapeNode(influenceCount, 0);
    MIntArray isActive(influenceCount, 1);

    MIntArray shapeType(influenceCount, 0);
    MDagPathArray shapeDagPaths(influenceCount, MDagPath());

    MVectorArray influenceVec(influenceCount, MVector(0.0, 0.0, 0.0));
    MMatrixArray influenceMatrixArray(influenceCount);
    MMatrixArray parentMatArray(influenceCount);
    MMatrixArray restParentMatArray(influenceCount);
    MPointArray bboxMin(influenceCount, MPoint());
    MPointArray bboxMax(influenceCount, MPoint());

    MMeshIntersector intersector;

    for (i = 0; i < influenceCount; i ++)
    {
        unsigned int index = (unsigned)influenceIndices[i];

        MPlug influenceElementPlug = influencePlug.elementByLogicalIndex(index);

        MPlug matrixPlug = influenceElementPlug.child(0);

        MPlugArray connectedPlugs;
        if (matrixPlug.isConnected())
        {
            // Get the next element in the data array.
            influenceArrayDataHandle.jumpToElement(i);
            influenceDataHandle = influenceArrayDataHandle.inputValue(&status);
            CHECK_MSTATUS_AND_RETURN_IT(status);

            MDataHandle activeHandle = influenceDataHandle.child(active);
            isActive[i] = (int)activeHandle.asBool();

            if (isActive[i])
            {
                MDagPath influenceDag;

                // Get the node connected to the matrix or curve plug.
                matrixPlug.connectedTo(connectedPlugs, true, false);
                MObject influenceObj = connectedPlugs[0].node();
                MDagPath::getAPathTo(influenceObj, influenceDag);

                // Get the rest parent matrix.
                MDataHandle restParentMatrixHandle = influenceDataHandle.child(restParentMatrix);
                MMatrix restParentMatrix = restParentMatrixHandle.asMatrix();

                MMatrix inclusiveMat = influenceDag.inclusiveMatrix();
                MMatrix exclusiveMat = influenceDag.exclusiveMatrix();
                MMatrix exclusiveMatInv = influenceDag.exclusiveMatrixInverse();

                // Find the mesh shape node or curve shape node.
                unsigned int shapeNum;
                influenceDag.numberOfShapesDirectlyBelow(shapeNum);
                MDagPath shapeDag(influenceDag);
                if (shapeNum)
                {
                    shapeDag.extendToShapeDirectlyBelow(0);
                    if (shapeDag.hasFn(MFn::kMesh))
                    {
                        shapeType[i] = shapeDag.apiType();
                        shapeDagPaths.set(shapeDag, i);

                        MFnMesh mesh(shapeDag);
                        MBoundingBox bbox = mesh.boundingBox();
                        // If the influence it not a child of the world
                        // the bounding box needs to get transformed
                        // to represent the local transformation of the
                        // influence without the parent transformation.
                        // This is important for the closest point
                        // calculation which is also happening in local
                        // space rather than parent space.
                        bbox.transformUsing(inclusiveMat * exclusiveMatInv * restParentMatrix);
                        bboxMin.set(bbox.min(), i);
                        bboxMax.set(bbox.max(), i);
                    }
                    else if (shapeDag.hasFn(MFn::kNurbsCurve))
                    {
                        shapeType[i] = shapeDag.apiType();
                        shapeDagPaths.set(shapeDag, i);

                        MFnNurbsCurve curve(shapeDag);
                        MBoundingBox bbox = curve.boundingBox();
                        bbox.transformUsing(inclusiveMat);
                        bboxMin.set(bbox.min(), i);
                        bboxMax.set(bbox.max(), i);
                    }
                }

                usedElements[i] = 1;

                // Get the current world space position.
                MDataHandle matrixHandle = matrixPlug.asMDataHandle();
                MMatrix influenceMatrix = matrixHandle.asMatrix();

                // Store the parent and rest parent matrix for the
                // mesh and nurbs curve shape calculation.
                parentMatArray.set(exclusiveMat, i);
                restParentMatArray.set(restParentMatrix, i);

                MDataHandle worldSpaceHandle = influenceDataHandle.child(worldSpace);
                useWorldSpace[i] = (int)worldSpaceHandle.asBool();

                if (!useWorldSpace[i])
                    influenceMatrix *= exclusiveMatInv * restParentMatrix;
                influenceMatrixArray.set(influenceMatrix, i);

                MTransformationMatrix influenceTransMat(influenceMatrix);
                influenceVec.set(influenceTransMat.getTranslation(MSpace::kWorld), i);

                // Get the other influence values
                MDataHandle radiusHandle = influenceDataHandle.child(radius);
                radiusArray[i] = radiusHandle.asDouble();

                MDataHandle scaleHandle = influenceDataHandle.child(scale);
                scaleArray[i] = scaleHandle.asDouble();

                MDataHandle useShapeHandle = influenceDataHandle.child(useShape);
                useShapeNode[i] = (int)useShapeHandle.asBool();
            }
        }
    }

    // -----------------------------------------------------------------
    // get the weight list indices which need to get computed
    // -----------------------------------------------------------------

    // In order to be able to handle multiple blend shape channels or
    // deformers it's necessary to generate separate weight lists,
    // therefore the weightList output attribute exists as an array.
    // For creating the weights for each list the index of the current
    // weights plug needs to be known. This index can be derived from
    // the indexed weightList plug which is the parent of the current
    // weights plug.

    MPlug weightsPlug(thisNode, weights);
    MIntArray outputIndices;

    // DG Evaluation:
    // In this evaluation mode the computation request comes from the
    // weightList[].weights plug. Therefore the weight list index can be
    // found by looking at the logical index of the parent plug, which
    // is the weightList plug itself.
    if (plug == weights)
    {
        MPlug parentPlug = plug.parent();
        if (plug.isConnected())
            outputIndices.append((int)parentPlug.logicalIndex());
    }
    // Parallel evaluation:
    // During parallel evaluation the weightList plug is requesting
    // computation. In this case we need to collect all existing indices
    // and loop through them sequentially.
    else if (plug == weightList)
    {
        // It doesn't seem possible to use
        // getExistingArrayAttributeIndices on a const plug. The plug is
        // copied to avoid this restriction.
        MPlug weightListPlug = plug;
        MIntArray existingIndices;
        weightListPlug.getExistingArrayAttributeIndices(existingIndices, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        unsigned int numIndices = existingIndices.length();

        for (i = 0; i < numIndices; i ++)
        {
            weightsPlug.selectAncestorLogicalIndex((unsigned)existingIndices[i], weightList);
            if (weightsPlug.isConnected())
                outputIndices.append(existingIndices[i]);
        }
    }
    else
        return MStatus::kUnknownParameter;

    // -----------------------------------------------------------------
    // process the output indices
    // -----------------------------------------------------------------

    for (i = 0; i < outputIndices.length(); i ++)
    {
        unsigned int listIndex = (unsigned)outputIndices[i];
        weightsPlug.selectAncestorLogicalIndex(listIndex, weightList);

        // -------------------------------------------------------------
        // get the driven deformer node
        // -------------------------------------------------------------

        MPlugArray weightsOutPlugArray;
        plug.connectedTo(weightsOutPlugArray, false, true, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MObject deformerObj;
        if (weightsOutPlugArray.length())
            deformerObj = weightsOutPlugArray[0].node();
        MFnDependencyNode deformerFn(deformerObj);

        // -------------------------------------------------------------
        // check mesh or curve and get its points
        // -------------------------------------------------------------

        MDagPath shapeDag;
        MPointArray points;
        MFloatArray uArray;
        MFloatArray vArray;
        MFloatVectorArray vertexNormals;

        int inType = 0;

        //
        // check for a mesh
        //

        // First check the mesh array input at the current index. If
        // there is a mesh present use this to get the point data.
        MPlug meshPlug(thisNode, mesh);
        MPlug indexedMeshPlug = meshPlug.elementByLogicalIndex(listIndex, &status);
        if (status == MStatus::kSuccess)
        {
            if (indexedMeshPlug.isConnected())
            {
                meshArrayDataHandle.jumpToElement(listIndex);
                MDataHandle meshDataHandle = meshArrayDataHandle.inputValue(&status);
                CHECK_MSTATUS_AND_RETURN_IT(status);
                MObject meshObj = meshDataHandle.asMesh();
                MFnMesh meshFn(meshObj, &status);
                CHECK_MSTATUS_AND_RETURN_IT(status);
                meshFn.getPoints(points, MSpace::kObject);
                meshFn.getUVs(uArray, vArray);
                meshFn.getNormals(vertexNormals);

                // Set the geometry type to mesh.
                inType = 1;
            }
        }

        //
        // check for a curve
        //

        // If there is no connected mesh and the deformed object is not
        // a mesh check for a connected curve at the current index.
        if (!inType)
        {
            MPlug curvePlug(thisNode, curve);
            MPlug indexedCurvePlug = curvePlug.elementByLogicalIndex(listIndex, &status);
            if (status == MStatus::kSuccess)
            {
                if (indexedCurvePlug.isConnected())
                {
                    curveArrayDataHandle.jumpToElement(listIndex);
                    MDataHandle curveDataHandle = curveArrayDataHandle.inputValue(&status);
                    CHECK_MSTATUS_AND_RETURN_IT(status);
                    MObject curveObj = curveDataHandle.asNurbsCurve();
                    MFnNurbsCurve curveFn(curveObj, &status);
                    CHECK_MSTATUS_AND_RETURN_IT(status);
                    curveFn.getCVs(points, MSpace::kObject);

                    inType = 2;
                }
            }
        }

        CHECK_MSTATUS_AND_RETURN_IT(status);

        if (inType == 0)
            return MStatus::kFailure;

        // -------------------------------------------------------------
        // get the matrix from the deformed mesh
        // -------------------------------------------------------------

        MMatrix inputMatrix;
        MPlug matrixListPlug(thisNode, matrixList);
        MPlug indexedMatrixPlug = matrixListPlug.elementByLogicalIndex(listIndex, &status);
        if (status == MStatus::kSuccess)
        {
            if (indexedMatrixPlug.isConnected())
            {
                matrixListArrayDataHandle.jumpToElement(listIndex);
                MDataHandle matrixDataHandle = matrixListArrayDataHandle.inputValue(&status);
                CHECK_MSTATUS_AND_RETURN_IT(status);
                inputMatrix = matrixDataHandle.asMatrix();
            }
        }

        // -------------------------------------------------------------
        // indexed invert state
        // -------------------------------------------------------------

        bool indexedInvertVal = false;

        if (invertListArrayDataHandle.jumpToElement(listIndex))
        {
            MDataHandle invertListDataHandle = invertListArrayDataHandle.inputValue(&status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            indexedInvertVal = invertListDataHandle.asBool();
        }

        // -------------------------------------------------------------
        // get the components
        // -------------------------------------------------------------

        // The input components are a copy of the components the
        // deformer affects. The data has to be copied over when the
        // ramp weights node gets connected to the deformer weights.
        // Parallel evaluation doesn't allow to draw data from a node
        // downstream but the components are mandatory. Therefore the
        // components are copied over and need to get updated manually
        // whenever the affected components on the deformer change.

        inputComponentsListArrayDataHandle.jumpToElement(listIndex);
        MDataHandle inputComponentsDataHandle = inputComponentsListArrayDataHandle.inputValue(&status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MObject componentsObj = inputComponentsDataHandle.data();

        MFnComponentListData compListFn(componentsObj, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MFnSingleIndexedComponent compFn;
        MObject vtxCompObj = compFn.create(MFn::kMeshVertComponent);

        // The components are stored in a sparse array which means that
        // each array entry contains one or more ordered components.
        // Example: vtx[61] vtx[76:78] vtx[91:95] vtx[107:112]
        for (j = 0; j < compListFn.length(); j ++)
        {
            MObject comp = compListFn[j];
            MFnSingleIndexedComponent indexedComp(comp);

            for (k = 0; k < (unsigned)indexedComp.elementCount(); k ++)
                compFn.addElement(indexedComp.element((int)k));
        }

        unsigned int elementNum = (unsigned)compFn.elementCount();

        // -------------------------------------------------------------
        // get the name of the connected shading node
        // -------------------------------------------------------------

        MString textureOutput = "";
        MPlug texturePlug(thisNode, texture);

        // Get the connected node and attribute for the texture.
        bool textureIsConnected = false;
        MPlugArray connectedTexture;
        texturePlug.connectedTo(connectedTexture, true, false);
        if (connectedTexture.length())
        {
            textureOutput = connectedTexture[0].name();
            textureIsConnected = true;
        }

        // -------------------------------------------------------------
        // process the connected shading network
        // -------------------------------------------------------------

        MFloatVectorArray colors(elementNum, textureVec);

        if (textureIsConnected)
        {
            MFloatMatrix camera;
            MFloatPointArray meshPoints;
            MFloatVectorArray normals;
            MFloatArray uCoords;
            MFloatArray vCoords;
            MFloatArray filterSizes;
            MFloatVectorArray transparencies;

            // ---------------------------------------------------------
            // collect the data for the shading network sampling
            // ---------------------------------------------------------

            for (j = 0; j < elementNum; j ++)
            {
                unsigned int index = (unsigned)compFn.element((int)j);

                meshPoints.append(MFloatPoint(points[index]));
                if (inType == 1)
                {
                    uCoords.append(uArray[index]);
                    vCoords.append(vArray[index]);
                    normals.append(vertexNormals[index]);
                }
                else
                {
                    uCoords.append(0.0);
                    vCoords.append(0.0);
                    normals.append(MFloatVector(0.0, 0.0, 0.0));
                }
                filterSizes.append(0.00001f);
            }

            // ---------------------------------------------------------
            // sample the connected 2d or 3d textures
            // ---------------------------------------------------------

            if (useUV && inType == 1)
            {
                MRenderUtil::sampleShadingNetwork(textureOutput,
                                                  (int)normals.length(),
                                                  false,
                                                  false,
                                                  camera,
                                                  &meshPoints,
                                                  &uCoords,
                                                  &vCoords,
                                                  &normals,
                                                  &meshPoints,
                                                  NULL,
                                                  NULL,
                                                  &filterSizes,
                                                  colors,
                                                  transparencies);
            }
            else
            {
                MRenderUtil::sampleShadingNetwork(textureOutput,
                                                  (int)normals.length(),
                                                  false,
                                                  false,
                                                  camera,
                                                  &meshPoints,
                                                  NULL,
                                                  NULL,
                                                  &normals,
                                                  &meshPoints,
                                                  NULL,
                                                  NULL,
                                                  &filterSizes,
                                                  colors,
                                                  transparencies);
            }
        }

        // -------------------------------------------------------------
        // create weights
        // -------------------------------------------------------------

        // Create the handles and array builder for the weights plug.
        // Using the MArrayBuilder to collect the weights and then set
        // the output weights array in a single step is much faster than
        // setting the value for each weight index individually.
        MDataHandle weightsHandle = weightsPlug.constructHandle(data);
        MArrayDataHandle weightsArrayHandle(weightsHandle);
        MArrayDataBuilder weightsBuilder = weightsArrayHandle.builder(&status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MFnNurbsCurve curveFn;

        MFloatArray outputWeights(elementNum, 0.0);

        // Compute for each influence.
        for (j = 0; j < influenceCount; j ++)
        {
            if (usedElements[j] && isActive[j])
            {
                double radius = globalRadiusVal;
                if (radiusArray[j] > 0)
                    radius = radiusArray[j];

                bool isMesh = false;
                bool isCurve = false;
                if (shapeType[j] == MFn::kMesh)
                    isMesh = true;
                else if (shapeType[j] == MFn::kNurbsCurve)
                    isCurve = true;

                // -----------------------------------------------------
                // create the intersector
                // -----------------------------------------------------

                MMatrix influenceMatrix = influenceMatrixArray[j];
                MMatrix inverseMatrix = restParentMatArray[j].inverse() * parentMatArray[j];
                bool isWorldChild = true;
                if (restParentMatArray[j] != MMatrix())
                    isWorldChild = false;

                if (isMesh)
                {
                    MObject influenceObj = shapeDagPaths[j].node();
                    status = intersector.create(influenceObj, influenceMatrix);
                    if (status != MStatus::kSuccess)
                        useShapeNode[j] = 0;
                }
                else if (isCurve)
                {
                    curveFn.setObject(shapeDagPaths[j]);
                }

                tbb::parallel_for(tbb::blocked_range<unsigned int>(0, elementNum),
                                  [&](tbb::blocked_range<unsigned int> r)
                {
                    for (unsigned int m = r.begin(); m < r.end(); m ++)
                    {
                        unsigned int index = (unsigned)compFn.element((int)m);

                        // In case of a local transform influence the
                        // influence point is transformed back to a
                        // non-hierarchical space which is important for
                        // blend shape deformers since the original mesh
                        // has a static position in space.
                        MPoint inflPos = influenceVec[j];

                        // Get the point position and take it into world
                        // space.
                        MPoint point = points[index];
                        point *= inputMatrix;

                        float value = outputWeights[m];
                        double curveParam = 0.0;

                        // ----------------
                        // shape influence
                        // ----------------
                        if (useShapeNode[j])
                        {
                            // Check if the point is within the bounding
                            // box of the influence.
                            double grow = radius * 1.1;
                            MPoint minPoint = MPoint(bboxMin[j].x - grow,
                                                     bboxMin[j].y - grow,
                                                     bboxMin[j].z - grow);
                            MPoint maxPoint = MPoint(bboxMax[j].x + grow,
                                                     bboxMax[j].y + grow,
                                                     bboxMax[j].z + grow);
                            MBoundingBox bbox(minPoint, maxPoint);
                            bool contains = bbox.contains(point);

                            if (contains && shapeType[j] != MFn::kInvalid)
                            {
                                if (isMesh)
                                {
                                    // The influence shape node
                                    // calculation must be handled
                                    // differently because when the
                                    // shape influence is part of a
                                    // hierarchy the point spaces don't
                                    // match and it's quite elaborate to
                                    // transform the shape back to it's
                                    // original position. It's easier to
                                    // transform the original mesh point
                                    // by the hierarchy matrix to match
                                    // the position of the mesh.
                                    if (!useWorldSpace[j] && isWorldChild)
                                        point *= inverseMatrix;

                                    MPointOnMesh pointOnMesh;
                                    status = intersector.getClosestPoint(point,
                                                                         pointOnMesh,
                                                                         radius);

                                    // Note:
                                    // Usually the status of
                                    // getClosestPoint would get checked
                                    // but for some reason this
                                    // interferes with the threaded
                                    // loop. Some few random components
                                    // are skipped or get wrong weight
                                    // values. But since the status is
                                    // not of primary concern it's been
                                    // neglected.

                                    // Convert the closestPoint
                                    // (MPointOnMesh) to MPoint.
                                    inflPos = pointOnMesh.getPoint();

                                    // The closest point is in
                                    // object space. To get the
                                    // actual distance it needs to
                                    // be in world space.
                                    inflPos *= influenceMatrix;
                                }
                                else if (isCurve)
                                {
                                    if (!useWorldSpace[j])
                                        point *= inverseMatrix;

                                    inflPos = curveFn.closestPoint(point,
                                                                   &curveParam,
                                                                   0.00001,
                                                                   MSpace::kWorld,
                                                                   &status);
                                }
                            }
                        }

                        MVector delta = inflPos - point;

                        double distance = delta.length();

                        if (distance <= radius)
                        {
                            // Read the value based on the curve ramp.
                            float influenceValue = (float)(distance / radius);
                            float distanceNormalized = influenceValue > 1.0f ? 1.0f : influenceValue;
                            curveAttr.getValueAtPosition(distanceNormalized, influenceValue);

                            // Read the curve value based on the
                            // curveFalloff ramp.
                            if (useShapeNode[j] && isCurve)
                            {
                                // The closestPoint function only
                                // returns param values between 0 and 1.
                                // If the curve has a greater min max
                                // range the values need to get
                                // remapped.
                                double curveStart;
                                double curveEnd;
                                curveFn.getKnotDomain(curveStart, curveEnd);
                                float curveValue;
                                curveUAttr.getValueAtPosition((float)(curveParam / curveEnd),
                                                              curveValue);
                                influenceValue *= curveValue;
                            }

                            value += influenceValue * scaleArray[j] * globalInfluenceScaleVal;
                            outputWeights.set(value, m);
                        }
                    }
                });
            }
        }

        for (j = 0; j < elementNum; j ++)
        {
            unsigned int index = (unsigned)compFn.element((int)j);

            float value = outputWeights[j];

            // ----------------
            // texture
            // ----------------

            MVector rgb = colors[j];
            float colorSum = 0.0;

            if (colorRVal)
                colorSum += (float)rgb.x;
            if (colorGVal)
                colorSum += (float)rgb.y;
            if (colorBVal)
                colorSum += (float)rgb.z;
            if (colorAVal)
                colorSum += (float)alphaVal;

            value += colorSum;

            if (value < 0.0)
                value = 0.0;
            else if (value > 1.0)
                value = 1.0;

            if (invertVal)
                value = 1 - value;
            if (indexedInvertVal)
                value = 1 - value;

            MDataHandle weightsIdHandle = weightsBuilder.addElement(index);
            weightsIdHandle.set(value * (float)globalScaleVal);
        }

        weightsArrayHandle.set(weightsBuilder);
        weightsPlug.setValue(weightsHandle);
        weightsPlug.destructHandle(weightsHandle);

        data.setClean(weightsPlug);
    }

    MDataHandle weightListData = data.outputValue(weightList, &status);
    weightListData.setClean();

    return status;
}

// ---------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2019 Ingo Clemens, brave rabbit
// weightsServer is under the terms of the MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// Author: Ingo Clemens    www.braverabbit.com
// ---------------------------------------------------------------------
