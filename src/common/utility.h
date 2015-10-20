/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年10月17日 星期六 18时34分43秒
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


// Windows Cygwin Environment
#ifdef __CYGWIN__
  #include "patch/cpp11.h"
#endif

namespace common {

class utility {
    // using boost_alg = boost::algorithm;
public:
    static void trim_left(std::string& input_str) { boost::trim_left(input_str); }
    static void trim_right(std::string& input_str) { boost::trim_right(input_str); }
    static void trim(std::string& input_str) { 
        if (input_str[0] == '\t') input_str = input_str.substr(1);
        boost::trim(input_str); 
    }

    static void replace_all(std::string& origin, char from, char to)
    {
        std::replace(origin.begin(), origin.end(), from, to);
    }
    static void replace_all_string(std::string& origin, const std::string& from, const std::string& to)
    {
        std::string::size_type idx = 0;
        while ((idx = origin.find(from, idx)) != std::string::npos) {
            origin.replace(idx, from.size(), to);
            idx += to.size();
        }
    }
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
    static bool split_string(const std::string& str, const std::string& delim, std::vector<std::string>& str_vec, bool delim_end = false)
    {
        size_t ps = 0, pe = 0;
        while ((pe = str.find(delim, ps)) != std::string::npos) {
            if (pe != ps)
                str_vec.push_back(str.substr(ps, pe - ps));
            ps = pe + delim.length();
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

    static bool gen_range(int beg, const int end, std::vector<std::string>& range_vec)
    {
        assert(beg <= end);
        while (beg <= end)
        {
           range_vec.push_back(std::to_string(beg++));
        }
        return true;
    }
    static bool gen_range_str(int beg, const int end, std::vector<std::string>& range_vec)
    {
        assert(beg <= end);

        std::ostringstream oss;
        while (beg <= end)
        {
            oss.str("");
            oss << std::setw(6) << std::setfill('0') << beg++;
            range_vec.push_back(oss.str());
        }
        return true;
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
