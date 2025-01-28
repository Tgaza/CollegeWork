import networkx as nx


class Alice:
    curNode = None

    def __init__(self, startingNode):
        self.curNode = startingNode

    def move(self, newNode):
        self.curNode = newNode
