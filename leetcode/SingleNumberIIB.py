class Solution:
    # @param A, alist of integer
    # @return an integer
    def singleNumber(self, A):
        qingluck = 0
        for i in xrange(32):
            x = 0
            for a in A:
                x = x+((a>>i)&1)
            x = x%3
            qingluck = qingluck|(x<<i)
        positive = (qingluck>>31)&1
        if positive == 0:
            return qingluck
        #if negative
        qingluck = qingluck^(int('FFFFFFFF',16))
        qingluck = qingluck+1
        qingluck = 0 - qingluck
        return qingluck

if __name__ == '__main__':
    A = [1,3,1,3,1,4,4,3,11,11,4,11,7]
    A = [-2,-2,1,1,-3,1,-3,-3,-4,-2]
    solution = Solution()
    res = solution.singleNumber(A)
    print 'result:%d'%res
    print '-4:%s'%bin(-4)
