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

#include "EngineConfigurator.h"

#include "core/extensions/cache/CacheExtension.h"
#include "data/DataUrlDataStore.h"
#include "data/HttpDataStore.h"
#include "data/LocalDataStore.h"
#include "formats/CSVReader.h"
#include "formats/CSVWriter.h"
#include "formats/DMReader.h"
#include "formats/DMWriter.h"
#include "formats/DPReader.h"
#include "formats/DPWriter.h"
#include "formats/JPEGReader.h"
#include "formats/JPEGWriter.h"
#include "formats/JSONReader.h"
#include "formats/JSONWriter.h"
#include "formats/OBJReader.h"
#include "formats/OBJWriter.h"
#include "formats/PNGReader.h"
#include "formats/PNGWriter.h"
#include "formats/STLReader.h"
#include "formats/STLWriter.h"
#include "formats/SVGReader.h"
#include "formats/SVGWriter.h"
#include "formats/TTFReader.h"
#include "nodes/DefaultNodeFactory.h"
#include "core/NodeFactory.h"
#include "nodes/AggregateNodeFactory.h"

#include "OFFReader.h"
#include "OFFWriter.h"
#include "Twist.h"
#include "AngleParameter.h"
#include "Degrees.h"
#include "Radians.h"

using namespace us;

ProductConfigurator createProductConfigurator()
{
    //factory containing all regular engine nodes
    auto defaultNodeFactory = CreateDefaultNodeFactory();
    //factory for our custom node definitions
    auto customNodeFactory = std::make_shared<NodeFactory>();
    //register custom node definitions to factory
    customNodeFactory->registerDefinition(std::make_unique<AngleParameter::Definition>());
    customNodeFactory->registerDefinition(std::make_unique<Twist::Definition>());
    //combine default and custom nodes in single factory
    auto aggregate = std::make_shared<AggregateNodeFactory>();
    aggregate->add(defaultNodeFactory);
    aggregate->add(customNodeFactory);
    ProductConfigurator result;
    //set log level
    result.logLevel(Logs::Warning)
        //register custom data types
        .type({typeid(Degrees), "Degrees", Degrees(0.0)})
        .type({typeid(Radians), "Radians", Radians(0.0)})
        //registering conversions between our two custom
        //data types
        .conversion({ typeid(Degrees), typeid(Radians), [](const Any &aSource) {
            return Any(Radians(double(aSource.get<Degrees>()) * M_PI / 180.0));
        }})
        .conversion({typeid(Radians), typeid(Degrees), [](const Any &aSource) {
            return Any(Degrees(double(aSource.get<Radians>()) * 180.0 / M_PI));
        }})
        //register combined node factory to engine
        .nodeFactory(aggregate)
        //add cache extension. The engine uses this as default
        //caching strategy: an output can be released once all
        //its dependencent nodes have accepted it, unless the
        //node took longer than 1 second to compute.
        .extension([](INode *aNode) {
            return std::unique_ptr<us::ANodeExtension>(new us::CacheExtension(aNode));
        })
        //registering our custom reader and writer
        .reader(std::make_shared<OFFReader>())
        .writer(std::make_shared<OFFWriter>())
        //registering the default engine's file formats.
        .reader(std::make_shared<OBJReader>())
        .reader(std::make_shared<STLReader>())
        .writer(std::make_shared<STLWriter>())
        .writer(std::make_shared<OBJWriter>())
        .reader(std::make_shared<DMReader>())
        .writer(std::make_shared<DMWriter>())
        .reader(std::make_shared<DPReader>())
        .writer(std::make_shared<DPWriter>())
        .reader(std::make_shared<CSVReader>())
        .writer(std::make_shared<CSVWriter>())
        .writer(std::make_shared<JSONWriter>())
        .reader(std::make_shared<JSONReader>())
        .reader(std::make_shared<TTFReader>())
        .writer(std::make_shared<PNGWriter>())
        .reader(std::make_shared<PNGReader>())
        .writer(std::make_shared<JPEGWriter>())
        .reader(std::make_shared<JPEGReader>())
        .reader(std::make_shared<SVGReader>())
        .writer(std::make_shared<SVGWriter>())
        .dataStore(std::make_shared<DataUrlDataStore>())
        .dataStore(std::make_shared<HttpDataStore>())
        .dataStore(std::make_shared<LocalDataStore>());

    return result;
}
