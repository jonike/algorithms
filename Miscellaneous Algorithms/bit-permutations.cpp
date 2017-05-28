// Given a mask, this will generate the next permutation with same amount of bits set. For example, 0011 => 0101 => 0110, etc.
uint64_t BitPermute( uint64_t nBitPermutation )
{
    uint64_t nAnswer = ( nBitPermutation | ( nBitPermutation - 1 ) ) + 1;
    return nAnswer | ( ( ( ( nAnswer & -nAnswer ) / ( nBitPermutation & -nBitPermutation ) ) >> 1 ) - 1 );
}
