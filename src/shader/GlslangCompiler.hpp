
#include <utility>
#include <string>

#include <cstring>
#include "glslang/build_info.h"
#include "glslang/glsl_intrinsic_header.h"

#include "glslang/Include/ShHandle.h"
#include "glslang/Public/ShaderLang.h"
#include "glslang/OSDependent/osinclude.h"

namespace Levek {

class GlslangCompiler {

private:
    std::string mErrorMessage;
    TCompiler* compiler = nullptr;

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

public:

GlslangCompiler() {

}

const std::string& getErrorMessage() {
    return mErrorMessage;
}

bool compile(const std::string& filename, const std::string& source) {

    EShLanguage language  = FindLanguage(filename, true);
    compiler = ConstructCompiler(language, 0);

    return true;
}


};
};