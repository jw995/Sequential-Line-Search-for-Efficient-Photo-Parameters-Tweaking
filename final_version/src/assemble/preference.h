#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <utility>
#include <vector>

// Pair (i, j(, k)) means that the ith data point is the best among i, j(, k)
struct Preference : public std::vector<unsigned>
{
    Preference(unsigned i, unsigned j) : std::vector <unsigned> {i, j} {}
    Preference(unsigned i, unsigned j, unsigned k) : std::vector <unsigned> {i, j, k} {}
    Preference(const std::vector<unsigned>& idx) : std::vector <unsigned> {idx} {}
};

#endif // PREFERENCE_H
