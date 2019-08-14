// ---------------------------------------------------------------------
//
//  weightsServer.h
//
//  Created by ingo on 01/01/18.
//  Copyright (c) 2018 Ingo Clemens. All rights reserved.
//
// ---------------------------------------------------------------------

#ifndef weightsServer_h
#define weightsServer_h

#include <iostream>
#include <tbb/tbb.h>

#include <maya/MArrayDataBuilder.h>
#include <maya/MBoundingBox.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFloatArray.h>
#include <maya/MFloatMatrix.h>
#include <maya/MFloatPointArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFnComponentListData.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MFnSkinCluster.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MMeshIntersector.h>
#include <maya/MPxNode.h>
#include <maya/MRampAttribute.h>
#include <maya/MRenderUtil.h>
#include <maya/MSelectionList.h>
#include <maya/MTypeId.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MMatrix.h>
#include <maya/MMatrixArray.h>
#include <maya/MPlugArray.h>
#include <maya/MPointArray.h>

class weightsServer : public MPxNode
{
public:
	weightsServer();
	~weightsServer();

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

	static MObject active;
	static MObject alpha;
	static MObject colorR;
	static MObject colorG;
	static MObject colorB;
	static MObject colorA;
	static MObject curve;
	static MObject curveRamp;
	static MObject curveRampUVal;
	static MObject flood; // unused
	static MObject globalInfluenceScale;
	static MObject globalRadius;
	static MObject globalScale;
	static MObject influence;
	static MObject inputComponentsList;
	static MObject inputComponents;
	static MObject inputTransfer;
	static MObject invert;
	static MObject invertList;
	static MObject matrix;
	static MObject matrixList;
	static MObject mesh;
	static MObject outputTransfer;
	static MObject radius;
	static MObject restParentMatrix;
	static MObject scale;
	static MObject texture;
	static MObject transferWeights;
	static MObject useShape;
	static MObject useTransfer;
	static MObject useUV;
	static MObject weights;
	static MObject weightList;
	static MObject worldSpace;

	static MTypeId id;
};

#endif

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
