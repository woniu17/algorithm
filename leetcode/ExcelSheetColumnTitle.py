class Solution:
	# @return a string
	def convertToTitle(self, num):
		title = ['Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',]
		qingluck = ''
		while num>0:
			tmp = num%26
			if tmp == 0:
				num = num-26
			num = num/26
			qingluck = '%s%s'%(title[tmp], qingluck)
		return qingluck
