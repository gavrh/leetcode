// LeetCode 20. Valid Parentheses (Easy)
// https://leetcode.com/problems/valid-parentheses/
// Submitted 2026-09-27 07:21 UTC · runtime 0 ms · memory 8.9 MB · submission 2154728009

class Solution {
public:
    static constexpr char ROUND_OPEN = '(';
    static constexpr char ROUND_CLOSE = ')';
    static constexpr char SQUARE_OPEN = '[';
    static constexpr char SQUARE_CLOSE = ']';
    static constexpr char BRACE_OPEN = '{';
    static constexpr char BRACE_CLOSE = '}';
    bool isValid(string s) {
        std::stack<char> paren;

        for (size_t  i {}; i < s.length(); i++) {
            switch (s[i]) {
                case ROUND_OPEN:
                    paren.push(s[i]);
                    break;
                case SQUARE_OPEN:
                    paren.push(s[i]);
                    break;
                case BRACE_OPEN:
                    paren.push(s[i]);
                    break;

                case ROUND_CLOSE:
                    if (paren.size() != 0 && paren.top() == ROUND_OPEN) {
                        paren.pop(); 
                        break;
                    } else return false;
                case SQUARE_CLOSE:
                    if (paren.size() != 0 && paren.top() == SQUARE_OPEN) {
                        paren.pop(); 
                        break;
                    } else return false;
                case BRACE_CLOSE:
                    if (paren.size() != 0 && paren.top() == BRACE_OPEN) {
                        paren.pop(); 
                        break;
                    } else return false;
            }
        }

        return paren.size() == 0;
    }
};
