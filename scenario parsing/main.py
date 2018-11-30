import networkx as nx
import matplotlib.pyplot as plt

nodes = [111, 222, 1, 2, 3]
edges = [(1,2), (2,3), (3,1), (111, 222)]

grpA = [111, 222]
grpB = [1,2,3]
grpC = [222]

G = nx.DiGraph()
G.add_nodes_from(nodes)
G.add_edges_from(edges)

position = nx.circular_layout(G)

nx.draw(G, pos=position,
                 nodelist = grpA,
                 edgelist = edges,
                 with_labels = True,
                 alpha= 1,
                 linewidths = 3,
                 node_color = 'y',
                 width = 2,
                 font_size = 16,
                 node_size = 1000,
                 node_shape = 's'
                 )

nx.draw(G, pos=position,
                 nodelist = grpB,
                 edgelist = edges,
                 with_labels = True,
                 alpha= 1,
                 linewidths = 3,
                 node_color = 'r',
                 width = 2,
                 font_size = 16,
                 node_size = 1000,
                 node_shape = 's'
                 )


nx.draw(G, pos=position,
                 nodelist = grpC,

                 with_labels = True,
                 alpha= 1,
                 linewidths = 3,
                 node_color = 'green',
                 width = 2,
                 font_size = 16,
                 node_size = 1000,
                 node_shape = 's'
                 )


plt.show()