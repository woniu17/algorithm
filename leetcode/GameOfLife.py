class Solution(object):
    def gameOfLife(self, board):
        """
        :type board: List[List[int]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        old_status = [0, 0, 1, 1]
        new_status = [0, 1, 0, 1]
        rl = len(board) #row length
        cl = len(board[0]) #column length
        for i in xrange(rl):
            for j in xrange(cl):
                c = 0
                if i > 0 and j > 0:
                    c = c + old_status[board[i-1][j-1]]
                if i > 0:
                    c = c + old_status[board[i-1][j]]
                if i > 0 and j < cl-1:
                    c = c + old_status[board[i-1][j+1]]
                if j > 0:
                    c = c + old_status[board[i][j-1]]

                if j < cl-1:
                    c = c + board[i][j+1]
                if i < rl-1 and j > 0:
                    c = c + board[i+1][j-1]
                if i < rl-1:
                    c = c + board[i+1][j]
                if i < rl-1 and j < cl-1:
                    c = c + board[i+1][j+1]

                #
                if board[i][j] == 1:
                    if c < 2 or c > 3:
                        board[i][j] = 2 # 1 -> 0
                    else: #c == 2 or c == 3
                        board[i][j] = 3 # 1 -> 1
                else:
                    if c == 3:
                        board[i][j] = 1 # 0 -> 1
                    else:
                        board[i][j] = 0 # 0 -> 0
        
        for i in xrange(rl):
            for j in xrange(cl):
                board[i][j] = new_status[board[i][j]]
