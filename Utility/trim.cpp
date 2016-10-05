// Trim end / beginning of strings.
using namespace std;
inline string& trim_leading(string& s,
			    const char* t = " \t\n\r\f\v"){
    s.erase(0, s.find_first_not_of(t));return s;}
inline string& trim_trailing(string& s,
			     const char* t = " \t\n\r\f\v"){
    s.erase(s.find_last_not_of(t) + 1);return s;}
inline string& trim(string& s,
		    const char* t = " \t\n\r\f\v"){
    return trim_leading(trim_trailing(s, t), t);}

// Remove adjacent duplicates. "pred" dictates wether two adjacent
// characters should be treated as duplicates of each other.
bool duplicate_pred(const char lhs, const char rhs) {
    return (lhs == rhs) && (lhs == ' ');}
inline void remove_adjacent(string& s){
    auto new_end = unique(s.begin(), s.end(), duplicate_pred);
    s.erase(new_end, s.end());
}
