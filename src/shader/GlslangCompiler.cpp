//
// Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
// Copyright (C) 2013-2016 LunarG, Inc.
// Copyright (C) 2016-2020 Google, Inc.
// Modifications Copyright(C) 2021 Advanced Micro Devices, Inc.All rights reserved.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

/*
#include "GlslangChecker.hpp"


#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <array>
#include <map>
#include <memory>
#include <thread>
#include <set>
#include <vector>

#include "glslang/Include/ShHandle.h"
#include "glslang/Public/ShaderLang.h"
#include "glslang/OSDependent/osinclude.h"
#include "WorkList.hpp"

// Build-time generated includes
#include "glslang/build_info.h"
#include "glslang/glsl_intrinsic_header.h"

using namespace glslang;

// Command-line options
enum TOptions {
    EOptionNone                 = 0,
    EOptionIntermediate         = (1 <<  0),
    EOptionSuppressInfolog      = (1 <<  1),
    EOptionMemoryLeakMode       = (1 <<  2),
    EOptionRelaxedErrors        = (1 <<  3),
    EOptionGiveWarnings         = (1 <<  4),
    EOptionLinkProgram          = (1 <<  5),
    EOptionMultiThreaded        = (1 <<  6),
    EOptionDumpConfig           = (1 <<  7),
    EOptionDumpReflection       = (1 <<  8),
    EOptionSuppressWarnings     = (1 <<  9),
    EOptionDumpVersions         = (1 << 10),
    EOptionSpv                  = (1 << 11),
    EOptionHumanReadableSpv     = (1 << 12),
    EOptionVulkanRules          = (1 << 13),
    EOptionDefaultDesktop       = (1 << 14),
    EOptionOutputPreprocessed   = (1 << 15),
    EOptionOutputHexadecimal    = (1 << 16),
    EOptionReadHlsl             = (1 << 17),
    EOptionCascadingErrors      = (1 << 18),
    EOptionAutoMapBindings      = (1 << 19),
    EOptionFlattenUniformArrays = (1 << 20),
    EOptionNoStorageFormat      = (1 << 21),
    EOptionKeepUncalled         = (1 << 22),
    EOptionHlslOffsets          = (1 << 23),
    EOptionHlslIoMapping        = (1 << 24),
    EOptionAutoMapLocations     = (1 << 25),
    EOptionDebug                = (1 << 26),
    EOptionStdin                = (1 << 27),
    EOptionOptimizeDisable      = (1 << 28),
    EOptionOptimizeSize         = (1 << 29),
    EOptionInvertY              = (1 << 30),
    EOptionDumpBareVersion      = (1 << 31),
};
bool targetHlslFunctionality1 = false;
bool SpvToolsDisassembler = false;
bool SpvToolsValidate = false;
bool NaNClamp = false;
bool stripDebugInfo = false;
bool beQuiet = false;
bool VulkanRulesRelaxed = false;
bool autoSampledTextures = false;

//
// Return codes from main/exit().
//
enum TFailCode {
    ESuccess = 0,
    EFailUsage,
    EFailCompile,
    EFailLink,
    EFailCompilerCreate,
    EFailThreadCreate,
    EFailLinkerCreate
};

//
// Forward declarations.
//
EShLanguage FindLanguage(const std::string& name, bool parseSuffix=true);
void CompileFile(const char* fileName, ShHandle);
void usage();
char* ReadFileData(const char* fileName);
void FreeFileData(char* data);
void InfoLogMsg(const char* msg, const char* name, const int num);

// Globally track if any compile or link failure.
bool CompileFailed = false;
bool LinkFailed = false;

// array of unique places to leave the shader names and infologs for the asynchronous compiles
std::vector<std::unique_ptr<glslang::TWorkItem>> WorkItems;

TBuiltInResource Resources;
std::string ConfigFile;



int ShCompile(
    const ShHandle handle,
    const char* const shaderStrings[],
    const int numStrings,
    const int* inputLengths,
    const EShOptimizationLevel optLevel,
    const TBuiltInResource* resources,
    int,
    int defaultVersion,        // use 100 for ES environment, 110 for desktop
    bool forwardCompatible,    // give errors for use of deprecated features
    EShMessages messages       // warnings/errors/AST; things to print out
    )
{
    // Map the generic handle to the C++ object
    if (handle == 0)
        return 0;

    TShHandleBase* base = reinterpret_cast<TShHandleBase*>(handle);
    TCompiler* compiler = base->getAsCompiler();
    if (compiler == 0)
        return 0;

    SetThreadPoolAllocator(compiler->getPool());

    compiler->infoSink.info.erase();
    compiler->infoSink.debug.erase();

    TIntermediate intermediate(compiler->getLanguage());
    TShader::ForbidIncluder includer;
    bool success = CompileDeferred(compiler, shaderStrings, numStrings, inputLengths, nullptr,
                                   "", optLevel, resources, defaultVersion, ENoProfile, false,
                                   forwardCompatible, messages, intermediate, includer);

    //
    // Call the machine dependent compiler
    //
    if (success && intermediate.getTreeRoot() && optLevel != EShOptNoGeneration)
        success = compiler->compile(intermediate.getTreeRoot(), intermediate.getVersion(), intermediate.getProfile());

    intermediate.removeTree();

    // Throw away all the temporary memory used by the compilation process.
    // The push was done in the CompileDeferred() call above.
    GetThreadPoolAllocator().pop();

    return success ? 1 : 0;
}

//
// Thread entry point, for non-linking asynchronous mode.
//
void CompileShaders(glslang::TWorklist& worklist)
{

    glslang::TWorkItem* workItem;
    while (worklist.remove(workItem)) {
        ShHandle compiler = ShConstructCompiler(FindLanguage(workItem->name), Options);
        if (compiler == 0)
            return;

        CompileFile(workItem->name.c_str(), compiler);

        if (! (Options & EOptionSuppressInfolog))
            workItem->results = ShGetInfoLog(compiler);

        ShDestruct(compiler);
    }
}

std::pair<bool, std::string> glslangCompileShader(const std::string& source) {
    
    ShInitialize();
    ShInitialize();  // also test reference counting of users
    ShFinalize();
    
    glslang::TWorklist workList;
    std::for_each(WorkItems.begin(), WorkItems.end(), [&workList](std::unique_ptr<glslang::TWorkItem>& item) {
        assert(item);
        workList.add(item.get());
    });

    CompileShaders(workList);
    
}*/