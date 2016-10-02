// Trim end / beginning of strings.
inline std::string& trim_leading(std::string& s, const char* t = " \t\n\r\f\v"){s.erase(0, s.find_first_not_of(t));return s;}
inline std::string& trim_trailing(std::string& s, const char* t = " \t\n\r\f\v"){s.erase(s.find_last_not_of(t) + 1);return s;}
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v"){return trim_leading(trim_trailing(s, t), t);}

// Remove adjacent duplicates. "pred" dictates wether two adjacent characters should be treated as duplicates of each other.
bool duplicate_pred(const char lhs, const char rhs) {return (lhs == rhs) && (lhs == ' ');}
inline std::string& remove_adjacent(string& s){
    std::string::iterator new_end = std::unique(s.begin(), s.end(), duplicate_pred);
    s.erase(new_end, s.end());
}
