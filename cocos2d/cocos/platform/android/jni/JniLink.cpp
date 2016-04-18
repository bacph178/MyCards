/*
 * JniLink.cpp
 */


#include "JniLink.h"
#include "JniHelper.h"

using namespace cocos2d;

extern "C"
{

    void openURLX(const char* url)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t,
                                           "org/cocos2dx/lib/Cocos2dxActivity",    // fully qualified class name
                                           "openURLX",                              // method name
                                           "(Ljava/lang/String;)V")) {             // data type of argument
            
            // jstring - C++ representation of Java String
            jstring stringArg = t.env->NewStringUTF(url);
            
            // call the method, with arguments
            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
        }
    }
}
