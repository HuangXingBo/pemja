// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
#include <stdlib.h>
#include <dlfcn.h>
#include <CommonUtils.h>

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved)
{
    return JNI_VERSION_1_8;
}

/*
 * Class:     utils_CommonUtils
 * Method:    loadLibrary0
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_pemja_utils_CommonUtils_loadLibrary0
  (JNIEnv *env, jobject obj, jstring library)
{
    void* dlresult = dlopen((*env)->GetStringUTFChars(env, library, 0), RTLD_NOW | RTLD_GLOBAL);
    if (dlresult) {
        // The dynamic linker maintains reference counts so closing it is a no-op.
        dlclose(dlresult);
    } else {
        /*
         * Ignore errors and hope that the library is loaded globally or the
         * extensions are linked. If developers need to debug the cause they
         * should print the result of dlerror.
         */
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
}
