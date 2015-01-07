# Definition for a  binary tree node
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class BSTIterator:
    # @param root, a binary search tree's root node
    def __init__(self, root):
        self.qingluck = []
        self.sort(root)
        self.index = 0
        self.length = len(self.qingluck)
        #print 'index = %d'%self.index
        #print 'length = %d'%self.length

    def sort(self, root):
        if root == None:
            return
        #6print 'root = %d'%root.val
        self.sort(root.left)
        self.qingluck.append(root.val)
        self.sort(root.right)
        
    # @return a boolean, whether we have a next smallest number
    def hasNext(self):
        #print 'index = %d'%self.index
        #print 'length = %d'%self.length
        return (self.index < self.length)

    # @return an integer, the next smallest number
    def next(self):
        if self.index >= self.length:
            return None
        i = self.index
        self.index = i + 1
        #print 'qingluck = %d'%self.qingluck[i]
        return self.qingluck[i]

# Your BSTIterator will be called like this:
# i, v = BSTIterator(root), []
# while i.hasNext(): v.append(i.next())

#Definition for a  binary tree node
class TreeNode:
     def __init__(self, x):
         self.val = x
         self.left = None
         self.right = None

if __name__ == '__main__':
    root = TreeNode(1)
    i, v = BSTIterator(root), []
    while i.hasNext():
        #print 'hasNext'
        v.append(i.next())
    for i in xrange(len(v)):
        print '%d-->%d'%(i,v[i])
