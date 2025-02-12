import sys
import networkx as nx

from InputReader import InputReader
from Maze import Maze

if __name__ == "__main__":
    try:
        inputFile = sys.argv[1]
    except:
        inputFile = "MazeProject/Data/test1.txt"
    inputReader = InputReader(inputFile)
    sys.setrecursionlimit(1500)
    inputReader.readFile()
    baseData = inputReader.createBaseGraph()
    maze = Maze(baseData)
    maze.buildFullGraph()
    #maze.displayGraph()
    maze.findShortestPath()
