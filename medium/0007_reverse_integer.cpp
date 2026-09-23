// LeetCode 7. Reverse Integer (Medium)
// https://leetcode.com/problems/reverse-integer/
// Submitted 2025-02-10 18:49 UTC · runtime 0 ms · memory 8.9 MB · submission 1538462022

class Solution {
public:
    int reverse(int x) {
        bool neg = false;
        if (x < 0) {
            neg = true;
            x = std::abs((long long) x);
        }
        if (x > 2147483647 || x < -2147483647) {
            return 0;
        }

        int res = 0;
        while (true) {
            int rem = x % 10;
            try {
                if (res > std::numeric_limits<int>::max() / 10 || 
                    (res == std::numeric_limits<int>::max() / 10 && rem > std::numeric_limits<int>::max() % 10)) {
                    throw std::overflow_error("Overflow detected");
                }
                res = res * 10 + rem;
            } catch (std::overflow_error& e) {
                return 0;
            }
            x = (x - rem) / 10;
            if (x == 0) {
                break;
            }
        }

        return neg ? res*-1 : res;
    }
};
