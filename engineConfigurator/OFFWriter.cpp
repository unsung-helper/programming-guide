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
#include "OFFWriter.h"
#include "core/types/Mesh.h"

using namespace us;

std::type_index OFFWriter::type() const
{
    return typeid(MeshPtr);
}

std::string OFFWriter::format() const
{
    return "off";
}

void OFFWriter::write(const Any &aAsset, std::ostream &aOut) const
{
    aOut << "OFF" << std::endl;

    if (aAsset.type() != typeid(MeshPtr)) {
        return;
    }
    auto mesh = aAsset.get<MeshPtr>();
    if (!mesh) {
        return;
    }
    mesh->garbage_collection();
    int nbVertices = mesh->n_vertices();
    int nbFaces = mesh->n_faces();

    //ignoring nbEdges
    aOut << nbVertices << " " << nbFaces << " 0" << std::endl;

    std::unordered_map<Mesh::VertexHandle, int> vmap;
    for (auto vit = mesh->vertices_sbegin(); vit != mesh->vertices_end(); ++vit) {
        auto p = mesh->point(*vit);
        aOut << p.x() << " " << p.y() << " " << p.z() << std::endl;
        vmap[*vit] = vmap.size();
    }

    for (auto fit = mesh->faces_sbegin(); fit != mesh->faces_end(); ++fit) {
        std::vector<int> indices;
        for (auto fhit = mesh->fh_ccwiter(*fit); fhit.is_valid(); ++fhit) {
            indices.push_back(vmap[fhit->from()]);
        }
        aOut << indices.size() << " ";
        for (auto &index : indices) {
            aOut << index << " ";
        }
        aOut << std::endl;
    }
}
