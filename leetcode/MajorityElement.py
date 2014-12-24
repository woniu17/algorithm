# Runtime:O(n)--Moore voting algorithm
class Solution:
	# @param num, alist of integers
	# @return an integer
	def majorityElement(self, num):
		
		qingluck = 0
		count = 0
		for n in num:
			if count <= 0:
				qingluck = n

			if qingluck == n:
				count = count + 1
			else:
				count = count - 1
		return qingluck

if __name__ == '__main__':
	solution = Solution()
	num = [1,2,1,1,4,6,1]
	qingluck = solution.majorityElement(num)
	print 'result: %d'%qingluck
