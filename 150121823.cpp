#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

void fread(std::vector<int>&);

int
main()
{
    std::vector<int> seed;
    fread(seed);
    std::sort(std::begin(seed), std::end(seed));
    return 0;
}

void
fread(std::vector<int>& seed)
{
    std::ifstream fin("input.txt");
    std::istream_iterator<int> in(fin);
    std::copy(in, std::istream_iterator<int>(), std::back_inserter(seed));
    return;
}
