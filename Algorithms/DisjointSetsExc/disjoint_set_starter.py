#Starter code for disjoint set exercise
#Naive implementation without any optimizations

size,queries = map(int,input().split()) 

parent = list(range(size)) # each element is its own root at first.

def find(x):
    
    while parent[x]!=x:
        x = parent[x]
    return x   
    
def union(x,y):
    
    root_x = find(x)
    root_y = find(y)
   
    if root_x != root_y:
        parent[root_y]=root_x  

if __name__ == "__main__":
    for _ in range(queries):
        x, y = map(int,input().split())
        union(x,y)
        print(*parent)
