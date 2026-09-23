// LeetCode 20. Valid Parentheses (Easy)
// https://leetcode.com/problems/valid-parentheses/
// Submitted 2025-02-12 06:48 UTC · runtime 2 ms · memory 41.9 MB · submission 1540183080

class Solution {
    public boolean isValid(String s) {

        // list of our parentheses
        ArrayList<Character> parens = new ArrayList<>();

        for (int i = 0; i < s.length(); i++) {
            // current char
            char c = s.charAt(i);

            // check for opening parentheses
            // if equal to one of them add it to list and continue
            if (c == '(' || c == '{' || c == '[') {
                parens.add(c);
                continue;
            }

            // check if one of closing parentheses
            // if equal to one of them check if the
            // most recent opening parentheses in the list
            // is the one that correlates to the closing one
            // if not return false as the parentheses are no long valid
            // else remove the latest opening parentheses that 
            // correlated to the closing one and continue
            if (c == ')') {
                if (parens.size() == 0) { return false; }
                if (parens.get(parens.size()-1) != '(') {
                    return false;
                }
                parens.remove(parens.size()-1);
            } else if (c == '}') {
                if (parens.size() == 0) { return false; }
                if (parens.get(parens.size()-1) != '{') {
                    return false;
                }
                parens.remove(parens.size()-1);
            } else if (c == ']') {
                if (parens.size() == 0) { return false; }
                if (parens.get(parens.size()-1) != '[') {
                    return false;
                }
                parens.remove(parens.size()-1);
            }
        }

        // if no remaining open parenthesis
        // and nothing wrong was found in the loop
        // the parentheses are valid
        return parens.size() == 0;
    }
}
