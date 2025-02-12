import networkx as nx
"""_summary_
    Author: Ty Gazaway
    Definition: InputReader is a Class whose purpose is to take in a filename, and then decipher the input data within that file into
    useable data.
"""


class InputReader:
    filename = ""
    dataArray = []

    def __init__(self, filename):
        self.filename = filename

    def readFile(self):
        with open(self.filename) as file:
            for line in file:
                self.dataArray.append(line.strip().split(" "))

    def createBaseGraph(self):
        initialGraph = nx.DiGraph()
        firstLineProcessed = False
        totalRows = 0
        totalCols = 0
        startingNode = (0, 0)
        endNode = (0, 0)
        baseStepSize = 1
        # each row array should be of format [row:int,col:int,::,N:string,E:string..,::,tiletype:char]
        # except the first row which will be [totalRows:int,totalCols:int,::,startRow:int,startCol:int,::,endRow:int,endCol:int]
        for dataRow in self.dataArray:
            if not firstLineProcessed:
                totalRows = int(dataRow[0])
                totalCols = int(dataRow[1])
                startingNode = (int(dataRow[3]), int(dataRow[4]))
                endNode = (int(dataRow[6]), int(dataRow[7]))
                firstLineProcessed = True
            else:
                x = int(dataRow[0])
                y = int(dataRow[1])
                initialGraph.add_node((x, y, baseStepSize))
                initialGraph.nodes[(x, y, baseStepSize)]["directions"] = dataRow[3:-2]
                initialGraph.nodes[(x, y, baseStepSize)]["type"] = dataRow[-1]
                if (initialGraph.nodes[(x, y, baseStepSize)]["type"] != 'I' and initialGraph.nodes[(x, y, baseStepSize)]["type"] != 'D'):
                    weightedEdges = []
                    for direction in initialGraph.nodes[(x, y, baseStepSize)]["directions"]:
                        if direction == "N":
                            connectingNode = (x - baseStepSize, y, baseStepSize)
                        elif direction == "NE":
                            connectingNode = (x - baseStepSize, y + baseStepSize, baseStepSize)
                        elif direction == "E":
                            connectingNode = (x, y + baseStepSize, baseStepSize)
                        elif direction == "SE":
                            connectingNode = (x + baseStepSize, y + baseStepSize, baseStepSize)
                        elif direction == "S":
                            connectingNode = (x + baseStepSize, y, baseStepSize)
                        elif direction == "SW":
                            connectingNode = (x + baseStepSize, y - baseStepSize, baseStepSize)
                        elif direction == "W":
                            connectingNode = (x, y - baseStepSize, baseStepSize)
                        elif direction == "NW":
                            connectingNode = (x - baseStepSize, y - baseStepSize, baseStepSize)
                        else:
                            continue
                        if (connectingNode[0] <= totalRows and connectingNode[1] <= totalCols and connectingNode[0] >= 1 and connectingNode[1] >= 1):
                            weightedEdges.append(((x, y, baseStepSize), connectingNode, baseStepSize))
                    initialGraph.add_weighted_edges_from(weightedEdges)

        return (initialGraph, totalRows, totalCols, startingNode, endNode)


if __name__ == "__main__":
    inputreader = InputReader("./Data/test1.txt")
    inputreader.readFile()
    inputreader.createBaseGraph()
