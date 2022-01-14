#pragma once


#include "../OpenGLError.hpp"
#include <utility>
#include <string>

#include <cstring>

//#include "glslang/build_info.h"
//#include "glslang/glsl_intrinsic_header.h"

/*
#include "glslang/Include/ShHandle.h"
#include "glslang/Public/ShaderLang.h"
#include "glslang/OSDependent/osinclude.h"
*/
//#include "glslang/MachineIndependent/localintermediate.h"
/*
#include "glslang/Public/ShaderLang.h"
#include "glslang/MachineIndependent/Scan.h"
#include "glslang/MachineIndependent/Scan.h"
*/
//#include "WorkList.hpp"

//#include "ResourceLimits.h"
//#include "DirStackFileIncluder.h"

//#include "glslang/Public/ShaderLang.h"
//#include "../SPIRV/GlslangToSpv.h"
//#include "../SPIRV/GLSL.std.450.h"
//#include "../SPIRV/doc.h"
//#include "../SPIRV/disassemble.h"

#include "glslang/Include/ShHandle.h"

#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <array>
#include <map>
#include <memory>
#include <thread>
#include <set>

//#include "glslang/OSDependent/osinclude.h"

// Build-time generated includes
//#include "glslang/build_info.h"

//#include "glslang/glsl_intrinsic_header.h"


//using namespace glslang;

namespace Levek {


class GlslangCompiler {

private:

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

//defaults resources taken from standalone
const TBuiltInResource Resources = {
    /* .MaxLights = */ 32,
    /* .MaxClipPlanes = */ 6,
    /* .MaxTextureUnits = */ 32,
    /* .MaxTextureCoords = */ 32,
    /* .MaxVertexAttribs = */ 64,
    /* .MaxVertexUniformComponents = */ 4096,
    /* .MaxVaryingFloats = */ 64,
    /* .MaxVertexTextureImageUnits = */ 32,
    /* .MaxCombinedTextureImageUnits = */ 80,
    /* .MaxTextureImageUnits = */ 32,
    /* .MaxFragmentUniformComponents = */ 4096,
    /* .MaxDrawBuffers = */ 32,
    /* .MaxVertexUniformVectors = */ 128,
    /* .MaxVaryingVectors = */ 8,
    /* .MaxFragmentUniformVectors = */ 16,
    /* .MaxVertexOutputVectors = */ 16,
    /* .MaxFragmentInputVectors = */ 15,
    /* .MinProgramTexelOffset = */ -8,
    /* .MaxProgramTexelOffset = */ 7,
    /* .MaxClipDistances = */ 8,
    /* .MaxComputeWorkGroupCountX = */ 65535,
    /* .MaxComputeWorkGroupCountY = */ 65535,
    /* .MaxComputeWorkGroupCountZ = */ 65535,
    /* .MaxComputeWorkGroupSizeX = */ 1024,
    /* .MaxComputeWorkGroupSizeY = */ 1024,
    /* .MaxComputeWorkGroupSizeZ = */ 64,
    /* .MaxComputeUniformComponents = */ 1024,
    /* .MaxComputeTextureImageUnits = */ 16,
    /* .MaxComputeImageUniforms = */ 8,
    /* .MaxComputeAtomicCounters = */ 8,
    /* .MaxComputeAtomicCounterBuffers = */ 1,
    /* .MaxVaryingComponents = */ 60,
    /* .MaxVertexOutputComponents = */ 64,
    /* .MaxGeometryInputComponents = */ 64,
    /* .MaxGeometryOutputComponents = */ 128,
    /* .MaxFragmentInputComponents = */ 128,
    /* .MaxImageUnits = */ 8,
    /* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
    /* .MaxCombinedShaderOutputResources = */ 8,
    /* .MaxImageSamples = */ 0,
    /* .MaxVertexImageUniforms = */ 0,
    /* .MaxTessControlImageUniforms = */ 0,
    /* .MaxTessEvaluationImageUniforms = */ 0,
    /* .MaxGeometryImageUniforms = */ 0,
    /* .MaxFragmentImageUniforms = */ 8,
    /* .MaxCombinedImageUniforms = */ 8,
    /* .MaxGeometryTextureImageUnits = */ 16,
    /* .MaxGeometryOutputVertices = */ 256,
    /* .MaxGeometryTotalOutputComponents = */ 1024,
    /* .MaxGeometryUniformComponents = */ 1024,
    /* .MaxGeometryVaryingComponents = */ 64,
    /* .MaxTessControlInputComponents = */ 128,
    /* .MaxTessControlOutputComponents = */ 128,
    /* .MaxTessControlTextureImageUnits = */ 16,
    /* .MaxTessControlUniformComponents = */ 1024,
    /* .MaxTessControlTotalOutputComponents = */ 4096,
    /* .MaxTessEvaluationInputComponents = */ 128,
    /* .MaxTessEvaluationOutputComponents = */ 128,
    /* .MaxTessEvaluationTextureImageUnits = */ 16,
    /* .MaxTessEvaluationUniformComponents = */ 1024,
    /* .MaxTessPatchComponents = */ 120,
    /* .MaxPatchVertices = */ 32,
    /* .MaxTessGenLevel = */ 64,
    /* .MaxViewports = */ 16,
    /* .MaxVertexAtomicCounters = */ 0,
    /* .MaxTessControlAtomicCounters = */ 0,
    /* .MaxTessEvaluationAtomicCounters = */ 0,
    /* .MaxGeometryAtomicCounters = */ 0,
    /* .MaxFragmentAtomicCounters = */ 8,
    /* .MaxCombinedAtomicCounters = */ 8,
    /* .MaxAtomicCounterBindings = */ 1,
    /* .MaxVertexAtomicCounterBuffers = */ 0,
    /* .MaxTessControlAtomicCounterBuffers = */ 0,
    /* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
    /* .MaxGeometryAtomicCounterBuffers = */ 0,
    /* .MaxFragmentAtomicCounterBuffers = */ 1,
    /* .MaxCombinedAtomicCounterBuffers = */ 1,
    /* .MaxAtomicCounterBufferSize = */ 16384,
    /* .MaxTransformFeedbackBuffers = */ 4,
    /* .MaxTransformFeedbackInterleavedComponents = */ 64,
    /* .MaxCullDistances = */ 8,
    /* .MaxCombinedClipAndCullDistances = */ 8,
    /* .MaxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .maxDualSourceDrawBuffersEXT = */ 1,

    /* .limits = */ {
        /* .nonInductiveForLoops = */ 1,
        /* .whileLoops = */ 1,
        /* .doWhileLoops = */ 1,
        /* .generalUniformIndexing = */ 1,
        /* .generalAttributeMatrixVectorIndexing = */ 1,
        /* .generalVaryingIndexing = */ 1,
        /* .generalSamplerIndexing = */ 1,
        /* .generalVariableIndexing = */ 1,
        /* .generalConstantMatrixVectorIndexing = */ 1,
    }};




