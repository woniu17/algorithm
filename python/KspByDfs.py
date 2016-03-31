import sys
import re

class KspByDfs:
    def __init__(self, graph = None):
        self.graph = graph
        self.visit = None
        self.paths = None
        self.pathVals = None

    def dfs(self, source, sink, path):
        #
	print path
        if len(path) > 5:
            return
        for i in xrange(len(self.visit)):
            if self.visit[i] or  i == source:
                continue
            #there is no edge from path[-1] to i
            if self.graph[path[-1]][i] > sys.maxint - 10:
                continue
            if i != sink:
                self.visit[i] = True
                self.dfs(source, sink, path + [i,])
                self.visit[i] = False
                continue
            # i == sink
            path = path + [i,]
            pathVal = 0
            for j in xrange(len(path) - 1):
                u = path[j]
                v = path[j+1]
                pathVal += self.graph[u][v]
            for k in xrange(len(self.pathVals)):
                if 0 > self.pathVals[k]:
                    self.pathVals[k] = pathVal
                    self.paths[k] = path
                    break
                if pathVal < self.pathVals[k]:
                    tmpVal = self.pathVals[k]
                    tmpPath = self.paths[k]
                    self.pathVals[k] = pathVal
                    self.paths[k] = path
                    pathVal = tmpVal
                    path = tmpPath
            path = path[0:-1]

    def printPaths(self,):
         pathNum = len(self.paths)
         flag = [False] * pathNum
         for i in xrange(pathNum):
             val = -1
             k = -1
             for j in xrange(pathNum):
                 if 0 < self.pathVals[j] and not flag[k] and (0 > k or val > self.pathVals[j]):
                     k = j
                     val = self.pathVals[j]
             flag[k] = True
             print self.paths[i], self.pathVals[i]
             #print self.paths[k], self.pathVals[k]

    def getKsp(self, source, sink, k):
        self.paths = [None] * k
        self.pathVals = [-1] * k
        n = len(self.graph)
        self.visit = [False] * n
        self.visit[source] = True
        self.dfs(source, sink, [source,])

def readGraph(fileName):
    f = open(fileName)
    n = int(f.readline())
    graph = [([float(sys.maxint)] * n) for i in xrange(n)]
    #read blank line
    f.readline()
    for line in f.readlines():
        e = re.split('\s', line)
        u, v, w = int(e[0]), int(e[1]), float(e[2])
        graph[u][v] = w
    return graph
        

if __name__ == "__main__":
    graph = [[1, 1, 1], [1, 1, 1], [1, 1, 1]]
    graph = readGraph('test_5')
    graph = readGraph('test_6_1')
    graph = readGraph('test_6_2')
    graph = readGraph('test_7')
    graph = readGraph('test_8')
    graph = readGraph('test_6')
    graph = readGraph('network')
    graph = readGraph('test_50')
    ksp = KspByDfs(graph)
    ksp.getKsp(0, 1, 5)
    print '---------------------------------------'
    ksp.printPaths()
    for i in xrange(len(graph)):
        for j in xrange(len(graph)):
            if i == j:
                 continue
            #ksp.getKsp(i, j, 5)
            #ksp.printPaths()
            #print '---------------------------------------'
