/* Fast IO */

/* ------- */
#define getch getchar_unlocked
#define putch putchar_unlocked
char buff[16];
inline int get_int(){char ch = getch();while (true){if (ch == '-') break;if (ch >= '0' && ch <= '9') break;ch = getch();}int result = ch - '0';while (true) {ch = getch();if (ch < '0' || ch > '9') break;result = result*10 + (ch - '0');}return result;}
inline int get_int_neg(){char ch = getch();while((ch < '0' || ch > '9') && ch != '-'){ch = getch();}bool neg = (ch == '-');if(neg){ch = getch();}int result = ch - '0';while (true) {ch = getch();if (ch < '0' || ch > '9') break;result = result * 10 + (ch - '0');}return neg ? -result : result;}
inline long get_long(){char ch = getch();while (true){if (ch == '-') break;if (ch >= '0' && ch <= '9') break;ch = getch();}long result = ch - '0';while (true) {ch = getch();if (ch < '0' || ch > '9') break;result = result*10 + (ch - '0');}return result;}
inline long get_long_neg(){char ch = getch();while((ch < '0' || ch > '9') && ch != '-'){ch = getch();}bool neg = (ch == '-');if(neg){ch = getch();}long result = ch - '0';while (true) {ch = getch();if (ch < '0' || ch > '9') break;result = result * 10 + (ch - '0');}return neg ? -result : result;}
inline int get_single_int(){char ch = getch();return ch - '0';}
inline void print_single_char(char c){putch(c);}
inline void print_int(int x){int digits = 0;do{buff[digits++] = (x % 10) + 0x30;x /= 10;} while(x != 0);while(digits > 0){putch(buff[--digits]);}}
inline void print_long(long long x){if(x < 0){putch('-'); x = -x;}int digits = 0;do{buff[digits++] = ((x % 10) + 0x30);x /= 10;}while(x != 0);while(digits > 0){putch(buff[--digits]);}}
inline void print_newline(){putch('\n');}
inline void print_string(const string& s){for(int i = 0; i < s.length(); ++i){print_single_char(s[i]);}}
inline char get_char_special(const vector<char>& allowed_chars){while(true){char ch = getch();for(int i = 0; i < allowed_chars.size(); ++i){if(ch == allowed_chars[i]){return ch;}}}}
/* -------- */