    std::string mErrorMessage;
    TCompiler* compiler = nullptr;

    //TBuiltInResource Resources = glslang::DefaultTBuiltInResource;
//
//   Deduce the language from the filename.  Files must end in one of the
//   following extensions:
//
//   .vert = vertex
//   .tesc = tessellation control
//   .tese = tessellation evaluation
//   .geom = geometry
//   .frag = fragment
//   .comp = compute
//   .rgen = ray generation
//   .rint = ray intersection
//   .rahit = ray any hit
//   .rchit = ray closest hit
//   .rmiss = ray miss
//   .rcall = ray callable
//   .mesh  = mesh
//   .task  = task
//   Additionally, the file names may end in .<stage>.glsl and .<stage>.hlsl
//   where <stage> is one of the stages listed above.
//
EShLanguage FindLanguage(const std::string& name, bool parseStageName)
{
    std::string stageName;
    //if (shaderStageName)
    //    stageName = shaderStageName;
    //else 
    if (parseStageName) {
        // Note: "first" extension means "first from the end", i.e.
        // if the file is named foo.vert.glsl, then "glsl" is first,
        // "vert" is second.
        size_t firstExtStart = name.find_last_of(".");
        bool hasFirstExt = firstExtStart != std::string::npos;
        size_t secondExtStart = hasFirstExt ? name.find_last_of(".", firstExtStart - 1) : std::string::npos;
        bool hasSecondExt = secondExtStart != std::string::npos;
        std::string firstExt = name.substr(firstExtStart + 1, std::string::npos);
        bool usesUnifiedExt = hasFirstExt && (firstExt == "glsl" || firstExt == "hlsl");
        //I commented bellow
        //if (usesUnifiedExt && firstExt == "hlsl")
        //    Options |= EOptionReadHlsl;
        if (hasFirstExt && !usesUnifiedExt)
            stageName = firstExt;
        else if (usesUnifiedExt && hasSecondExt)
            stageName = name.substr(secondExtStart + 1, firstExtStart - secondExtStart - 1);
        else {
            //I commented bellow
            //usage();
            return EShLangVertex;
        }
    } else
        stageName = name;

    if (stageName == "vert")
        return EShLangVertex;
    else if (stageName == "tesc")
        return EShLangTessControl;
    else if (stageName == "tese")
        return EShLangTessEvaluation;
    else if (stageName == "geom")
        return EShLangGeometry;
    else if (stageName == "frag")
        return EShLangFragment;
    else if (stageName == "comp")
        return EShLangCompute;
    else if (stageName == "rgen")
        return EShLangRayGen;
    else if (stageName == "rint")
        return EShLangIntersect;
    else if (stageName == "rahit")
        return EShLangAnyHit;
    else if (stageName == "rchit")
        return EShLangClosestHit;
    else if (stageName == "rmiss")
        return EShLangMiss;
    else if (stageName == "rcall")
        return EShLangCallable;
    else if (stageName == "mesh")
        return EShLangMeshNV;
    else if (stageName == "task")
        return EShLangTaskNV;

    return EShLangVertex;
}


void SetMessageOptions(EShMessages& messages, int Options)
{
    if (Options & EOptionRelaxedErrors)
        messages = (EShMessages)(messages | EShMsgRelaxedErrors);
    if (Options & EOptionIntermediate)
        messages = (EShMessages)(messages | EShMsgAST);
    if (Options & EOptionSuppressWarnings)
        messages = (EShMessages)(messages | EShMsgSuppressWarnings);
    if (Options & EOptionSpv)
        messages = (EShMessages)(messages | EShMsgSpvRules);
    if (Options & EOptionVulkanRules)
        messages = (EShMessages)(messages | EShMsgVulkanRules);
    if (Options & EOptionOutputPreprocessed)
        messages = (EShMessages)(messages | EShMsgOnlyPreprocessor);
    if (Options & EOptionReadHlsl)
        messages = (EShMessages)(messages | EShMsgReadHlsl);
    if (Options & EOptionCascadingErrors)
        messages = (EShMessages)(messages | EShMsgCascadingErrors);
    if (Options & EOptionKeepUncalled)
        messages = (EShMessages)(messages | EShMsgKeepUncalled);
    if (Options & EOptionHlslOffsets)
        messages = (EShMessages)(messages | EShMsgHlslOffsets);
    if (Options & EOptionDebug)
        messages = (EShMessages)(messages | EShMsgDebugInfo);

    //NOTE I Disabled them (Grapix) because we don't need them
    /*if (HlslEnable16BitTypes)
        messages = (EShMessages)(messages | EShMsgHlslEnable16BitTypes);
    if ((Options & EOptionOptimizeDisable) || !ENABLE_OPT)
        messages = (EShMessages)(messages | EShMsgHlslLegalization);
    if (HlslDX9compatible)
        messages = (EShMessages)(messages | EShMsgHlslDX9Compatible);
    if (DumpBuiltinSymbols)
        messages = (EShMessages)(messages | EShMsgBuiltinSymbolTable);*/
}

public:

GlslangCompiler() {
    ShInitialize();
}

~GlslangCompiler() {
    ShFinalize();
}

const std::string& getErrorMessage() {
    return mErrorMessage;
}


bool compile(const std::string& filename, const std::string& source) {

    EShLanguage language  = FindLanguage(filename, true); //guess the language based on files name
    compiler = ConstructCompiler(language, 0);

    EShMessages messages = EShMsgDefault;
    SetMessageOptions(messages, EOptionNone);

    int numStrings = 1;
    const char* shaderStrings[1]; shaderStrings[0] = source.c_str();

    int ret = ShCompile(compiler, shaderStrings, 1, nullptr, EShOptNone, &Resources, EOptionNone, (EOptionNone & EOptionDefaultDesktop) ? 110 : 100, false, messages);
    mErrorMessage = ShGetInfoLog(compiler);

    //std::cout << mErrorMessage << std::endl;

    return ret;
}

void compileWithFailure(const std::string& filename, const std::string& source) {

    bool res = compile(filename, source);
    if (!res) {
        std::string s = "shader compilation failed for shader at" + filename + "\n";
        s += "Glslang resume:\n" + mErrorMessage; 
        LEVEK_RENDERING_FAIL(s.c_str());
    }
  
}

};
};