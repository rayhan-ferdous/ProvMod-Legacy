import networkx as nx
import matplotlib.pyplot as plt

view = 1

#f = open('test.txt')
f0 = open('scenarios/0.log') #analysis
f1 = open('scenarios/1.log') #prj>report
f2 = open('scenarios/2.log') #prj>open
f3 = open('scenarios/3.log') #prj>log>select
f4 = open('scenarios/4.log') #prj>saveas
f5 = open('scenarios/5.log') #prj>refresh rate>select
f6 = open('scenarios/6.log') #observation>open
f7 = open('scenarios/7.log') #prj>frequency default>cancel
f8 = open('scenarios/8.log') #parameters
f9 = open('scenarios/9.log') #parameters
f10 = open('scenarios/10.log') #help

def buildgraph(f, view):
    g = nx.DiGraph()
    stack = []

    for line in f:
        # get func and file names without unnecessary texts
        funname = ''
        if ':' in line:
            funname = line.strip()[line.find(':'):line.find('(') - 0]
        else:
            funname = line.strip()[1:line.find('(') - 0]


        filename = line.strip()[line.find('@@@') + 4: -1]


        #root opening
        if '<root>' in line:
            stack.append('root')
            g.add_nodes_from(['root'])

        #root closing
        elif '</root>' in line:
            stack.pop()

        #opening other than root
        elif '</' not in line:
            if view == 1:
                stack.append(funname)
            else:
                stack.append(filename)

            parent = stack[len(stack)-2]
            child = stack[len(stack)-1]

            #print stack[len(stack)-2]
            #print len(stack)-2
            #print stack[-1]

            g.add_edges_from([(parent, child)])

        else:
            stack.pop()

    #end of loop

    #print stack
    print 'unique scenario extracted for', f.name

    return g

def custom_draw(g):
    nx.draw_circular(g,
                     with_labels=True,
                     node_size=500,
                     edge_color='darkblue',
                     node_shape = 's',
                     width=1,
                     alpha = 1,
                     node_color='lightgreen',
                     font_color='red',
                     font_size=8,
                     arrowstyle = '->',


                     )

    plt.show(block=True)

def compressed_info(g):
    nodes = []

    for e in g.nodes:
        nodes.append(e)

    return nodes

def similarity(list1, list2):
    score = 0
    for i in list1:
        if i in list2:
            score = score+1

    return score


### existing scenario part

g0 = buildgraph(f0, view)
g1 = buildgraph(f1, view)
g2 = buildgraph(f2, view)
g3 = buildgraph(f3, view)
g4 = buildgraph(f4, view)
g5 = buildgraph(f5, view)
g6 = buildgraph(f6, view)
g7 = buildgraph(f7, view)
g8 = buildgraph(f8, view)
g9 = buildgraph(f9, view)
g10 = buildgraph(f10, view)




### building graph metric

#full graph
graphs = [g0, g1, g2, g3, g4, g5, g6, g7, g8, g9, g10]

#compressed graph
compressed_graphs = []

for g in graphs:
    compressed_graphs.append(compressed_info(g))


### user scenario part

ftest = open('C:/injection.log')
gtest = buildgraph(ftest, view)

#custom_draw(gtest)

#compress graph
compressed_gtest = compressed_info(gtest)

### get similarities

sims = []
for com in compressed_graphs:
    sims.append(similarity(com, compressed_gtest))

print '\n\n'

print sims

maxsim = max(sims)
matchingscene = sims.index(maxsim)
print 'maxsim =', maxsim
print 'scenario', matchingscene

def color():
    nodegrp1 = graphs[matchingscene].nodes
    edgegrp1 = graphs[matchingscene].edges

    nodegrp2 = gtest.nodes
    edgegrp2 = gtest.edges

    G = nx.DiGraph()
    G.add_nodes_from(nodegrp1)
    G.add_edges_from(edgegrp1)
    G.add_nodes_from(nodegrp2)
    G.add_edges_from(edgegrp2)

    position = nx.circular_layout(G)

    nx.draw(G,
            pos=position,
            nodelist = nodegrp1,
            edgelist = edgegrp1,
            with_labels = True,
            node_size = 500,
            edge_color = 'darkblue',
            node_shape = 's',
            width = 1,
            alpha = 1,
            node_color = 'yellow',
            font_color = 'red',
            font_size = 8,
            arrowstyle = '->',
            )

    nx.draw(G,
            pos=position,
            nodelist = nodegrp2,
            edgelist = edgegrp2,
            with_labels = False,
            node_size = 500,
            #edge_color = 'lightgreen',
            #node_shape = 'd',
            width = 0,
            alpha = 1,
            node_color = 'lightgreen',
            font_color = 'red',
            font_size = 8,
            #arrowstyle = '->',
            )

    plt.show()





color()



open('C:/injection.log', 'w').close()