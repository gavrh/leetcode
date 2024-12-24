#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

// "/palindrome-number"
bool isPalindrome(int x) {
    if (x < 0) return false;
    
    int64_t a = 0;
    int64_t b = x;

    while (b != 0) {
        a = (a*10) + (b%10);
        b = b/10;
    }

    return (a == x);
};

// "/longest-common-prefix"
string longestCommonPrefix(vector<string>& strs) {

    sort(strs.begin(), strs.end());

    string f = strs.front();
    string l = strs.back();
    int ml = min(f.size(), l.size());

    int i = 0;
    while (i < ml && f[i] == l[i]) {
        i++;
    }

    return f.substr(0, i);
};

int main(int argc, char* argv[]) {

    char* problem = argv[1];
    cout << "https://leetcode.com/problems/" << problem << "\n";

    if (strcmp(problem, "palindrome-number") == 0) {

        cout << "-121: "<< isPalindrome(-121) << "\n";
        cout << "121: " << isPalindrome(121) << "\n";
        cout << "36963: " << isPalindrome(36963) << "\n";
        cout << "369953: " << isPalindrome(369953) << "\n";
        cout << "11133111: " << isPalindrome(11133111) << "\n";
        cout << "1234567899: " << isPalindrome(1234567899) << "\n";

    } else if (strcmp(problem, "longest-common-prefix") == 0) {

        vector<string> t1 = {"flower", "flow", "flight"};
        vector<string> t2 = {"poweranger", "powerful", "powerup", "powersteer"};
        vector<string> t3 = {"smack", "smash", "small", "smart"};
        vector<string> t4 = {"pastel", "pasta", "paste"};
        vector<string> t5 = {"whatever", "what"};
        vector<string> t6 = {""};
        vector<string> t7 = {"", ""};

        cout << "[\"flower\", \"flow\", \"flight\"]: " << longestCommonPrefix(t1) << "\n";
        cout << "[\"powerranger\", \"powerful\", \"powerup\", \"powersteer\"]: " << longestCommonPrefix(t2) << "\n";
        cout << "[\"smack\", \"smash\", \"small\", \"smart\"]: " << longestCommonPrefix(t3) << "\n";
        cout << "[\"pastel\", \"pasta\", \"paste\"]: " << longestCommonPrefix(t4) << "\n";
        cout << "[\"whatever\", \"what\"]: " << longestCommonPrefix(t5) << "\n";
        cout << "[\"\"]: " << longestCommonPrefix(t6) << "\n";
        cout << "[\"\" \"\"]: " << longestCommonPrefix(t7) << "\n";

    }

    return 0;
}
