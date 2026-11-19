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
#include "OFFReader.h"
#include "core/Any.h"
#include "core/types/Mesh.h"
#include "core/types/Vec3.h"
#include "util/StringUtil.h"

using namespace us;

namespace {

std::pair<int, bool> readInt(const std::string &aWord)
{
    int result;
    try {
        result = std::stoi(aWord);
    } catch (...) {
        return {-1, false};
    }
    return {result, true};
};

std::pair<Vec3, bool> readVec3(const std::string &aLine)
{
    Vec3 result;
    auto coords = split(aLine, " ");
    if (coords.size() < 3) {
        return {result, false};
    }
    try {
        result.x() = std::stof(coords.at(0));
        result.y() = std::stof(coords.at(1));
        result.z() = std::stof(coords.at(2));
    } catch (...) {
        return {result, false};
    }
    return {result, true};
};

} // namespace

std::type_index OFFReader::type() const
{
    return typeid(MeshPtr);
}

std::vector<std::string> OFFReader::formats() const
{
    return {"off"};
}

us::Any OFFReader::read(std::istream &aIn) const
{
    bool eof = false;
    std::string line;
    auto nextUncommentedLine = [&]() {
        do {
            eof = !platformIndependentGetLine(aIn, line);
        } while (!eof && startsWith(line, "#"));
    };

    MeshPtr result = std::make_shared<Mesh>();

    nextUncommentedLine();
    if (eof) {
        return result;
    }
    if (contains(line, "OFF")) { //ignore
        nextUncommentedLine();
        if (eof) {
            return result;
        }
    }
    auto words = split(line, " ");
    if (words.size() < 2) { //invalid header
        return result;
    }

    auto [nbVertices, nbVerticesRead] = readInt(words.at(0));
    if (!nbVerticesRead) {
        return result;
    }
    auto [nbFaces, nbFacesRead] = readInt(words.at(1));
    if (!nbFacesRead) {
        return result;
    }

    std::unordered_map<int, Mesh::VertexHandle> vmap;

    for (int i = 0; i < nbVertices; ++i) {
        nextUncommentedLine();
        if (eof) {
            return result;
        }
        auto [pos, success] = readVec3(line);
        if (!success) {
            return result;
        }
        vmap[i] = result->add_vertex(pos);
    }

    for (int i = 0; i < nbFaces; ++i) {
        nextUncommentedLine();
        if (eof) {
            return result;
        }
        std::vector<Mesh::VertexHandle> face;
        auto indices = split(line, " ");
        if (indices.size() < 1) {
            continue;
        }
        auto [nbv, success] = readInt(indices.at(0));
        if (!success || indices.size() < (nbv + 1)) {
            continue;
        }
        for (int j = 1; j <= nbv && success; ++j) {
            auto [index, s] = readInt(indices.at(j));
            success &= s && vmap.contains(index);
            face.push_back(vmap[index]);
        }
        if (!success) {
            continue;
        }
        result->add_face(face);
    }
    return result;
}
