/****************************************************************************
 Copyright (c) 2013-2014 Auticiel SAS
 
 http://www.fennex.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************///

#include "NativeUtility.h"

std::string NativeUtility::objectiveC_call() {
    NSString *deviceId = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
    return std::string([deviceId UTF8String]);
}

std::string NativeUtility::deviceID() {
    NSString *deviceId = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
    return std::string([deviceId UTF8String]);
}

std::string NativeUtility::deviceName() {
    NSString *deviceName = [[UIDevice currentDevice] model];
    return std::string([deviceName UTF8String]);
}

std::string NativeUtility::osVersion(){
    NSString *osVersion = [[UIDevice currentDevice] systemVersion];
    return std::string([osVersion UTF8String]);
}

std::string NativeUtility::appVersion(){
   NSString *version = [[[NSBundle mainBundle] infoDictionary]
                        objectForKey:@"CFBundleShortVersionString"];
    return std::string([version UTF8String]);
}
