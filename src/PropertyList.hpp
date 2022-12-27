#pragma once

/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob, Romain Prévost

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Common.hpp"
#include <map>
#include <glm/glm.hpp>

LEVEK_NAMESPACE_BEGIN

/**
 * @brief This file is largely inspired by Nori Renderer by Wenzel Jackob
 * 
 * \brief This is an associative container used to supply the constructors
 * of \ref NoriObject subclasses with parameter information.
 */
class PropertyList {
public:
    PropertyList() { }

    bool has(const std::string & name) const {
        return (m_properties.find(name) != m_properties.end());
    }

    void list() const {
        std::cout << "listing properties:" << "\n";
        for (auto const& x : m_properties) {
            std::cout << "\t" << x.first << " " << x.second.type << "\n";
        }
    }

    /// Set a boolean property
    void setBoolean(const std::string &name, const bool &value);
    
    /// Get a boolean property, and throw an exception if it does not exist
    bool getBoolean(const std::string &name) const;

    /// Get a boolean property, and use a default value if it does not exist
    bool getBoolean(const std::string &name, const bool &defaultValue) const;

    /// Set an integer property
    void setInteger(const std::string &name, const int &value);
    
    /// Get an integer property, and throw an exception if it does not exist
    int getInteger(const std::string &name) const;

    /// Get am integer property, and use a default value if it does not exist
    int getInteger(const std::string &name, const int &defaultValue) const;

    /// Set a float property
    void setFloat(const std::string &name, const float &value);
    
    /// Get a float property, and throw an exception if it does not exist
    float getFloat(const std::string &name) const;

    /// Get a float property, and use a default value if it does not exist
    float getFloat(const std::string &name, const float &defaultValue) const;

    /// Set a string property
    void setString(const std::string &name, const std::string &value);

    /// Get a string property, and throw an exception if it does not exist
    std::string getString(const std::string &name) const;

    /// Get a string property, and use a default value if it does not exist
    std::string getString(const std::string &name, const std::string &defaultValue) const;

    /// Set a color property
    void setColor(const std::string &name, const glm::vec3 &value);

    /// Get a color property, and throw an exception if it does not exist
    glm::vec3 getColor(const std::string &name) const;

    /// Get a color property, and use a default value if it does not exist
    glm::vec3 getColor(const std::string &name, const glm::vec3 &defaultValue) const;

    /// Set a point property
    void setPoint3(const std::string &name, const glm::vec3 &value);

    /// Get a point property, and throw an exception if it does not exist
    glm::vec3 getPoint3(const std::string &name) const;

    /// Get a point property, and use a default value if it does not exist
    glm::vec3 getPoint3(const std::string &name, const glm::vec3 &defaultValue) const;

    /// Set a vector property
    void setVector3(const std::string &name, const glm::vec3 &value);

    /// Get a vector property, and throw an exception if it does not exist
    glm::vec3 getVector3(const std::string &name) const;

    /// Get a vector property, and use a default value if it does not exist
    glm::vec3 getVector3(const std::string &name, const glm::vec3 &defaultValue) const;

    /// Set a point property
    void setPoint2(const std::string &name, const glm::vec2 &value);

    /// Get a point property, and throw an exception if it does not exist
    glm::vec2 getPoint2(const std::string &name) const;

    /// Get a point property, and use a default value if it does not exist
    glm::vec2 getPoint2(const std::string &name, const glm::vec2 &defaultValue) const;

    /// Set a vector property
    void setVector2(const std::string &name, const glm::vec2 &value);

    /// Get a vector property, and throw an exception if it does not exist
    glm::vec2 getVector2(const std::string &name) const;

    /// Get a vector property, and use a default value if it does not exist
    glm::vec2 getVector2(const std::string &name, const glm::vec2 &defaultValue) const;

    /// Set a transform property
    //void setTransform(const std::string &name, const Transform &value);

    /*
    /// Get a transform property, and throw an exception if it does not exist
    Transform getTransform(const std::string &name) const;

    /// Get a transform property, and use a default value if it does not exist
    Transform getTransform(const std::string &name, const Transform &defaultValue) const;
    */

private:
    /* Custom variant data type (stores one of boolean/integer/float/...) */
    struct Property {
        enum {
            Boolean_type, Integer_type, Float_type,
            String_type, Color_type, Point3_type,
            Vector3_type, Point2_type,
            Vector2_type, Transform_type
        } type;

        /* Visual studio lacks support for unrestricted unions (as of ver. 2013) */
        struct Value
        {
            Value() : Boolean_value(false) { }
            ~Value() { }

            bool Boolean_value;
            int Integer_value;
            float Float_value;
            std::string String_value;
            glm::vec3 Color_value;
            glm::vec3 Point3_value;
            glm::vec3 Vector3_value;
            glm::vec2 Point2_value;
            glm::vec2 Vector2_value;
            //Transform Transform_value;
        } value;

        Property() : type(Boolean_type) { }
    };

    std::map<std::string, Property> m_properties;
};

LEVEK_NAMESPACE_END