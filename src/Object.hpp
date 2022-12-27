#pragma once

#include "Common.hpp"
#include "PropertyList.hpp"

LEVEK_NAMESPACE_BEGIN

/**
 * @brief Inspired by Nori renderer (class NoriObject) by Wenzel Jackob
 * 
 */
class LevekObject {

public:

    enum EClassType {
        EScene = 0,
        ETexture,
        EMesh,
        ECamera
    };

    static std::string classTypeName(EClassType type) {
        switch (type)
        {
        case EScene: return "scene";
        case ETexture: return "texture";
        case EMesh: return "mesh";
        case ECamera: return "camera";
        default:
            throw LevekException("not found class type: %d", type);
        }
    }

    virtual ~LevekObject() {}

    virtual EClassType getClassType() const = 0;

    virtual void addChild(LevekObject* child) {
        throw LevekException(
                "LevekObject::addChild() is not implemented for objects of type '%s'!",
                classTypeName(getClassType()));
    }

    virtual void activate() { /* Do nothing */ }
    virtual std::string toString() const = 0;

    void setName(const std::string& name) { mName = name; }
    const std::string& getName() const { return mName; }

private:
    std::string mName;

};


/**
 * @brief Adapted from the NoriRenderer by Wenzel Jackob
 * 
 * \brief Factory for Nori objects
 *
 * This utility class is part of a mini-RTTI framework and can 
 * instantiate arbitrary Nori objects by their name.
 */
class LevekObjectFactory {
public:
    typedef std::function<LevekObject *(const PropertyList &)> Constructor;

    /**
     * \brief Register an object constructor with the object factory
     *
     * This function is called by the macro \ref NORI_REGISTER_CLASS
     *
     * \param name
     *     An internal name that is associated with this class. This is the
     *     'type' field found in the scene description XML files
     *
     * \param constr
     *     A function pointer to an anonymous function that is
     *     able to call the constructor of the class.
     */
    static void registerClass(const std::string &name, const Constructor &constr);

    /**
     * \brief Construct an instance from the class of the given name
     *
     * \param name
     *     An internal name that is associated with this class. This is the
     *     'type' field found in the scene description XML files
     *
     * \param propList
     *     A list of properties that will be passed to the constructor
     *     of the class.
     */
    static LevekObject *createInstance(const std::string &name,
            const PropertyList &propList) {
        if (!m_constructors || m_constructors->find(name) == m_constructors->end())
            throw LevekException("A constructor for class \"%s\" could not be found!", name);
        return (*m_constructors)[name](propList);
    }

    static void printRegisteredClasses() {
        if(m_constructors)
            for(auto v : *m_constructors)
                std::cout << v.first << std::endl;
    }

private:
    static std::map<std::string, Constructor> *m_constructors;
};

/// taken from the Nori renderer by Wenzel Jackob
/// Macro for registering an object constructor with the \ref NoriObjectFactory
#define NORI_REGISTER_CLASS(cls, name) \
    cls *cls ##_create(const PropertyList &list) { \
        return new cls(list); \
    } \
    static struct cls ##_{ \
        cls ##_() { \
            NoriObjectFactory::registerClass(name, cls ##_create); \
        } \
    } cls ##__NORI_;

/// taken from the Nori renderer by Wenzel Jackob
/// Macro for registering an object constructor with the \ref NoriObjectFactory
#define NORI_REGISTER_TEMPLATED_CLASS(cls, T, name) \
    cls<T> * cls ##_## T ##_create(const PropertyList &list) { \
        return new cls<T>(list); \
    } \
    static struct cls ##_## T ##_{ \
        cls ##_## T ##_() { \
            NoriObjectFactory::registerClass(name, cls ##_## T ##_create); \
        } \
    } cls ## T ##__NORI_;


LEVEK_NAMESPACE_END