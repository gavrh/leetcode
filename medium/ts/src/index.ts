import addTwoNumbersTests from './addTwoNumbers';
import longestPalindromicSubstringTests from './longestPalindromicSubstring';

const problem = process.argv.slice(2)[0].toLowerCase();

switch(problem) {
    case "addtwonumbers": addTwoNumbersTests(); break;
    case "longestpalindromicsubstring": longestPalindromicSubstringTests(); break;
}
