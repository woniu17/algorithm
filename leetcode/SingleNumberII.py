class Solution:
    # @param A, alist of integer
    # @return an integer
    def singleNumber(self, A):
        one = 0
        two = 0
        three = 0
        for a in A:
            three = two&a
            two = two^(one&a)
            one = one^a

            two = two&(~three)
            one = one&(~two)&(~three)
            three = 0
        qingluck = one
        return qingluck

if __name__ == '__main__':
    A = [1,3,1,3,1,4,4,3,11,11,4,11,7]
    solution = Solution()
    res = solution.singleNumber(A)
    print 'result:%d'%res
