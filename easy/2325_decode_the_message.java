// LeetCode 2325. Decode the Message (Easy)
// https://leetcode.com/problems/decode-the-message/
// Submitted 2025-04-01 00:30 UTC · runtime 6 · memory 42580000 · submission 1592542843

class Solution {
    public String decodeMessage(String key, String message) {
        int count = 0;
        HashMap<Character, Integer> map = new HashMap<>();
        for (char c : key.toCharArray()) {
            if (!map.containsKey(c) && c != ' ') {
                map.put(c, count++);
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < message.length(); i++) {
            char curr = message.charAt(i);
            if (curr != ' ') {
                curr = (char) ((int) map.get(curr) + 97);
            }
            sb.append(curr);
        }
        
        return sb.toString();
    }
}
