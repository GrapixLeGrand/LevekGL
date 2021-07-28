#pragma once


#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>


#define LEVEK_RENDERING_ASSERT_(EXPR) \
    LEVEK_RENDERING_ASSERT(EXPR, "")

#define LEVEK_RENDERING_ASSERT(EXPR, MESSAGE) \
    if (!EXPR) { \
        Levek::LevekRenderingAssert(__LINE__, __FILE__, MESSAGE); \
    }

#define LEVEK_RENDERING_FAIL(MESSAGE)    Levek::LevekRenderingAssert(__LINE__, __FILE__, MESSAGE);
#define LEVEK_RENDERING_INFO(MESSAGE)    Levek::LevekRenderingInfo(MESSAGE);

#define LEVEK_STRING_INT(STR, N) ((std::string(STR) + ": " + std::to_string(N)).c_str())
#define LEVEK_RENDERING_ID_INFO(MESSAGE_1, ID) LEVEK_RENDERING_INFO(LEVEK_STRING_INT(MESSAGE_1, ID))
#define LEVEK_RENDERING_ID_FAIL(MESSAGE_1, ID) LEVEK_RENDERING_FAIL(LEVEK_STRING_INT(MESSAGE_1, ID))

namespace Levek {

    static const std::string LevekRenderingRedBegin("\033[1;31m");
    static const std::string LevekRenderingResetColor("\033[0m");
    static const std::string LevekRenderingYellowBegin("\033[1;33m");

    static void LevekRenderingInfo(const char* message) {
        std::string type = LevekRenderingYellowBegin + "Rendering: Info " + LevekRenderingResetColor;
        std::cout << type << message << std::endl;
    }

    static void LevekRenderingAssert(int line, const char* fileName, const char* message) {
        std::string type = LevekRenderingRedBegin + "Rendering: assert " + LevekRenderingResetColor;
        std::cout << type << message << "\n" <<"    at " << fileName << ":" << line << std::endl;
        exit(1);
    }
};

#define ERROR_MSG_FULL_PATH_ENABLE 1
#define ERROR_DEBUG_MSG_ENABLE 1
#define ERROR_DEBUG_MSG_SILENT 1

#define ERROR_MSG_DEBUG_PREFIX std::string("*** DEBUG ***")
#define ERROR_MSG_ERROR_PREFIX std::string("*** ERROR ***")
#define ERROR_MSG_SPACE std::string(" ")

#define TEXT_COLOR_RED std::string("\033[0;31m")
#define TEXT_COLOR_YELLOW std::string("\033[0;33m")
#define TEXT_COLOR_BLUE std::string("\033[0;34m")
#define TEXT_COLOR_GREEN std::string("\033[0;32m")
#define TEXT_COLOR_RESET std::string("\033[0m")

#define TEXT_HEADER_ERROR TEXT_COLOR_RED + std::string("*** ERROR ***") + TEXT_COLOR_RESET
#define TEXT_HEADER_WARNING TEXT_COLOR_YELLOW + std::string("*** WARNING ***") + TEXT_COLOR_RESET
#define TEXT_HEADER_INFO TEXT_COLOR_BLUE + std::string("*** INFO ***") + TEXT_COLOR_RESET
#define TEXT_HEADER_SUCCESS TEXT_COLOR_GREEN + std::string("*** SUCCESS ***") + TEXT_COLOR_RESET
    


#define ASSERT(x) { if (!(x)) x; }
#define GL_CHECK(fun) \
            clearErrors(); \
            fun; \
            errorHandler(__LINE__, __FILE__);

#define DEBUG_M(str) \
        const std::string tmp(str); \
        MESSAGE_D(tmp); \
            
#define MESSAGE_TEST(k) \
    std::cout << k << std::endl; \

#define MESSAGE_D(m) \
    std::cout << ERROR_MSG_DEBUG_PREFIX + ERROR_MSG_SPACE + m.c_str() << std::endl; \

//#define ERR_M(str) \
            
    
void clearErrors();
void errorHandler(int line, std::string path);
std::vector<std::string> split(const std::string & str, const std::string & delim);
void message(const std::string& m);
void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam);

static const std::string redBegin("\033[1;31m");
static const std::string reset("\033[0m");

#endif

//#define ERROR_MANAGER_IMPLEMENTATION //////

#ifdef ERROR_MANAGER_IMPLEMENTATION

std::vector<std::string> split(const std::string & str, const std::string & delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

std::string getFileName(const std::string& pathName) {
    return split(pathName, "\\").back();
}

std::string errorEnumIntToStr(GLenum err) {

    const char* res;
    switch (err) {

        case 0x500: res = "GL_INVALID_ENUM \n Given when an enumeration parameter is not a legal enumeration for that function. This is given only for local problems; if the spec allows the enumeration in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead."; break;
        case 0x501: res = "GL_INVALID_VALUE \n Given when a value parameter is not a legal value for that function. This is only given for local problems; if the spec allows the value in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead."; break;
        case 0x502: res = "GL_INVALID_OPERATION \n Given when the set of state for a command is not legal for the parameters given to that command. It is also given for commands where combinations of parameters define what the legal parameters are."; break;
        case 0x503: res = "GL_STACK_OVERFLOW \n Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size."; break;
        case 0x504: res = "GL_STACK_UNDERFLOW \n Given when a stack popping operation cannot be done because the stack is already at its lowest point."; break;
        case 0x505: res = "GL_OUT_OF_MEMORY \n Given when performing an operation that can allocate memory, and the memory cannot be allocated. The results of OpenGL functions that return this error are undefined; it is allowable for partial execution of an operation to happen in this circumstance."; break;
        case 0x506: res = "GL_INVALID_FRAMEBUFFER_OPERATION \n Given when doing anything that would attempt to read from or write/render to a framebuffer that is not complete."; break;
        case 0x507: res = "GL_CONTEXT_LOST \n Given if the OpenGL context has been lost, due to a graphics card reset."; break;
        case 0x8031: res = "GL_TABLE_TOO_LARGE \n Part of the ARB_imaging extension."; break;
        default: res = "NO ERROR CODE FOUNDS"; break;
    }

    return std::string(res);
}

void clearErrors() { while (glGetError() != GL_NO_ERROR); }

void errorHandler(int line, std::string path) {
    GLenum errorCode;
    if ((errorCode = glGetError()) != GL_NO_ERROR) {
     
        std::string fileName = getFileName(path);
        std::string message = TEXT_HEADER_ERROR + " <" + fileName + ", " + std::to_string(line) + "> errcode : " + std::to_string(errorCode);
        std::cout << message.c_str() << std::endl;
        std::cout << std::string("Description : ") + errorEnumIntToStr(errorCode) << std::endl;
        
        if (ERROR_MSG_FULL_PATH_ENABLE) {
            std::cout << ("full path : " + path).c_str() << std::endl;
        }

        exit(1);
      
    }
}

void message(const std::string& m) {
    if (ERROR_DEBUG_MSG_SILENT) {
        std::cout << m.c_str() << std::endl;
    } else {
        std::cout << ERROR_MSG_DEBUG_PREFIX + ERROR_MSG_SPACE + m.c_str() << std::endl;
    }
}

void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    std::cout << redBegin + "Opengl  " + reset << message << std::endl;
    //exit(1);
    /*
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                type, severity, message );
                */
}

#endif