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

#include "core/types/URI.h"
#include <memory>
#include <string>

namespace us {

class EnumerationTypePrivate;

class EnumerationType
{
public:
    class Option
    {
    public:
        Option(const std::string &aName = "");

        std::string name() const;

        bool operator==(const Option &aOther) const;

        bool operator!=(const Option &aOther) const;

        bool operator<(const Option &aOther) const;

    private:
        friend struct std::hash<Option>;
        std::string _name;
    };

    class Listener
    {
    public:
        virtual void onNameChanged(EnumerationType *);
        virtual void onDescriptionChanged(EnumerationType *);
        virtual void onOptionsChanged(EnumerationType *);
    };

    EnumerationType(const std::string &aID);

    virtual ~EnumerationType();

    /**
     * Returns the name of the EnumerationType.
     */
    std::string name() const;
    /**
     * Returns an explanation about what this EnumerationType is.
     */
    std::string description() const;
    /**
     * Returns the unique id with which the EnumerationType is identified
     * in a product.
     */
    std::string id() const;

    void setName(const std::string &aName);

    void setDescription(const std::string &aDescription);

    void addOption(const Option &aOption, const URI &aImage = URI());

    void removeOption(const Option &aOption);

    void setOptions(const std::vector<std::pair<Option, URI>> &aOptions);

    const std::vector<std::pair<Option, URI>> options() const;

    URI image(const Option &aOption) const;

    void addListener(Listener *aListener);

    void removeListener(Listener *aListener);

private:
    friend class EnumerationTypePrivate;
    std::unique_ptr<EnumerationTypePrivate> _d;
};

} // namespace us

namespace std {
template<>
struct hash<us::EnumerationType::Option>
{
    std::size_t operator()(const us::EnumerationType::Option &o) const noexcept
    {
        return std::hash<std::string>()(o._name);
    }
};
} // namespace std
