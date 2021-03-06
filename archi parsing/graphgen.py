#call graph without duplicate
import py2neo as pn
graph = pn.Graph(password = 'password')
graph.delete_all()


xml = open('injection.log')
stack = []
edges = set()
nodes = set()

for line in xml:
    if '<crhm>' in line:
        stack.append('crhm')
        nodes.add('crhm')
        q = 'create(n:System{name: "crhm"})'
        graph.run(q)
        #print stack

    elif '</crhm>' in line:
        stack.pop()
        #print stack

    elif '</' not in line:
        stack.append(line.strip()[1 : len(line)-3])

        parent = stack[len(stack)-2]
        child = stack[len(stack)-1]


        #print stack
        #print parent
        print child

        childfnameindex = child.find('@@@')
        childfname = child[childfnameindex+4:len(child)-6]

        if child not in nodes:
            nodes.add(child)
            q1 = 'create(n:Fn{name:"' + child + '", origin:"' + childfname + '"})'
            graph.run(q1)

        if ( (parent, child) ) not in edges:
            edges.add((parent, child))
            q2 = 'match (p), (c) where p.name ="' + parent + '" and c.name ="' + child + '" create (p)-[r:calls]->(c)'
            graph.run(q2)


    else:
        stack.pop()
        #print stack



print stack