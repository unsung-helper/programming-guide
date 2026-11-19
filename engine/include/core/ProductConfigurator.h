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

#include "ExtensionProvider.h"
#include "core/CustomTypes.h"
#include <memory>
#include "Logs.h"

namespace us {

class INodeFactory;
class IDataStore;
class ITypeReader;
class ITypeWriter;
class ProductPrivate;

class ProductConfigurator
{
public:
    ProductConfigurator();

    virtual ~ProductConfigurator();

    ProductConfigurator(const ProductConfigurator &) = delete;
    ProductConfigurator &operator=(const ProductConfigurator &) = delete;
    ProductConfigurator(ProductConfigurator &&aOther);
    ProductConfigurator &operator=(ProductConfigurator &&aOther);

    /**
    * Registers the given node factory to be used by the product
    */
    virtual ProductConfigurator &nodeFactory(std::shared_ptr<INodeFactory> aNodeFactory);
    /**
    * Adds the given extension provider to be used by the product
    */
    virtual ProductConfigurator &extension(ExtensionProvider aProvider);
    /**
    * Adds the given extension providers to be used by the product
    */
    virtual ProductConfigurator &extensions(ExtensionProviders aProviders);

    virtual ProductConfigurator &type(CustomType aType);

    virtual ProductConfigurator &conversion(CustomConversion aConversion);

    virtual ProductConfigurator &types(const CustomTypes &aTypes);

    virtual ProductConfigurator &conversions(const CustomConversions &aConversions);
    /**
    * Adds the given data store to this Product 
    */
    virtual ProductConfigurator &dataStore(std::shared_ptr<IDataStore> aDataStore);
    /**
    * Adds the given asset reader to this product 
    */
    virtual ProductConfigurator &reader(std::shared_ptr<ITypeReader> aReader);
    /**
    * Adds the given asset writer to this product 
    */
    virtual ProductConfigurator &writer(std::shared_ptr<ITypeWriter> aWriter);
    /**
    * Adds the given asset readers to this product 
    */
    virtual ProductConfigurator &readers(const std::vector<std::shared_ptr<ITypeReader>> &aReaders);
    /**
    * Adds the given asset writers to this product 
    */
    virtual ProductConfigurator &writers(const std::vector<std::shared_ptr<ITypeWriter>> &aWriter);
    /**
    * Sets the product's log level
    */
    virtual ProductConfigurator &logLevel(Logs::Level aLevel);

protected:
    std::unique_ptr<ProductPrivate> _d;
};

} // namespace us
