import networkx as nx


class Maze:
    rows = 0
    cols = 0
    baseGraph = nx.Graph()
    startingNode = (0, 0)
    endNode = (0, 0)
    growNodes = []
    shrinkNodes = []

    def __init__(self, baseData):
        self.baseGraph = baseData[0]
        self.rows = baseData[1]
        self.cols = baseData[2]
        self.startingNode = baseData[3]
        self.endNode = baseData[4]

    def buildFullGraph(self):
        print("buildingGraph")
        for node in self.baseGraph.nodes.data():
            if node[1]["type"] == "I":
                self.growNodes.append(node)
            elif node[1]["type"] == "D":
                self.shrinkNodes.append(node)

    def getStartingNode(self):
        return self.startingNode

    def getEndNode(self):
        return self.endNode
