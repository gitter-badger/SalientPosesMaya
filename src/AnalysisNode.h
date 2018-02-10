#ifndef ANALYSISNODE_H
#define ANALYSISNODE_H
 
#include <maya/MPxNode.h>

class AnalysisNode : public MPxNode {
 public:
  AnalysisNode() {}
    
  MStatus computeAnalysis(const MPlug& plug, MDataBlock& data);
  virtual MStatus compute(const MPlug& plug, MDataBlock& data);
    
  static void* creator();
  static MStatus initialize();
 
  static MTypeId id;
  static MObject aInput;
  static MObject aOutput;
};
#endif
