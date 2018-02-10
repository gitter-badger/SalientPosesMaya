#include <sstream>
#include <stdexcept>

#include <maya/MStatus.h>
#include <maya/MDataBlock.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MDataHandle.h>
#include <maya/MFnPointArrayData.h>
#include <maya/MPointArray.h>
#include <maya/MFnDoubleArrayData.h>
#include <maya/MDoubleArray.h>

#include "AnalysisNode.h"
#include "common.h"
 
MTypeId AnalysisNode::id( 0x00000001 );
MObject AnalysisNode::aInput;
MObject AnalysisNode::aOutput;

void checkObjectIsPointArray(MObject obj) {
  MFn::Type type = obj.apiType();
  if (type != MFn::kPointArrayData) {
    std::ostringstream os; os << "Element was not of type MPointArray";
    throw std::runtime_error(os.str());
  }
}
 
void* AnalysisNode::creator() { return new AnalysisNode; }

MStatus AnalysisNode::computeAnalysis(const MPlug& plug, MDataBlock& data) {
  MStatus status;
  
  // Get array handle for "input" attribute.
  MArrayDataHandle inputCurvesHandle = data.inputArrayValue(aInput);
  inputCurvesHandle.jumpToArrayElement(0);
  int n = inputCurvesHandle.elementCount();
  
  // Iterate over array elements
  for (int i = 0; i < n; i++) {
    
    // Get data for this element from the iterator.
    MDataHandle inputCurveHandle = inputCurvesHandle.inputValue();
    MObject obj = inputCurveHandle.data();
    
    // Checks
    checkObjectIsPointArray(obj);
    
    // Read array data
    MFnPointArrayData pointArrayData(obj, &status);
    std::ostringstream os; os << "Failed to read point array at index: "; os << i;
    Log::showStatusWhenError(status, os.str());
    
    // Iterate points
    MPointArray pointArray = pointArrayData.array();
    for (int j = 0; j < pointArray.length(); j++) {
        MPoint point = pointArray[j];
      // Do something ..
    }
  }
  
  // Create output data
  const double src[] = {1, 2, 3};
  MDoubleArray blah(src, 3);
  MFnDoubleArrayData out;
  MObject mout = out.create(blah);
  
  // Set output
  MDataHandle outHandle = data.outputValue(aOutput);
  outHandle.set(mout);
  outHandle.setClean();
  
  return MS::kSuccess;
}

MStatus AnalysisNode::compute(const MPlug& plug, MDataBlock& data) {
  if (plug == aOutput) {
    return computeAnalysis(plug, data);
  } else {
    return MS::kUnknownParameter;
  }
}
 
MStatus AnalysisNode::initialize() {
  MFnTypedAttribute tAttr;
 
  aOutput = tAttr.create("output", "out", MFnData::kDoubleArray);
  tAttr.setWritable(false);
  tAttr.setReadable(true);
  tAttr.setStorable(true);
  addAttribute(aOutput);
  
  aInput = tAttr.create("input", "in", MFnData::kPointArray);
  tAttr.setReadable(true);
  tAttr.setArray(true);
  tAttr.setStorable(true);
  addAttribute(aInput);
  attributeAffects(aInput, aOutput);
  
  return MS::kSuccess;
}

