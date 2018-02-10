#include "AnalysisNode.h"

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MIOStream.h>


MStatus initializePlugin(MObject obj) {
    MStatus status;
    
    MFnPlugin plugin(obj, "Richard Roberts", "0.0.1", "201600");
    status = plugin.registerNode("AnalysisNode", AnalysisNode::id, AnalysisNode::creator, AnalysisNode::initialize);
    return status;
}

MStatus uninitializePlugin(MObject obj) {
    MStatus status;
    
    MFnPlugin plugin(obj);
    status = plugin.deregisterNode(AnalysisNode::id);
    return status;
}

