#ifndef common_h
#define common_h

#include <maya/MString.h>
#include <maya/MStatus.h>

class Log {
public:
    static void print(MString message);
    static void warning(MString message);
    static void error(MString message);
    
    static void showStatus(MStatus status, std::string message);
    static void showStatusWhenError(MStatus status, std::string message);
    static void showStatus(MStatus status);
    static void showStatusWhenError(MStatus status);
};

#endif
