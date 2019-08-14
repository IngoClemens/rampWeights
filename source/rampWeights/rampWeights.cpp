// ---------------------------------------------------------------------
//
//  rampWeights.cpp
//
//  Created by ingo on 4/20/16.
//  Copyright (c) 2016 Ingo Clemens. All rights reserved.
//
// ---------------------------------------------------------------------

#include <string>

static const std::string kVERSION = "4.0.0";

#include <iostream>
#include <cmath>

#include <maya/MArrayDataBuilder.h>
#include <maya/MDagPath.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFloatPointArray.h>
#include <maya/MFnComponentListData.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MFnPlugin.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MPointArray.h>
#include <maya/MPxNode.h>
#include <maya/MRampAttribute.h>
#include <maya/MSelectionList.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>
#include <maya/MVector.h>


// ---------------------------------------------------------------------
// header
// ---------------------------------------------------------------------

class rampWeights : public MPxNode
{
public:
    rampWeights();
    ~rampWeights();

    MStatus compute(const MPlug& plug, MDataBlock& data);

    static void* creator();
    static MStatus initialize();

    void postConstructor();
    MStatus postConstructor_init_curveRamp(MObject& nodeObj,
                                           MObject& rampObj,
                                           int index,
                                           float position,
                                           float value,
                                           int interpolation);

    static MObject axis;
    static MObject centered;
    static MObject clamp;
    static MObject curve;
    static MObject curveRamp;
    static MObject end;
    static MObject inputComponentsList;
    static MObject inputComponents;
    static MObject invert;
    static MObject invertList;
    static MObject matrixList;
    static MObject mesh;
    static MObject mirror;
    static MObject multiply;
    static MObject offset;
    static MObject placementMatrixList;
    static MObject start;
    static MObject useTransform;
    static MObject weightList;
    static MObject weights;

    static MTypeId id;
};


// ---------------------------------------------------------------------
// main
// ---------------------------------------------------------------------

MTypeId rampWeights::id(0x0011C1C7);

MObject rampWeights::axis;
MObject rampWeights::centered;
MObject rampWeights::clamp;
MObject rampWeights::curve;
MObject rampWeights::curveRamp;
MObject rampWeights::end;
MObject rampWeights::inputComponentsList;
MObject rampWeights::inputComponents;
MObject rampWeights::invert;
MObject rampWeights::invertList;
MObject rampWeights::matrixList;
MObject rampWeights::mesh;
MObject rampWeights::mirror;
MObject rampWeights::multiply;
MObject rampWeights::offset;
MObject rampWeights::placementMatrixList;
MObject rampWeights::start;
MObject rampWeights::useTransform;
MObject rampWeights::weightList;
MObject rampWeights::weights;


// ---------------------------------------------------------------------
// creator
// ---------------------------------------------------------------------

rampWeights::rampWeights()
{}

rampWeights::~rampWeights()
{}

void* rampWeights::creator()
{
    return new rampWeights();
}


// ---------------------------------------------------------------------
// initialize the attributes
// ---------------------------------------------------------------------

