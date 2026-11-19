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
#include <vector>

namespace us {

bool startsWith(const std::string & aString, const std::string & aPattern);

bool contains(const std::string &aString, const std::string &aPattern);

std::vector<std::string> split(const std::string &aString,
                               const std::string &aDelimiter,
                               bool aSkipEmptyWords = true);

std::string join(const std::vector<std::string> &aStrings, const std::string &aDelimiter);

std::wstring toWstring(const std::string &str);

std::string fromWstring(const std::wstring &str);

std::string trimmed(const std::string &aString);

std::string toLowerCase(std::string s);

void stripCR(std::string &aString) noexcept;

bool platformIndependentGetLine(std::istream &aIn, std::string &aLine);

void replaceAll(std::string &aString, const std::string &aSource, const std::string &aTarget);

} // namespace us
