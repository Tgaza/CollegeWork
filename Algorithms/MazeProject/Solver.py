import networkx as nx

from Alice import Alice
from InputReader import InputReader
from Maze import Maze

if __name__ == "__main__":
    inputReader = InputReader("./Data/test1.txt")
    inputReader.readFile()
    baseData = inputReader.createBaseGraph()
    maze = Maze(baseData)
    maze.buildFullGraph()
    alice = Alice(maze.getStartingNode())
