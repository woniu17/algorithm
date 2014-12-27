class Solution:
    # @param A, a list of integer
    # @return an integer
    def singleNumber(self, A):
        qingluck = 0
        for a in A:
            qingluck = qingluck^a
        return qingluck

if __name__ == '__main__':
    A = [1,1,2,3,4,5,4,3,2]
    solution = Solution()
    qingluck = solution.singleNumber(A)
    print 'result: %s'%qingluck
