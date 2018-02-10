#include <stdio.h>
#include <stdexcept>
#include <string>
#include <sstream>

#include "common.h"

#include <maya/MGlobal.h>

std::string mStringForErrorType(MStatus status) {
    if (status == MS::kSuccess) {
        return "Success";
    } else if (status == MS::kFailure) {
        return "Generic";
    } else if (status == MS::kInsufficientMemory) {
        return "InsufficientMemory";
    } else if (status == MS::kInvalidParameter) {
        return "InvalidParameter";
    } else if (status == MS::kLicenseFailure) {
        return "LicenseFailure";
    } else if (status == MS::kUnknownParameter) {
        return "UnknownParameter";
    } else if (status == MS::kNotImplemented) {
        return "NotImplemented";
    } else if (status == MS::kNotFound) {
        return "NotFound";
    } else if (status == MS::kEndOfFile) {
        return "endOfFile";
    } else {
        std::ostringstream os;
        os << status.statusCode();
        throw std::runtime_error("Status not understood (code=" + os.str() + ")");
    }
}

void Log::print(MString message) {
    MGlobal::displayInfo(message);
}

void Log::warning(MString message) {
    MGlobal::displayWarning(message);
}

void Log::error(MString message) {
    MGlobal::displayError(message);
}

void Log::showStatus(MStatus status, std::string message) {
    std::string messageStr = message;
    
    if (status == MS::kSuccess) {
        print(MString(("Success: " + messageStr).c_str()));
        return;
    }
    
    std::string errorPart = status.errorString().asChar();
    std::string suffix = "[" + errorPart + "]";
    std::string errorString = mStringForErrorType(status) + ": " + messageStr + " " + suffix;
    error(MString(errorString.c_str()));
}

void Log::showStatus(MStatus status) {
    if (status == MS::kSuccess) {
        print(MString("Success"));
        return;
    }
    std::string errorString = mStringForErrorType(status) + status.errorString().asChar();
    error(MString(errorString.c_str()));
}

void Log::showStatusWhenError(MStatus status, std::string message) {
    if (status == MS::kSuccess) { return; }
    showStatus(status, message);
}

void Log::showStatusWhenError(MStatus status) {
    if (status == MS::kSuccess) { return; }
    showStatus(status);
}

