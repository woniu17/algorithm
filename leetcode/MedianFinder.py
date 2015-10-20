class MedianFinder:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.minHeap = []
        self.maxHeap = []
        

    def addNum(self, num):
        """
        Adds a num into the data structure.
        :type num: int
        :rtype: void
        """
        import heapq
        import sys
        num = num + sys.maxint
        if len(self.minHeap) > len(self.maxHeap):
            if self.minHeap[0] >= num:
                heapq.heappush(self.maxHeap, -num)
            else:
                a = self.minHeap[0]
                heapq.heapreplace(self.minHeap, num)
                heapq.heappush(self.maxHeap, -a)
        elif len(self.minHeap) < len(self.maxHeap):
            if -self.maxHeap[0] <= num:
                heapq.heappush(self.minHeap, num)
            else:
                a = -self.maxHeap[0]
                heapq.heapreplace(self.maxHeap, -num)
                heapq.heappush(self.minHeap, a)
        else:
            if (len(self.minHeap) == 0) and  (len(self.maxHeap) == 0):
                heapq.heappush(self.minHeap, num)
                return
            a = self.minHeap[0]
            b = -self.maxHeap[0]
            if num >= b and num <= a:
                heapq.heappush(self.minHeap, num)
            elif num < b:
                heapq.heapreplace(self.maxHeap, -num)
                heapq.heappush(self.minHeap, b)
            else: #num > a
                heapq.heapreplace(self.minHeap, num)
                heapq.heappush(self.maxHeap, -a)
        #print 'minHeap:', self.minHeap
        #print 'maxHeap:', self.maxHeap
        

    def findMedian(self):
        """
        Returns the median of current data stream
        :rtype: float
        """
        import heapq
        import sys
        if (len(self.minHeap) == 0) and  (len(self.maxHeap) == 0):
            return None
        if len(self.minHeap) > len(self.maxHeap):
            return (self.minHeap[0] - sys.maxint) * 1.0
        elif len(self.minHeap) < len(self.maxHeap):
            return (-self.maxHeap[0] - sys.maxint) * 1.0
        else:
            a = self.minHeap[0] - sys.maxint
            b = - self.maxHeap[0] - sys.maxint
            return (a+b) / 2.0
        

# Your MedianFinder object will be instantiated and called as such:
mf = MedianFinder()
mf.addNum(-1)
print mf.findMedian()
mf.addNum(-2)
print mf.findMedian()
mf.addNum(-3)
print mf.findMedian()
mf.addNum(-4)
print mf.findMedian()
mf.addNum(-5)
print mf.findMedian()
import sys
#print 'maxint:', (sys.maxint + 1)
