"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const addTwoNumbers_1 = __importDefault(require("./addTwoNumbers"));
const longestPalindromicSubstring_1 = __importDefault(require("./longestPalindromicSubstring"));
const problem = process.argv.slice(2)[0].toLowerCase();
switch (problem) {
    case "addtwonumbers":
        (0, addTwoNumbers_1.default)();
        break;
    case "longestpalindromicsubstring":
        (0, longestPalindromicSubstring_1.default)();
        break;
}
