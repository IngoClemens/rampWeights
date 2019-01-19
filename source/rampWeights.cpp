// ---------------------------------------------------------------------
//
//  rampWeights.cpp
//
//  Created by ingo on 4/20/16.
//  Copyright (c) 2016 Ingo Clemens. All rights reserved.
//
// ---------------------------------------------------------------------

#include <string>

static const std::string kVERSION = "3.0.0";

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
#include <maya/MItDependencyGraph.h>
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

    MStatus getComponents(MPlug componentsPlug,
                          MFnSingleIndexedComponent &compFn);

    static MObject axis;
    static MObject centered;
    static MObject clamp;
    static MObject curve;
    static MObject curveRamp;
    static MObject end;
    static MObject invert;
    static MObject invertList;
    static MObject matrixList;
    static MObject mesh;
    static MObject mirror;
    static MObject multiply;
    static MObject offset;
    static MObject start;
    static MObject useTransform;
    static MObject weightList;
    static MObject weights;
    static MObject worldMatrix;

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
MObject rampWeights::invert;
MObject rampWeights::invertList;
MObject rampWeights::matrixList;
MObject rampWeights::mesh;
MObject rampWeights::mirror;
MObject rampWeights::multiply;
MObject rampWeights::offset;
MObject rampWeights::start;
MObject rampWeights::useTransform;
MObject rampWeights::weightList;
MObject rampWeights::weights;
MObject rampWeights::worldMatrix;


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

    worldMatrix = mAttr.create("worldMatrix", "wm");
    mAttr.setHidden(true);

    //
    // MRampAttribute
    //

    MRampAttribute rAttr;

    curveRamp = rAttr.createCurveRamp("blendCurve", "bc");

    //
    // MFnTypedAttribute
    //

    MFnTypedAttribute tAttr;

    mesh = tAttr.create("mesh", "m", MFnData::kMesh);
    tAttr.setHidden(true);

    curve = tAttr.create("curve", "crv", MFnData::kNurbsCurve);
    tAttr.setHidden(true);

    //
    // MFnCompoundAttribute
    //

    MFnCompoundAttribute cAttr;

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
    addAttribute(weightList);
    addAttribute(weights);
    addAttribute(worldMatrix);
    addAttribute(matrixList);
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
    attributeAffects(start, weightList);
    attributeAffects(useTransform, weightList);
    attributeAffects(worldMatrix, weightList);

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

    unsigned int i;

    MObject thisNode = this->thisMObject();

    if (plug != weights)
        return MStatus::kUnknownParameter;

    if (!plug.isConnected())
        return status;

    // In order to be able to handle multiple blend shape channels or
    // deformers it's necessary to generate separate weight lists,
    // therefore the weightList output attribute exists as an array.
    // For creating the weights for each list the index of the current
    // weights plug needs to be known. This index can be derived from
    // the indexed weightList plug which is the parent of the current
    // weights plug.
    // It's not possible to get the index from a newly referenced
    // weights plug (see (*)), therefore the current plug passed
    // as the compute's method argument is used.
    MPlug parentPlug = plug.parent();
    unsigned int parentIndex = parentPlug.logicalIndex();

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

    MDataHandle curveData = data.inputValue(curve, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MObject curveObj = curveData.asNurbsCurve();

    MRampAttribute curveAttr(thisNode, curveRamp, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle endData = data.inputValue(end, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double endVal = endData.asDouble();

    MDataHandle invertData = data.inputValue(invert, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool invertVal = invertData.asBool();

    MArrayDataHandle invertListArrayDataHandle = data.inputArrayValue(invertList, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MArrayDataHandle matrixListArrayDataHandle = data.inputArrayValue(matrixList, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    MDataHandle meshData = data.inputValue(mesh, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MObject meshObj = meshData.asMesh();

    MDataHandle mirrorData = data.inputValue(mirror, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool mirrorVal = mirrorData.asBool();

    MDataHandle multiplyData = data.inputValue(multiply, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double multiplyVal = multiplyData.asDouble();

    MDataHandle offsetData = data.inputValue(offset, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double offsetVal = offsetData.asDouble();

    MDataHandle startData = data.inputValue(start, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    double startVal = startData.asDouble();

    MDataHandle useTransformData = data.inputValue(useTransform, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    bool useTransformVal = useTransformData.asBool();

    MDataHandle worldMatrixData = data.inputValue(worldMatrix, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MMatrix worldMatrixVal = worldMatrixData.asMatrix();

    // -----------------------------------------------------------------
    // get the driven deformer node
    // -----------------------------------------------------------------

    MPlugArray weightsOutPlugArray;
    plug.connectedTo(weightsOutPlugArray, false, true, &status);
    CHECK_MSTATUS_AND_RETURN_IT(status);
    MObject deformerObj = weightsOutPlugArray[0].node();
    MFnDependencyNode deformerFn(deformerObj);

    // -----------------------------------------------------------------
    // check mesh or curve and get its points
    // -----------------------------------------------------------------

    MDagPath shapeDag;
    MPointArray points;

    int inType = 0;

    //
    // check for a mesh
    //
    MItDependencyGraph dependIter(deformerObj,
                                  MFn::kMesh,
                                  MItDependencyGraph::kUpstream,
                                  MItDependencyGraph::kDepthFirst,
                                  MItDependencyGraph::kNodeLevel,
                                  &status);

    for (; !dependIter.isDone(); dependIter.next())
    {
        MObject currentObj = dependIter.currentItem();
        MFnDagNode currentFn(currentObj, &status);
        if (status && !inType && currentFn.isIntermediateObject())
        {
            MDagPath::getAPathTo(currentObj, shapeDag);
            MFnMesh meshFn(shapeDag);
            meshFn.getPoints(points, MSpace::kWorld);

            inType = 1;
        }
    }

    //
    // check for a curve
    //
    if (!inType)
    {
        dependIter.resetTo(deformerObj,
                           MFn::kNurbsCurve,
                           MItDependencyGraph::kUpstream,
                           MItDependencyGraph::kDepthFirst,
                           MItDependencyGraph::kNodeLevel);

        for (; !dependIter.isDone(); dependIter.next())
        {
            MObject currentObj = dependIter.currentItem();
            MFnDagNode currentFn(currentObj, &status);
            if (status && !inType && currentFn.isIntermediateObject())
            {
                MDagPath::getAPathTo(currentObj, shapeDag);
                MFnNurbsCurve curveFn(shapeDag);
                curveFn.getCVs(points, MSpace::kObject);

                inType = 2;
            }
        }
    }

    CHECK_MSTATUS_AND_RETURN_IT(status);

    if (inType == 0)
        return MStatus::kFailure;

    // -----------------------------------------------------------------
    // get the matrices
    // -----------------------------------------------------------------

    // Get the matrix of the deformed geometry.
    // If the transform is already connected get the matrix directly.
    // The advantage of this connection is that the node gets computed
    // when the matrix attribute changes.
    MMatrix inputMatrix;
    MPlug worldMatrixPlug(thisNode, worldMatrix);
    if (worldMatrixPlug.isConnected())
    {
        inputMatrix = worldMatrixVal.inverse();
    }
    // If the world matrix plug is not connected get the transform node
    // of the deformed mesh and the matrix from it. The result is the
    // same as with the connection but it doesn't update when the node
    // is moved.
    else
    {
        MFnDagNode shapeDagFn(shapeDag);
        MObject transformObj = shapeDagFn.parent(0);
        MFnDagNode transformDagFn(transformObj);
        inputMatrix = transformDagFn.transformationMatrix().inverse();
    }

    // Get the placement matrix for the current index in case it's
    // connected. If there is no connection then the matrix will simply
    // remain empty which doesn't affect the matrix calculations.
    MMatrix placementMatrix;
    MPlug matrixListPlug(thisNode, matrixList);
    MPlug indexedMatrixPlug = matrixListPlug.elementByLogicalIndex(parentIndex, &status);
    if (status == MStatus::kSuccess)
    {
        if (indexedMatrixPlug.isConnected())
        {
            matrixListArrayDataHandle.jumpToElement(parentIndex);
            MDataHandle matrixDataHandle = matrixListArrayDataHandle.inputValue(&status);
            CHECK_MSTATUS_AND_RETURN_IT(status);
            placementMatrix = matrixDataHandle.asMatrix().inverse();
        }
    }

    // Multiply with the inverse world matrix if the transformation
    // should not be considered.
    if (!useTransformVal)
        placementMatrix *= inputMatrix;

    // -----------------------------------------------------------------
    // indexed invert
    // -----------------------------------------------------------------

    bool indexedInvertVal = false;

    if (invertListArrayDataHandle.jumpToElement(parentIndex))
    {
        MDataHandle invertListDataHandle = invertListArrayDataHandle.inputValue(&status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        indexedInvertVal = invertListDataHandle.asBool();
    }

    // -----------------------------------------------------------------
    // defining settings
    // -----------------------------------------------------------------

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

    // -----------------------------------------------------------------
    // get the components
    // -----------------------------------------------------------------

    // Create a list of the components which are affected.
    MFnSingleIndexedComponent compFn;
    MObject vtxCompObj = compFn.create(MFn::kMeshVertComponent);

    MPlug inputPlug;
    MPlug componentsPlug;

    // In case of a blend shape deformer the components can be derived
    // from the target item to which the output weights plug is
    // connected to.
    if (deformerObj.hasFn(MFn::kBlendShape))
    {
        MPlug groupPlug = weightsOutPlugArray[0].parent();
        MPlug itemPlug = groupPlug.child(0).elementByLogicalIndex(6000);
        MPlug plug;
#if MAYA_API_VERSION >= 201600
        componentsPlug = itemPlug.child(4, &status);
#else
        componentsPlug = itemPlug.child(2, &status);
#endif
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }
    // In case of any other deformer the component indices are stored on
    // the deformer group node.
    else
    {
        inputPlug = deformerFn.findPlug("input", true, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        // The input plug can have multiple elements because all regular
        // deformers can affect multiple objects. The weights are
        // applied globally to the entire deformation and are not
        // element specific, therefore only the first connected object
        // is respected.
        MPlug geoItem = inputPlug[0].child(0, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
        MPlugArray connectedPlugs;
        geoItem.connectedTo(connectedPlugs, true, false, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);

        MFnDependencyNode groupNodeFn(connectedPlugs[0].node());
        componentsPlug = groupNodeFn.findPlug("inputComponents", true, &status);
        CHECK_MSTATUS_AND_RETURN_IT(status);
    }

    getComponents(componentsPlug, compFn);

    // -----------------------------------------------------------------
    // create weights
    // -----------------------------------------------------------------

    unsigned int elementNum = (unsigned)compFn.elementCount();

    // (*) Get the weights array plug. Even though this is already
    // referenced through 'plug' it's necessary to do this separately
    // just to be able to set the ancestor logical index.
    MPlug weightsPlug(thisNode, weights);
    weightsPlug.selectAncestorLogicalIndex(parentIndex, weightList);

    // Create the handles and array builder for the weights plug.
    // Using the MArrayBuilder to collect the weights and then set the
    // output weights array in a single step is much faster than setting
    // the value for each weight index individually.
    MDataHandle weightsHandle = weightsPlug.constructHandle(data);
    MArrayDataHandle weightsArrayHandle(weightsHandle);
    MArrayDataBuilder weightsBuilder = weightsArrayHandle.builder(&status);
    CHECK_MSTATUS_AND_RETURN_IT(status);

    for (i = 0; i < elementNum; i ++)
    {
        unsigned int index = (unsigned)compFn.element((int)i);

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

    return status;
}


MStatus rampWeights::getComponents(MPlug componentsPlug,
                                   MFnSingleIndexedComponent &compFn)
{
    MStatus status = MStatus::kSuccess;

    unsigned int i, j;

    MFnComponentListData compListFn(componentsPlug.asMObject());

    // Get the components and store them in the vtxList.
    // The components are stored in a sparse array which means that each
    // array entry contains one or more ordered components.
    // Example: vtx[61] vtx[76:78] vtx[91:95] vtx[107:112]
    for (i = 0; i < compListFn.length(); i ++)
    {
        MObject comp = compListFn[i];
        MFnSingleIndexedComponent indexedComp(comp);

        for (j = 0; j < (unsigned)indexedComp.elementCount(); j ++)
            compFn.addElement(indexedComp.element((int)j));
    }

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


MStatus uninitializePlugin( MObject obj)
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
