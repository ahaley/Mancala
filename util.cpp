#include "util.h" 

short rand_from_pool()
{
    double rand_zero_one = (static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1));
    return static_cast<short>(rand_zero_one * POOLSIZE);
}

short rand_node(int i)
{
    double rand_zero_one = (static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1));
    return static_cast<short>(rand_zero_one * i);
}

short rand_mancala_function()
{
    double rand_zero_one = (static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1));
    return static_cast<short>(rand_zero_one * NUM_FUNCTION);
}