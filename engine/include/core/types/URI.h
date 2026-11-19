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

#include <string>
#include <memory>
#include <vector>

namespace us {

/**
 * Class representing the location of an asset
 */
class URI
{
    struct URIPrivate;

public:
    const static std::string DATA_URL_SCHEME;

    const static std::string LOCAL_SCHEME_ABSOLUTE;

    const static std::string LOCAL_SCHEME_RELATIVE;

    URI();

    ~URI();

    URI(const URI& aOther);

    URI(URI&& aOther);

    URI& operator = (const URI& aOther);

    URI& operator = (URI&& aOther);

    std::string scheme() const;

    void setScheme(const std::string& aScheme);

    void prependPath(const std::vector<std::string>& aPath);

    void appendPath(const std::vector<std::string>& aPath);

    std::vector<std::string> path() const;

    std::string baseName() const;

    void setBaseName(const std::string& aBasename);

    std::string data() const;

    std::string extension() const;

    static URI fromString(const std::string &aString);

    std::string toString() const;

    bool operator==(const URI &aOther) const;

    bool operator!=(const URI &aOther) const;

    bool valid() const;

    static URI toDataURI(const std::string& aExtension, const std::string& aData);

private:

    URI( std::unique_ptr<URIPrivate> && aImpl );

    std::unique_ptr<URIPrivate> _d;
};

} // namespace us
