/** @file editdistance.h
 * @brief Edit distance calculation algorithm.
 */
/* Copyright (C) 2003 Richard Boulton
 * Copyright (C) 2007,2008 Olly Betts
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef XAPIAN_INCLUDED_EDITDISTANCE_H
#define XAPIAN_INCLUDED_EDITDISTANCE_H

/** Calculate the edit distance between two sequences.
 *
 *  Edit distance is defined as the minimum number of edit operations
 *  required to move from one sequence to another.  The edit operations
 *  considered are:
 *   - Insertion of a character at an arbitrary position.
 *   - Deletion of a character at an arbitrary position.
 *   - Substitution of a character at an arbitrary position.
 *   - Transposition of two neighbouring characters at an arbitrary position
 *     in the string.
 *
 *  @param ptr1 A pointer to the start of the first sequence.
 *  @param len1 The length of the first sequence.
 *  @param ptr2 A pointer to the start of the second sequence.
 *  @param len2 The length of the first sequence.
 *  @param max_distance The greatest edit distance that's interesting to us.
 *			If the true edit distance is > max_distance, any
 *			value > max_distance may be returned instead (which
 *			allows the edit distance algorithm to avoid work for
 *			poor matces).
 *
 *  @return The edit distance from one item to the other.
 */


#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;
template<class CHR>
struct edist_seq
{
    edist_seq(const CHR * ptr_, int len_) : ptr(ptr_), len(len_)
    {
    }
    const CHR * ptr;
    int len;
};
template<class CHR>
class edist_state
{
    /// Don't allow assignment.
    void operator=(const edist_state &);

    /// Don't allow copying.
    edist_state(const edist_state &);

    edist_seq<CHR> seq1;
    edist_seq<CHR> seq2;

    /* Array of f(k,p) values, where f(k,p) = the largest index i such that
     * d(i,j) = p and d(i,j) is on diagonal k.
     * ie: f(k,p) = largest i s.t. d(i,k+i) = p
     * Where: d(i,j) = edit distance between substrings of length i and j.
     */
    int * fkp;
    int fkp_cols;

    /* Maximum possible edit distance (this is referred to as ZERO_K in
     * the algorithm description by Berghel and Roach). */
    int maxdist;
    int calc_index(int k, int p) const
    {
        return (k + maxdist) * fkp_cols + p + 1;
    }

public:

    edist_state(const CHR * ptr1, int len1, const CHR * ptr2, int len2);

    ~edist_state();
    int get_f_kp(int k, int p) const
    {
        return fkp[calc_index(k, p)];
    }
    void set_f_kp(int k, int p, int val)
    {
        fkp[calc_index(k, p)] = val;
    }
    bool is_transposed(int pos1, int pos2) const
    {
        if (pos1 <= 0 || pos2 <= 0 || pos1 >= seq1.len || pos2 >= seq2.len) return false;
        return (seq1.ptr[pos1 - 1] == seq2.ptr[pos2] &&
                seq1.ptr[pos1] == seq2.ptr[pos2 - 1]);
    }

    void edist_calc_f_kp(int k, int p);
};
template<class CHR>
void edist_state<CHR>::edist_calc_f_kp(int k, int p)
{
    int maxlen = get_f_kp(k, p - 1) + 1; /* dist if do substitute */
    int maxlen2 = get_f_kp(k - 1, p - 1); /* dist if do insert */
    int maxlen3 = get_f_kp(k + 1, p - 1) + 1; /* dist if delete */

    if (is_transposed(maxlen, maxlen + k))
    {
        // Transposition.
        ++maxlen;
    }

    if (maxlen >= maxlen2)
    {
        if (maxlen >= maxlen3)
        {
            // Transposition or Substitution.
        }
        else
        {
            // Deletion.
            maxlen = maxlen3;
        }
    }
    else
    {
        if (maxlen2 >= maxlen3)
        {
            // Insertion.
            maxlen = maxlen2;
        }
        else
        {
            // Deletion.
            maxlen = maxlen3;
        }
    }

    /* Check for exact matches, and increase the length until we don't have
     * one. */
    while (maxlen < seq1.len &&
            maxlen + k < seq2.len &&
            seq1.ptr[maxlen] == seq2.ptr[maxlen + k])
    {
        ++maxlen;
    }
    set_f_kp(k, p, maxlen);
}

