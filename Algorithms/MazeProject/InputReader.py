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
        # each row array should be of format [row:int,col:int,::,N:string,E:string..,::,tiletype:char]
        # except the first row which will be [totalRows:int,totalCols:int,::,startRow:int,startCol:int,::,endRow:int,endCol:int]
        for dataRow in self.dataArray:
            if not firstLineProcessed:
                totalRows = dataRow[0]
                totalCols = dataRow[1]
                startingNode = (dataRow[3], dataRow[4])
                endNode = (dataRow[6], dataRow[7])
                firstLineProcessed = True
            else:
                initialGraph.add_node((dataRow[0], dataRow[1]))
                initialGraph.nodes[(dataRow[0],
                                    dataRow[1])]["directions"] = dataRow[3:-2]
                initialGraph.nodes[(dataRow[0],
                                    dataRow[1])]["type"] = dataRow[-1]
                weightedEdges = []
                for direction in initialGraph.nodes[(
                        dataRow[0], dataRow[1])]["directions"]:
                    if direction == "N":
                        weightedEdges.append(((dataRow[0], dataRow[1]),
                                              (dataRow[0], dataRow[1] - 1), 1))
                    elif direction == "NE":
                        weightedEdges.append((
                            (dataRow[0], dataRow[1]),
                            (dataRow[0] + 1, dataRow[1] - 1),
                            1,
                        ))
                    elif direction == "E":
                        weightedEdges.append(((dataRow[0], dataRow[1]),
                                              (dataRow[0] + 1, dataRow[1]), 1))
                    elif direction == "SE":
                        weightedEdges.append((
                            (dataRow[0], dataRow[1]),
                            (dataRow[0] + 1, dataRow[1] + 1),
                            1,
                        ))
                    elif direction == "S":
                        weightedEdges.append(((dataRow[0], dataRow[1]),
                                              (dataRow[0], dataRow[1] + 1), 1))
                    elif direction == "SW":
                        weightedEdges.append((
                            (dataRow[0], dataRow[1]),
                            (dataRow[0] - 1, dataRow[1] + 1),
                            1,
                        ))
                    elif direction == "W":
                        weightedEdges.append(((dataRow[0], dataRow[1]),
                                              (dataRow[0] - 1, dataRow[1]), 1))
                    elif direction == "NW":
                        weightedEdges.append((
                            (dataRow[0], dataRow[1]),
                            (dataRow[0] - 1, dataRow[1] - 1),
                            1,
                        ))

        return (initialGraph, totalRows, totalCols, startingNode, endNode)


if __name__ == "__main__":
    inputreader = InputReader("./Data/test1.txt")
    inputreader.readFile()
    inputreader.createBaseGraph()
