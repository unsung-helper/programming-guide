/*
 * Copyright (c) 2024-2026 Jucon BV
 * All rights reserved.
 *
 * This file is part of unsung. Unauthorized copying, modification,
 * distribution, or use of this file is strictly prohibited without prior
 * written consent from Jucon BV.
 *
 * For inquiries regarding the use of this software, please contact: info@juconbv.be
 */

#pragma once
#include "Color.h"
#include "OpenMesh/Core/Mesh/Attributes.hh"
#include "OpenMesh/Core/Mesh/Handles.hh"
#include "OpenMesh/Core/Mesh/Traits.hh"
#include "OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh"
#include <OpenMesh/Core/Geometry/EigenVectorT.hh>
#include <OpenMesh/Core/Utils/PropertyManager.hh>
#include <memory>
#include <unordered_set>

namespace us {

class PropertyName
{
public:
    PropertyName(const std::string &aName = "");

    operator std::string() const;

    operator const char *() const;

    std::string toString() const;

    bool operator==(const PropertyName &aOther) const;

    bool operator!=(const PropertyName &aOther) const;

    bool operator<(const PropertyName &aOther) const;

private:
    friend struct std::hash<PropertyName>;
    std::string _name;
};

} // namespace us

namespace std {
template<>
struct hash<us::PropertyName>
{
    std::size_t operator()(const us::PropertyName &p) const noexcept
    {
        return std::hash<std::string>()(p._name);
    }
};
} // namespace std

namespace us {
struct MeshTraits : public OpenMesh::DefaultTraits {
    using Point = Eigen::Vector3d;
    using Normal = Eigen::Vector3d;
    using TexCoord1D = double;
    using TexCoord2D = Eigen::Vector2d;
    using TexCoord3D = Eigen::Vector3d;
    using Color = us::Color;

    VertexAttributes(OpenMesh::Attributes::Status);
    HalfedgeAttributes(OpenMesh::Attributes::PrevHalfedge |
                       OpenMesh::Attributes::Status);
    EdgeAttributes(OpenMesh::Attributes::Status);
    FaceAttributes(OpenMesh::Attributes::Status);
    VertexTraits{};
    HalfedgeTraits{};
    FaceTraits{};
};

using Mesh = OpenMesh::TriMesh_ArrayKernelT<MeshTraits>;

using MeshPtr = std::shared_ptr<Mesh>;

using Point = MeshTraits::Point;

using Normal = MeshTraits::Normal;

using TexCoord2D = MeshTraits::TexCoord2D;

using VHandle = OpenMesh::VertexHandle;

using HeHandle = OpenMesh::HalfedgeHandle;

using EHandle = OpenMesh::EdgeHandle;

using FHandle = OpenMesh::FaceHandle;

enum class MeshPropertyType { Scalar, Direction };

enum class MeshPropertyTarget { Vertex, Halfedge, Edge, Face };

class MeshProperty
{
public:
    MeshProperty(Mesh &aMesh,
                 const PropertyName &aName,
                 MeshPropertyType aType,
                 MeshPropertyTarget aTarget);

    double &value(Mesh::VertexHandle aH);
    double &value(Mesh::HalfedgeHandle aH);
    double &value(Mesh::EdgeHandle aH);
    double &value(Mesh::FaceHandle aH);

    Eigen::Vector3d &direction(Mesh::VertexHandle aH);
    Eigen::Vector3d &direction(Mesh::HalfedgeHandle aH);
    Eigen::Vector3d &direction(Mesh::EdgeHandle aH);
    Eigen::Vector3d &direction(Mesh::FaceHandle aH);

    MeshPropertyType type() const;
    MeshPropertyTarget target() const;
    std::string name() const;

private:
    template<typename TARGET, typename HANDLE>
    std::function<TARGET &(HANDLE)> createPropertyHandle(Mesh &aMesh,
                                                         const PropertyName &aName) const
    {
        auto pm = OpenMesh::getOrMakeProperty<HANDLE, TARGET>(aMesh, aName);
        return [pm](HANDLE aH) mutable -> TARGET & { return pm[aH]; };
    }

    PropertyName _name;
    MeshPropertyType _type;
    MeshPropertyTarget _target;
    std::function<double &(Mesh::VertexHandle)> _scalarVertex;
    std::function<double &(Mesh::HalfedgeHandle)> _scalarHalfedge;
    std::function<double &(Mesh::EdgeHandle)> _scalarEdge;
    std::function<double &(Mesh::FaceHandle)> _scalarFace;
    std::function<Eigen::Vector3d &(Mesh::VertexHandle)> _directionVertex;
    std::function<Eigen::Vector3d &(Mesh::HalfedgeHandle)> _directionHalfedge;
    std::function<Eigen::Vector3d &(Mesh::EdgeHandle)> _directionEdge;
    std::function<Eigen::Vector3d &(Mesh::FaceHandle)> _directionFace;
};

class Identifiers
{
public:
    using const_iterator = std::unordered_set<int>::const_iterator;

    Identifiers();

    virtual ~Identifiers();

    Identifiers(const Identifiers &aOther);

    Identifiers(Identifiers &&aOther);

    Identifiers &operator=(const Identifiers &aOther);

    Identifiers &operator=(Identifiers &&aOther);

    int size() const;

    bool contains(int aID) const;

    void add(int aID);

    void remove(int aID);

    const_iterator cbegin() const;

    const_iterator cend() const;

private:
    std::unique_ptr<std::unordered_set<int>> _ids;
};

class MeshMetadata
{
public:
    MeshMetadata();

    virtual ~MeshMetadata();

    int addIdentifier(const std::string &aIdentifier);

    std::string identifierName(int aIndex) const;
    int identifierIndex(const std::string &aName) const;

    int nbIdentifiers() const;

    std::function<Identifiers &(OpenMesh::FaceHandle)> faceIdentifiers();

    std::function<Identifiers &(OpenMesh::HalfedgeHandle)> halfedgeIdentifiers();

    std::function<Identifiers &(OpenMesh::EdgeHandle)> edgeIdentifiers();

    std::function<Identifiers &(OpenMesh::VertexHandle)> vertexIdentifiers();

    bool addProperty(const PropertyName &aName, MeshPropertyType aType, MeshPropertyTarget aTarget);

    bool hasProperty(const PropertyName &aName);

    bool removeProperty(const PropertyName &aName);

    MeshProperty getProperty(const PropertyName &aName);

    std::unordered_set<PropertyName> properties() const;

private:
    friend MeshMetadata &metadata(Mesh &aMesh);

    Mesh *_mesh;

    std::vector<std::string> _identifierNames;

    std::unordered_map<PropertyName, std::tuple<MeshPropertyTarget, MeshPropertyType>> _properties;
};

MeshMetadata &metadata(Mesh &aMesh);

} // namespace us
