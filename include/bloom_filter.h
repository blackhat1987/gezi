/** 
 *  ==============================================================================
 * 
 *          \file   bloom_filter.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-07-24 18:03:29.429975
 *  
 *  \Description:   TODO try
 *                  bits num 不超过 4G 即 500M 内存最多 否则有问题
 *                  4 * 1024 * 1024 * 1024 = n = 42亿
 *                  所以原始elem 数目不超过  n / 20
 *                  214748364 一般最好 2亿
 *  ==============================================================================
 */

#ifndef BLOOM_FILTER_H_
#define BLOOM_FILTER_H_

#include <string>
#include <vector>
#include <fstream>
#include <cstddef>
#include <algorithm>
#include <cmath>
#include <limits>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
//#include "ul_sign.h"
#include "common_help.h"
#include "ul_log_help.h"
#include "debug_help.h"
//char bloom_filter_suffix[] = {'!', ',', '*', '#', '?', '+', '-'};
class BloomFilter
{
public:
    typedef unsigned int bloom_type;
public:
    BloomFilter(double false_prob = 0.00001, size_t random_seed = 0)
    : _false_prob(false_prob), _random_seed((random_seed) ? random_seed : 0xA5A5A5A5),
    _max_bits_num(4 * size_t(1024 * 1024 * 1024))
    {
        Pval(false_prob);
    }
    BloomFilter(size_t elem_num, double false_prob = 0.00001, size_t random_seed = 0)
    : _elem_num(elem_num), _false_prob(false_prob), _random_seed((random_seed) ? random_seed : 0xA5A5A5A5),
    _max_bits_num(4 * size_t(1024 * 1024 * 1024))
    {
        Pval(elem_num);
        find_optimal_parameters();
        generate_unique_salt();
    }
    void set_max_bits_num(size_t num)
    {
        _max_bits_num = num;
    }
    void add(const std::string& phrase)
    {
        for (int i = 0; i < _hash_num; i++)
        {
            bloom_type pos = hash_ap(reinterpret_cast<const unsigned char*> (phrase.c_str()), phrase.size(), _salt[i]);
            //            Pval(pos);
            pos = pos % _bits_num;
            //            Pval(pos);
            _bits[pos] = 1;
        }
    }
    bool has(const std::string& phrase)
    {
        for (int i = 0; i < _hash_num; i++)
        {
            bloom_type pos = hash_ap(reinterpret_cast<const unsigned char*> (phrase.c_str()), phrase.size(), _salt[i]);
            //            Pval(pos);
            pos = pos % _bits_num;
            //            Pval(pos);
            if (!_bits[pos])
                return false;
        }
        return true;
    }
    int size() const
    {
        return _elem_num;
    }
    void clear()
    {
        _bits.clear();
    }
    void save(const std::string& dir)
    {
        namespace bf = boost::filesystem;
        bf::path path(dir); //如果索引输出路径文件夹未被建立则首先建立，比如update_data/abc,需要首先建立abc文件夹
        if (!bf::exists(path))
        {
            LOG_WARNING("%s not exist, will create first", dir.c_str());
            bf::create_directories(path);
        }
        std::string file = dir + "/bloom.dict";
        std::ofstream ofs(file.c_str());
        Pval(_bits.size());
        boost::to_block_range(_bits, std::ostream_iterator<unsigned char>(ofs)); // this is fine
        ofs.close();
        init(_bits, file);
        Pval(_bits.size());
        file = dir + "/hash.vec";
        write_vec(_salt, file);
    }
    bool load(const std::string& dir)
    {
        std::string file = dir + "/bloom.dict";
        init(_bits, file); //in common_help.h
        file = dir + "/hash.vec";
        read_vec(file, _salt);
        _bits_num = _bits.size();
        _hash_num = _salt.size();
        Pval(_bits_num);
        Pval(_hash_num);
    }
    /**
     * 从明文词典中创建
     * TODO 支持在线创建bloom filter
     */
    bool create(const std::string& file)
    {
        using namespace std;
        { //如果没有外部设置有多少bits
            ifstream ifs(file.c_str());
            if (!ifs.is_open())
            {
                LOG_ERROR("Open %s failed\n", file.c_str());
                return false;
            }
            string line;
            int num = 0;
            while (getline(ifs, line))
            {
                num++;
            }
            _elem_num = num;
            find_optimal_parameters();
            generate_unique_salt();
        }

        std::ifstream ifs(file.c_str());
        if (!ifs.is_open())
        {
            LOG_ERROR("Open %s failed\n", file.c_str());
            return false;
        }

        string line, key;
        while (getline(ifs, line))
        {
            int pos = line.find("\t");
            if (pos == string::npos)
            {
                key = line;
            }
            else
            {
                key = line.substr(0, pos);
            }
            add(key);
        }
    }
private:
    void generate_unique_salt()
    {
        /*
          Note:
          A distinct hash function need not be implementation-wise
          distinct. In the current implementation "seeding" a common
          hash function with different values seems to be adequate.
         */
        const unsigned int predef__saltcount = 128;
        static const bloom_type predef_salt[predef__saltcount] = {
            0xAAAAAAAA, 0x55555555, 0x33333333, 0xCCCCCCCC,
            0x66666666, 0x99999999, 0xB5B5B5B5, 0x4B4B4B4B,
            0xAA55AA55, 0x55335533, 0x33CC33CC, 0xCC66CC66,
            0x66996699, 0x99B599B5, 0xB54BB54B, 0x4BAA4BAA,
            0xAA33AA33, 0x55CC55CC, 0x33663366, 0xCC99CC99,
            0x66B566B5, 0x994B994B, 0xB5AAB5AA, 0xAAAAAA33,
            0x555555CC, 0x33333366, 0xCCCCCC99, 0x666666B5,
            0x9999994B, 0xB5B5B5AA, 0xFFFFFFFF, 0xFFFF0000,
            0xB823D5EB, 0xC1191CDF, 0xF623AEB3, 0xDB58499F,
            0xC8D42E70, 0xB173F616, 0xA91A5967, 0xDA427D63,
            0xB1E8A2EA, 0xF6C0D155, 0x4909FEA3, 0xA68CC6A7,
            0xC395E782, 0xA26057EB, 0x0CD5DA28, 0x467C5492,
            0xF15E6982, 0x61C6FAD3, 0x9615E352, 0x6E9E355A,
            0x689B563E, 0x0C9831A8, 0x6753C18B, 0xA622689B,
            0x8CA63C47, 0x42CC2884, 0x8E89919B, 0x6EDBD7D3,
            0x15B6796C, 0x1D6FDFE4, 0x63FF9092, 0xE7401432,
            0xEFFE9412, 0xAEAEDF79, 0x9F245A31, 0x83C136FC,
            0xC3DA4A8C, 0xA5112C8C, 0x5271F491, 0x9A948DAB,
            0xCEE59A8D, 0xB5F525AB, 0x59D13217, 0x24E7C331,
            0x697C2103, 0x84B0A460, 0x86156DA9, 0xAEF2AC68,
            0x23243DA5, 0x3F649643, 0x5FA495A8, 0x67710DF8,
            0x9A6C499E, 0xDCFB0227, 0x46A43433, 0x1832B07A,
            0xC46AFF3C, 0xB9C8FFF0, 0xC9500467, 0x34431BDF,
            0xB652432B, 0xE367F12B, 0x427F4C1B, 0x224C006E,
            0x2E7E5A89, 0x96F99AA5, 0x0BEB452A, 0x2FD87C39,
            0x74B2E1FB, 0x222EFD24, 0xF357F60C, 0x440FCB1E,
            0x8BBE030F, 0x6704DC29, 0x1144D12F, 0x948B1355,
            0x6D8FD7E9, 0x1C11A014, 0xADD1592F, 0xFB3C712E,
            0xFC77642F, 0xF9C4CE8C, 0x31312FB9, 0x08B0DD79,
            0x318FA6E7, 0xC040D23D, 0xC0589AA7, 0x0CA5C075,
            0xF874B172, 0x0CF914D5, 0x784D3280, 0x4E8CFEBC,
            0xC569F575, 0xCDB2A091, 0x2CC016B4, 0x5C5F4421
        };

        if (_hash_num <= predef__saltcount)
        {
            std::copy(predef_salt,
                    predef_salt + _hash_num,
                    std::back_inserter(_salt));
            for (unsigned int i = 0; i < _salt.size(); ++i)
            {
                /*
                  Note:
                  This is done to integrate the user defined random seed,
                  so as to allow for the generation of unique bloom filter
                  instances.
                 */
                _salt[i] = _salt[i] * _salt[(i + 3) % _salt.size()] + _random_seed;
            }
        }
        else
        {
            std::copy(predef_salt, predef_salt + predef__saltcount, std::back_inserter(_salt));
            srand(static_cast<unsigned int> (_random_seed));
            while (_salt.size() < _hash_num)
            {
                bloom_type current_salt = static_cast<bloom_type> (rand()) * static_cast<bloom_type> (rand());
                if (0 == current_salt) continue;
                if (_salt.end() == std::find(_salt.begin(), _salt.end(), current_salt))
                {
                    _salt.push_back(current_salt);
                }
            }
        }
    }
    void find_optimal_parameters()
    {
        /*
          Note:
          The following will attempt to find the number of hash functions
          and minimum amount of storage bits required to construct a bloom
          filter consistent with the user defined false positive probability
          and estimated element insertion count.
         */

        double min_m = std::numeric_limits<double>::infinity();
        double min_k = 0.0;
        double curr_m = 0.0;
        double k = 1.0;
        while (k < 1000.0)
        {
            double numerator = (-k * _elem_num);
            double denominator = std::log(1.0 - std::pow(_false_prob, 1.0 / k));
            curr_m = numerator / denominator;

            if (curr_m < min_m)
            {
                min_m = curr_m;
                min_k = k;
            }
            k += 1.0;
        }

        _hash_num = static_cast<std::size_t> (min_k);
        Pval(_elem_num);
        Pval(_hash_num);
        _bits_num = static_cast<std::size_t> (min_m);
        if (_max_bits_num / _bits_num < 2)
            _bits_num = _max_bits_num;
        else
            _bits_num *= 2;
        Pval(_bits_num);
        _bits_num += (8 - _bits_num % 8); //凑成8的倍数
        Pval(_bits_num);
        Pval(_bits_num / _elem_num);
        _bits.resize(_bits_num, 0);
    }
    inline bloom_type hash_ap(const unsigned char* begin, std::size_t remaining_length, bloom_type hash) const
    {
        const unsigned char* itr = begin;

        while (remaining_length >= 4)
        {
            hash ^= (hash << 7) ^ (*itr++) * (hash >> 3);
            hash ^= (~((hash << 11) + ((*itr++) ^ (hash >> 5))));
            hash ^= (hash << 7) ^ (*itr++) * (hash >> 3);
            hash ^= (~((hash << 11) + ((*itr++) ^ (hash >> 5))));
            remaining_length -= 4;
        }

        while (remaining_length >= 2)
        {
            hash ^= (hash << 7) ^ (*itr++) * (hash >> 3);
            hash ^= (~((hash << 11) + ((*itr++) ^ (hash >> 5))));
            remaining_length -= 2;
        }

        if (remaining_length)
        {
            hash ^= (hash << 7) ^ (*itr) * (hash >> 3);
        }

        return hash;
    }
public:
    boost::dynamic_bitset<unsigned char> _bits;
    size_t _bits_num;
    int _hash_num;
    size_t _elem_num;
    double _false_prob;
    size_t _random_seed;
    std::vector<bloom_type> _salt;
    //    static const size_t MaxBitsNum = 4 * size_t(1024 * 1024 * 1024);
    size_t _max_bits_num;
};

#endif  //----end of BLOOM_FILTER_H_
