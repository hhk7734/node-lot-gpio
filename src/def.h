/*
 * MIT License
 * Copyright (c) 2019 Hyeonki Hong <hhk7734@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <map>
#include <string>

namespace def
{
std::map<std::string, int> mode_str_to_num = {
    { "IN", 0 },   { "OUT", 1 },  { "ALT0", 2 }, { "ALT1", 3 }, { "ALT2", 4 },
    { "ALT3", 5 }, { "ALT4", 6 }, { "ALT5", 7 }, { "ALT6", 8 }, { "ALT7", 9 },
};
std::string mode_num_to_str[] = { "IN",   "OUT",  "ALT0", "ALT1", "ALT2",
                                  "ALT3", "ALT4", "ALT5", "ALT6", "ALT7" };

std::map<std::string, int> status_str_to_num = { { "LOW", 0 }, { "HIGH", 1 } };
std::string                status_num_to_str[] = { "LOW", "HIGH" };
}    // namespace def