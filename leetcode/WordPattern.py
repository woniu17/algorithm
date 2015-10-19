class Solution(object):
    def wordPattern(self, pattern, str):
        words = str.split()
        if len(pattern) != len(words):
            return False
        ptDict, wordDict = {}, {}
        for pt, word in zip(pattern, words):
            if pt not in ptDict:
                ptDict[pt] = word
            if word not in wordDict:
                wordDict[word] = pt
            if ptDict[pt] != word or wordDict[word] != pt: 
                return False
        return True

if __name__ == '__main__':
    print 'hello, leetcode!'
    import sys
    i = 0
    str = None
    pattern = None
    sol = Solution()
    for s in sys.stdin:
        i = i + 1
        if i%2 == 0:
            str = s[:-1]
            res = sol.wordPattern(pattern, str)
            print 'res:', res
        else:
            pattern = s[:-1]
