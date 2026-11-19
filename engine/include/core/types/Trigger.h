#pragma once

namespace us {

class Trigger
{
public:
    Trigger();

    operator bool() const;

    Trigger &operator++();

    bool operator<(const Trigger &aOther) const;

    bool operator==(const Trigger &aOther) const;

    bool operator!=(const Trigger &aOther) const;

private:
    int _timestamp;
};

} // namespace us
