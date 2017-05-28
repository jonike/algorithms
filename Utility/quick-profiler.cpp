// Idea from here: https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
// Use by { PROFILE_BLOCK("Some message"); [... code you want to profile ...] }

#include <cstring>
#include <chrono>

struct SBlockProfiler
{
    std::string name;
    std::chrono::high_resolution_clock::time_point tp;
    
    SBlockProfiler(std::string const & _name) 
      : name(_name), p(std::chrono::high_resolution_clock::now()) {}
      
    ~SBlockProfiler()
    {
        using d_type = std::chrono::duration<double>;
        auto d = std::chrono::high_resolution_clock::now() - tp;
        auto o = std::chrono::duration_cast<d_type>(d).count();
        std::cout << name << ": " << o << std::endl;
    }
};

#define PROFILE_BLOCK(__p) SBlockProfiler __SBlockProfilerInstance(__p)