#define INF 1000000
template<class CHR>
edist_state<CHR>::edist_state(const CHR * ptr1, int len1,
                              const CHR * ptr2, int len2)
: seq1(ptr1, len1), seq2(ptr2, len2), maxdist(len2)
{
    //Assert(len2 >= len1);
    /* Each row represents a value of k, from -maxdist to maxdist. */
    int fkp_rows = maxdist * 2 + 1;
    /* Each column represents a value of p, from -1 to maxdist. */
    fkp_cols = maxdist + 2;
    /* fkp is stored as a rectangular array, row by row. */
    fkp = new int[fkp_rows * fkp_cols];

    for (int k = -maxdist; k <= maxdist; k++)
    {
        for (int p = -1; p <= maxdist; p++)
        {
            if (p == abs(k) - 1)
            {
                if (k < 0)
                {
                    set_f_kp(k, p, abs(k) - 1);
                }
                else
                {
                    set_f_kp(k, p, -1);
                }
            }
            else if (p < abs(k))
            {
                set_f_kp(k, p, -INF);
            }
        }
    }
}
template<class CHR>
edist_state<CHR>::~edist_state()
{
    delete [] fkp;
}
template<class CHR>
static int
seqcmp_editdist(const CHR * ptr1, int len1, const CHR * ptr2, int len2,
                int max_distance)
{
    int lendiff = len2 - len1;
    /* Make sure second sequence is longer (or same length). */
    if (lendiff < 0)
    {
        lendiff = -lendiff;
        swap(ptr1, ptr2);
        swap(len1, len2);
    }

    /* Special case for if one or both sequences are empty. */
    if (len1 == 0) return len2;

    edist_state<CHR> state(ptr1, len1, ptr2, len2);

    int p = lendiff; /* This is the minimum possible edit distance. */
    while (p <= max_distance)
    {
        for (int temp_p = 0; temp_p != p; ++temp_p)
        {
            int inc = p - temp_p;
            if (abs(lendiff - inc) <= temp_p)
            {
                state.edist_calc_f_kp(lendiff - inc, temp_p);
            }
            if (abs(lendiff + inc) <= temp_p)
            {
                state.edist_calc_f_kp(lendiff + inc, temp_p);
            }
        }
        state.edist_calc_f_kp(lendiff, p);

        if (state.get_f_kp(lendiff, p) == len1) break;
        ++p;
    }

    return p;
}

inline int edit_distance_unsigned(const unsigned * ptr1, int len1,
                                  const unsigned * ptr2, int len2,
                                  int max_distance)
{
    return seqcmp_editdist<unsigned>(ptr1, len1, ptr2, len2, max_distance);
}
inline int edit_distance(const char * ptr1, int len1,
                         const char * ptr2, int len2,
                         int max_distance)
{
    return seqcmp_editdist<char>(ptr1, len1, ptr2, len2, max_distance);
}

///gbk格式的汉字串编辑距离的计算  FIXME 数字汉字混合情况怎么处理
inline int edit_distance_ch(const char * ptr1, int len1,
                            const char * ptr2, int len2,
                            int max_distance)
{
    return seqcmp_editdist<unsigned short>((unsigned short *) ptr1, len1,
            (unsigned short *) ptr2, len2, max_distance);
}


//gbk格式中文字符串编辑距离,用户确保全中文!
inline int edit_distance_ch(const std::string& s1, const std::string& s2, int max_diff)
{
    return edit_distance_ch(s1.c_str(), s1.size() / 2, s2.c_str(), s2.size() / 2, max_diff);
}
#endif // XAPIAN_INCLUDED_EDITDISTANCE_H
