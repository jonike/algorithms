// Relatively effective multiset permutation generator. Not as effective as std::next_permutation though.
// std::next_permutation is about double as fast.
// Looked at https://github.com/ekg/multipermute/blob/master/multipermute.h while implementing this.

#include <vector>
#include <algorithm>

template <class T>
class CList
{
public:	
    T _Value;
    CList<T> * _pNext;
	
    // Constructors and destructors.
    CList() : _pNext(nullptr), _Value() {}
    CList(T Value, CList<T> * pNext) : _pNext(pNext), _Value(Value) {}
    ~CList() { if(_pNext != nullptr) { delete _pNext; } }
	
    // Helpful functions.
    CList<T> * GetAt( int nPosition )
    {
        CList<T> * pResult = this;
        while(nPosition-- > 0 && pResult->_pNext != nullptr)
        {
            pResult = pResult->_pNext;
        }
        return pResult;
    }
    
    std::vector<T> ToVector()
    {
        std::vector<T> Result;
        CList<T> * pIterator = this;
        while( pIterator != nullptr ) 
        {
            Result.push_back( pIterator->_Value );
            pIterator = pIterator->_pNext;
        }
        return Result;
    }
	
    static CList<T> * ToList( const std::vector<T> & Multiset )
    {
        CList<T> * pResult = nullptr;
        for( auto pIterator = Multiset.begin(); pIterator != Multiset.end(); ++pIterator )
        {
            pResult = new CList<T>( *pIterator, pResult );
        }
        return pResult;
    }
};

template <class T>
std::vector< std::vector<T> > GenerateAllMultisetPermutations(std::vector<T>& Multiset) 
{    
    std::vector< std::vector<T> > Results;
    const int nMembers = Multiset.size();

    // Non-increasing order.
    std::sort( Multiset.begin(), Multiset.end() ); 
	
    // Initialize pointers.
    CList<T> * h = CList<T>::ToList( Multiset );
    CList<T> * i = h->GetAt( nMembers - 2 );
    CList<T> * j = (i->_pNext == nullptr) ? i : i->_pNext;
    CList<T> * s, * t;

    Results.push_back( std::move( h->ToVector() ) );

    // Generate all multiset permutations.
    while (j->_pNext != nullptr || j->_Value < h->_Value) 
    {
        s = (j->_pNext != nullptr && i->_Value >= j->_pNext->_Value) ? j : i;
        t = s->_pNext;
        s->_pNext = t->_pNext;
        t->_pNext = h;
        if (t->_Value < h->_Value) { i = t; }
        j = i->_pNext;
        h = t;
        Results.push_back( std::move( h->ToVector() ) );
    }

    delete h;

    return Results;
}
