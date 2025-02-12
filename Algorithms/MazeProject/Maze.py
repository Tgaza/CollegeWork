import networkx as nx
import copy

#import matplotlib.pyplot as plt


class Maze:
    rows = 0
    cols = 0
    baseGraph = nx.DiGraph()
    startingNode = (0, 0)
    endNode = (0, 0)
    growNodes = []
    shrinkNodes = []
    recursionDepth = 0

    def __init__(self, baseData):
        self.baseGraph = baseData[0]
        self.rows = baseData[1]
        self.cols = baseData[2]
        self.startingNode = baseData[3]
        self.endNode = baseData[4]

    def buildFullGraph(self):
        #print("buildingGraph")
        nodesToDelete = []
        for node in self.baseGraph.nodes.data():
            if (len(node[1]) == 0):
                nodesToDelete.append(node[0])
            elif node[1]["type"] == "I":
                self.growNodes.append(node)
            elif node[1]["type"] == "D":
                self.shrinkNodes.append(node)
        for nodeToDelete in nodesToDelete:
            self.baseGraph.remove_node(nodeToDelete)
        # self.__growGraph()
        for growNode in self.growNodes:
            self.__growGraph(growNode)

    # def __growGraph(self):
    #     weightedEdges = []
    #     newNodes = []
    #     baseGraphData = copy.deepcopy(self.baseGraph.nodes.data())
    #     for stepSize in range(1, max(self.rows, self.cols)):
    #         for node in baseGraphData:
    #             x = node[0][0]
    #             y = node[0][1]
    #             if (node[1]['type'] == 'I'):
    #                 trueStepSize = stepSize + 1
    #             elif (node[1]['type'] == 'D'):
    #                 trueStepSize = stepSize - 1
    #             else:
    #                 trueStepSize = stepSize
    #             #print(stepSize)
    #             for direction in node[1]['directions']:
    #                 if direction == "N":
    #                     newNode = (x - trueStepSize, y, trueStepSize)
    #                 elif direction == "NE":
    #                     newNode = (x - trueStepSize, y + trueStepSize, trueStepSize)
    #                 elif direction == "E":
    #                     newNode = (x, y + trueStepSize, trueStepSize)
    #                 elif direction == "SE":
    #                     newNode = (x + trueStepSize, y + trueStepSize, trueStepSize)
    #                 elif direction == "S":
    #                     newNode = (x + trueStepSize, y, trueStepSize)
    #                 elif direction == "SW":
    #                     newNode = (x + trueStepSize, y - trueStepSize, trueStepSize)
    #                 elif direction == "W":
    #                     newNode = (x, y - trueStepSize, trueStepSize)
    #                 elif direction == "NW":
    #                     newNode = (x - trueStepSize, y - trueStepSize, trueStepSize)
    #                 else:
    #                     continue
    #                 if (newNode[0] > self.rows or newNode[1] > self.cols or newNode[0] < 1 or newNode[1] < 1 or trueStepSize < 1
    #                         or trueStepSize > max(self.rows, self.cols)):
    #                     #print("returning at 66 - " + str(node) + " - " + str(newNode) + " - " + str(self.baseGraph.edges.__contains__((node[0], newNode))))
    #                     continue
    #                 else:
    #                     self.baseGraph.add_node((node[0][0], node[0][1], stepSize), directions=node[1]['directions'], type=node[1]['type'])
    #                     self.baseGraph.add_node(newNode,
    #                                             directions=self.baseGraph.nodes[(newNode[0], newNode[1], 1)]['directions'],
    #                                             type=self.baseGraph.nodes[(newNode[0], newNode[1], 1)]['type'])
    #                     self.baseGraph.add_edge((node[0][0], node[0][1], stepSize), newNode, weight=newNode[2])

    def __growGraph(self, growNode):
        self.recursionDepth += 1
        print('recursion depth' + str(self.recursionDepth))
        if ((growNode[0][0], growNode[0][1]) == self.endNode):
            #print("returning at 37 - " + str(growNode))
            return
        weightedEdges = []
        newNodes = []
        x = growNode[0][0]
        y = growNode[0][1]
        if (growNode[1]['type'] == 'I'):
            stepSize = growNode[0][2] + 1
        elif (growNode[1]['type'] == 'D'):
            stepSize = growNode[0][2] - 1
        else:
            stepSize = growNode[0][2]
        for direction in growNode[1]['directions']:
            if direction == "N":
                newNode = (x - stepSize, y, stepSize)
            elif direction == "NE":
                newNode = (x - stepSize, y + stepSize, stepSize)
            elif direction == "E":
                newNode = (x, y + stepSize, stepSize)
            elif direction == "SE":
                newNode = (x + stepSize, y + stepSize, stepSize)
            elif direction == "S":
                newNode = (x + stepSize, y, stepSize)
            elif direction == "SW":
                newNode = (x + stepSize, y - stepSize, stepSize)
            elif direction == "W":
                newNode = (x, y - stepSize, stepSize)
            elif direction == "NW":
                newNode = (x - stepSize, y - stepSize, stepSize)
            else:
                continue
            if (newNode[0] > self.rows or newNode[1] > self.cols or newNode[0] < 1 or newNode[1] < 1 or self.baseGraph.edges.__contains__((growNode[0], newNode))
                    or stepSize < 1 or not self.baseGraph.nodes.__contains__((newNode[0], newNode[1], 1))):
                #print("returning at 66 - " + str(growNode) + " - " + str(newNode) + " - " + str(self.baseGraph.edges.__contains__((growNode[0], newNode))))
                continue
            else:
                self.baseGraph.add_node(newNode,
                                        directions=self.baseGraph.nodes[(newNode[0], newNode[1], 1)]['directions'],
                                        type=self.baseGraph.nodes[(newNode[0], newNode[1], 1)]['type'])
                self.baseGraph.add_edge(growNode[0], newNode, weight=newNode[2])
                self.__growGraph((newNode, self.baseGraph.nodes[newNode]))

    def getStartingNode(self):
        return self.startingNode

    def getEndNode(self):
        return self.endNode

    # def displayGraph(self):
    #     # for coords, attributes in self.baseGraph.nodes.data():
    #     #     print("coords - " + str(coords) + " - ")
    #     #     print("attributes - " + str(attributes))
    #     pos = {(x, y, stepSize): (int(y) + int(self.cols) * (int(stepSize) - 1), -int(x) - (int(stepSize) - 1)) for x, y, stepSize in self.baseGraph.nodes()}
    #     colors = ['red' if attributes['type'] == 'I' else 'blue' if attributes['type'] == 'D' else 'green' for coords, attributes in self.baseGraph.nodes.data()]
    #     fig = plt.figure(1, figsize=(28, 16), dpi=60)
    #     nx.draw_networkx(self.baseGraph, pos=pos, node_color=colors, with_labels=True, node_size=600, font_size=8)
    #     plt.show()

    def findShortestPath(self):
        endNodes = [(self.endNode[0], self.endNode[1], stepSize) for stepSize in range(1, max(self.rows, self.cols))]

        shortestPath = None
        smallestLength = float('inf')

        for endNode in endNodes:
            if endNode in self.baseGraph.nodes():
                try:
                    potentialPath = nx.shortest_path(self.baseGraph, source=(self.startingNode[0], self.startingNode[1], 1), target=endNode, weight='weight')
                    potentialLength = nx.shortest_path_length(self.baseGraph,
                                                              source=(self.startingNode[0], self.startingNode[1], 1),
                                                              target=endNode,
                                                              weight='weight')
                    if potentialLength < smallestLength:
                        smallestLength = potentialLength
                        shortestPath = potentialPath
                except nx.NetworkXNoPath:
                    continue
        if shortestPath == None:
            print("NO PATH")
        else:
            print(str(smallestLength) + " " + str(len(shortestPath)))
            for node in shortestPath:
                print(str(node[0]) + " " + str(node[1]))