MStatus rampWeights::initialize()
{
    //
    // MFnEnumAttribute
    //

    MFnEnumAttribute eAttr;

    axis = eAttr.create("axis", "ax", 0);
    eAttr.addField("X", 0);
    eAttr.addField("Y", 1);
    eAttr.addField("Z", 2);
    eAttr.setKeyable(true);

    //
    // MFnNumericAttribute
    //

    MFnNumericAttribute nAttr;

    centered = nAttr.create("centered", "ct", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setKeyable(true);

    clamp = nAttr.create("clamp", "cl", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setKeyable(true);

    end = nAttr.create("rangeEnd", "re", MFnNumericData::kDouble);
    nAttr.setDefault(1.0);
    nAttr.setKeyable(true);
    nAttr.setSoftMin(-10.0);
    nAttr.setSoftMax(10.0);

    invert = nAttr.create("invert", "iv", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setKeyable(true);

    invertList = nAttr.create("invertList", "ivl", MFnNumericData::kBoolean);
    nAttr.setArray(true);
    nAttr.setUsesArrayDataBuilder(true);

    mirror = nAttr.create("mirror", "mi", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setKeyable(true);

    multiply = nAttr.create("multiply", "mult", MFnNumericData::kDouble);
    nAttr.setDefault(1.0);
    nAttr.setKeyable(true);
    nAttr.setSoftMin(0.0);
    nAttr.setSoftMax(1.0);

    offset = nAttr.create("offset", "of", MFnNumericData::kDouble);
    nAttr.setDefault(0.0);
    nAttr.setKeyable(true);
    nAttr.setSoftMin(-10.0);
    nAttr.setSoftMax(10.0);

    start = nAttr.create("rangeStart", "rs", MFnNumericData::kDouble);
    nAttr.setDefault(0.0);
    nAttr.setKeyable(true);
    nAttr.setSoftMin(-5.0);
    nAttr.setSoftMax(5.0);

    useTransform = nAttr.create("useTransform", "ut", MFnNumericData::kBoolean);
    nAttr.setDefault(false);
    nAttr.setKeyable(true);

    weights = nAttr.create("weights", "w", MFnNumericData::kFloat, 0.0);
    nAttr.setHidden(true);
    nAttr.setArray(true);
    nAttr.setUsesArrayDataBuilder(true);

    //
    // MFnMatrixAttribute
    //

    MFnMatrixAttribute mAttr;

    matrixList = mAttr.create("matrixList", "ml");
    mAttr.setHidden(true);
    mAttr.setArray(true);

    placementMatrixList = mAttr.create("placementMatrixList", "pml");
    mAttr.setHidden(true);
    mAttr.setArray(true);

    //
    // MRampAttribute
    //

    MRampAttribute rAttr;

    curveRamp = rAttr.createCurveRamp("blendCurve", "bc");

    //
    // MFnTypedAttribute
    //

    MFnTypedAttribute tAttr;

    inputComponents = tAttr.create("inputComponents", "ic", MFnComponentListData::kComponentList);

    curve = tAttr.create("curve", "crv", MFnData::kNurbsCurve);
    tAttr.setHidden(true);
    tAttr.setArray(true);
    tAttr.setUsesArrayDataBuilder(true);

    mesh = tAttr.create("mesh", "m", MFnData::kMesh);
    tAttr.setHidden(true);
    tAttr.setArray(true);
    tAttr.setUsesArrayDataBuilder(true);

    //
    // MFnCompoundAttribute
    //

    MFnCompoundAttribute cAttr;

    inputComponentsList = cAttr.create("inputComponentsList", "icl");
    cAttr.setHidden(true);
    cAttr.setArray(true);
    cAttr.setUsesArrayDataBuilder(true);
    cAttr.addChild(inputComponents);

    weightList = cAttr.create("weightList", "wl");
    cAttr.setHidden(true);
    cAttr.setArray(true);
    cAttr.setUsesArrayDataBuilder(true);
    cAttr.addChild(weights);

    // -----------------------------------------------------------------
    // add attributes (order matters)
    // -----------------------------------------------------------------

    addAttribute(axis);
    addAttribute(mirror);
    addAttribute(start);
    addAttribute(end);
    addAttribute(offset);
    addAttribute(clamp);
    addAttribute(centered);
    addAttribute(invert);
    addAttribute(useTransform);
    addAttribute(multiply);
    addAttribute(curveRamp);
    addAttribute(mesh);
    addAttribute(curve);
    addAttribute(inputComponentsList);
    addAttribute(inputComponents);
    addAttribute(weightList);
    addAttribute(weights);
    addAttribute(matrixList);
    addAttribute(placementMatrixList);
    addAttribute(invertList);

    // -----------------------------------------------------------------
    // affects
    // -----------------------------------------------------------------

    attributeAffects(axis, weightList);
    attributeAffects(centered, weightList);
    attributeAffects(clamp, weightList);
    attributeAffects(curve, weightList);
    attributeAffects(curveRamp, weightList);
    attributeAffects(end, weightList);
    attributeAffects(invert, weightList);
    attributeAffects(invertList, weightList);
    attributeAffects(matrixList, weightList);
    attributeAffects(mesh, weightList);
    attributeAffects(mirror, weightList);
    attributeAffects(multiply, weightList);
    attributeAffects(offset, weightList);
    attributeAffects(placementMatrixList, weightList);
    attributeAffects(start, weightList);
    attributeAffects(useTransform, weightList);

    return MS::kSuccess;
}


// ---------------------------------------------------------------------
// initialize the ramp attribute
// ---------------------------------------------------------------------

void rampWeights::postConstructor()
{
    MStatus status;
    MObject thisNode = this->thisMObject();
    // One entry is the least needed or the attribute editor will
    // produce an error.
    postConstructor_init_curveRamp(thisNode, curveRamp, 0, 0.0f, 0.0f, 2);
    postConstructor_init_curveRamp(thisNode, curveRamp, 1, 1.0f, 1.0f, 2);
}

MStatus rampWeights::postConstructor_init_curveRamp(MObject& nodeObj,
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

    return status;
}


// ---------------------------------------------------------------------
// compute
// ---------------------------------------------------------------------

MStatus rampWeights::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status = MS::kSuccess;

    unsigned int i, j, k;

    MObject thisNode = this->thisMObject();

    // -----------------------------------------------------------------
    // attributes
    // -----------------------------------------------------------------

    MDataHandle axisData = data.inputValue(axis, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    int axisVal = axisData.asShort();

    MDataHandle centeredData = data.inputValue(centered, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool centeredVal = centeredData.asBool();

    MDataHandle clampData = data.inputValue(clamp, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool clampVal = clampData.asBool();

    MArrayDataHandle curveArrayDataHandle = data.inputArrayValue(curve, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MRampAttribute curveAttr(thisNode, curveRamp, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle endData = data.inputValue(end, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double endVal = endData.asDouble();

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

    MDataHandle mirrorData = data.inputValue(mirror, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool mirrorVal = mirrorData.asBool();

    MDataHandle multiplyData = data.inputValue(multiply, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double multiplyVal = multiplyData.asDouble();

    MDataHandle offsetData = data.inputValue(offset, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double offsetVal = offsetData.asDouble();

    MArrayDataHandle placementMatrixListArrayDataHandle = data.inputArrayValue(placementMatrixList, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle startData = data.inputValue(start, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double startVal = startData.asDouble();

    MDataHandle useTransformData = data.inputValue(useTransform, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool useTransformVal = useTransformData.asBool();

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
        weightsPlug.connectedTo(weightsOutPlugArray, false, true, &status);
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
                meshFn.getPoints(points, MSpace::kWorld);

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
        // get the matrices
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
                inputMatrix = matrixDataHandle.asMatrix().inverse();
            }
        }

        // Get the placement matrix for the current index in case it's
        // connected. If there is no connection then the matrix will
        // simply remain empty which doesn't affect the matrix calculations.
        MMatrix placementMatrix;
        MPlug placementMatrixListPlug(thisNode, placementMatrixList);
        indexedMatrixPlug = placementMatrixListPlug.elementByLogicalIndex(listIndex, &status);
        if (status == MStatus::kSuccess)
        {
            if (indexedMatrixPlug.isConnected())
            {
                placementMatrixListArrayDataHandle.jumpToElement(listIndex);
                MDataHandle matrixDataHandle = placementMatrixListArrayDataHandle.inputValue(&status);
                CHECK_MSTATUS_AND_RETURN_IT(status);
                placementMatrix = matrixDataHandle.asMatrix().inverse();
            }
        }

        // Multiply with the inverse world matrix if the transformation
        // should not be considered.
        if (!useTransformVal)
            placementMatrix *= inputMatrix;

        // -------------------------------------------------------------
        // indexed invert
        // -------------------------------------------------------------

        bool indexedInvertVal = false;

        if (invertListArrayDataHandle.jumpToElement(listIndex))
        {
            MDataHandle invertListDataHandle = invertListArrayDataHandle.inputValue(&status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            indexedInvertVal = invertListDataHandle.asBool();
        }

        // -------------------------------------------------------------
        // defining settings
        // -------------------------------------------------------------

        if (centeredVal && startVal != endVal)
        {
            double min = startVal;
            double max = endVal;

            min = startVal - ((endVal - startVal) / 2.0);
            max = endVal - ((endVal - startVal) / 2.0);

            startVal = min;
            endVal = max;
        }

        startVal += offsetVal;
        endVal += offsetVal;

        if (mirrorVal && clampVal && startVal < 0.0)
            startVal = 0.0;

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

        for (j = 0; j < elementNum; j ++)
        {
            unsigned int index = (unsigned)compFn.element((int)j);

            MPoint point = points[index];
            MPoint originalPoint = point * placementMatrix;

            float value = 0.0;

            double pos = originalPoint.x;
            if (axisVal == 1)
                pos = originalPoint.y;
            else if (axisVal == 2)
                pos = originalPoint.z;

            if (mirrorVal)
                pos = std::abs(pos);

            if (pos < startVal)
                ;
            else
            {
                if (pos > endVal)
                    curveAttr.getValueAtPosition(1.0, value);
                else
                {
                    float curvePos = (float)((pos - startVal) / (endVal - startVal));
                    curveAttr.getValueAtPosition(curvePos, value);
                }
            }
            if (value < 0.0)
                value = 0.0;
            else if (value > 1.0)
                value = 1.0;

            if (invertVal)
                value = 1 - value;
            if (indexedInvertVal)
                value = 1 - value;

            MDataHandle weightsIdHandle = weightsBuilder.addElement(index);
            weightsIdHandle.set(value * (float)multiplyVal);
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
// initialization
// ---------------------------------------------------------------------

MStatus initializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin plugin(obj, "Ingo Clemens", kVERSION.c_str(), "Any");

    status = plugin.registerNode("rampWeights", rampWeights::id, rampWeights::creator,
                                 rampWeights::initialize);

    if (status != MStatus::kSuccess)
        status.perror("Register rampWeights node failed.");

    return status;
}


MStatus uninitializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin plugin(obj, "Ingo Clemens", kVERSION.c_str(), "Any");

    status = plugin.deregisterNode(rampWeights::id);

    if (status != MStatus::kSuccess)
        status.perror("Deregister rampWeights node failed.");

    return status;
}

// ---------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2019 Ingo Clemens, brave rabbit
// rampWeights is under the terms of the MIT License
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
