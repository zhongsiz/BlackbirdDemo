/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年11月17日 星期二 01时47分28秒
*Purpose:
**/

#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cassert>

#include <boost/algorithm/string.hpp>

#include "logger.h"

namespace common {

class utility {
public:
    static bool split(const std::string& str, char delim, std::vector<std::string>& str_vec, bool delim_end = false)
    {
        size_t ps = 0, pe = 0;
        while ((pe = str.find_first_of(delim, ps)) != std::string::npos) {
            str_vec.push_back(str.substr(ps, pe - ps));
            ps = pe + 1;
        }
        if (!delim_end) {
            str_vec.push_back(str.substr(ps));
        }
        return true;
    }
    static bool subsplit(const std::string& str, char delim, std::string& substr)
    {
        size_t ps = str.find_first_of(delim);
        if (ps++ == std::string::npos) return false;

        size_t pe = str.find_first_of(delim, ps + 1);
        if (pe == std::string::npos) return false;

        substr = str.substr(ps, pe - ps);

        return true;
    }

    static bool delete_char(std::string& str, char ch)
    {
        str.erase(std::remove(str.begin(), str.end(), ch), str.end());
        return true;
    }

    template <typename T>
    static std::string to_string(const T& param) {
        return std::to_string(param);
    }

    template <typename T>
    static std::string to_string_pcs(const T& param, const size_t n = 6)
    {
        std::ostringstream out;
        out << std::fixed << std::setprecision(n) << param;
        return out.str();
    }

    template <typename T>
    static bool get_vec_by_step(const std::vector<T>& data, uint32_t& idx, uint32_t step, std::vector<T>& sub_data)
    {
        assert(step > 0);
        if (idx + step > data.size()) {
            sub_data.assign(data.begin() + idx, data.end());
            return false;
        } else {
            sub_data.assign(data.begin() + idx, data.begin() + idx + step);
            idx += step;
            return true;
        }
    }
    template <typename T>
    static bool unique_vector(std::vector<T>& data)
    {
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
        return true;
    }
    template <typename T>
    static bool remove_common_vector(std::vector<T>& vec1, std::vector<T>& vec2)
    {
        std::sort(vec1.begin(), vec1.end());
        std::sort(vec2.begin(), vec2.end());
        auto end_range = std::set_difference(vec1.begin(), vec1.end(),
                vec2.begin(), vec2.end(),
                vec1.begin());
        vec1.erase(end_range, vec1.end());
        return true;
    }
};
}

#endif
