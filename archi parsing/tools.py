import py2neo as pn

def delete_graph():
    graph = pn.Graph('http://34.239.207.52:34199/db/data/',
                     http_port=34199,
                     bolt_port=34198,
                     user='neo4j',
                     password='springs-rules-reserve')

    graph.delete_all()

    print 'graph deleted'

def format_log():
    lines = ['<crhm>']

    f = open("c:\\injection.log")

    for lin in f:
        lines.append(lin.strip())

    lines.append('</crhm>')

    xml = open('injectionv2.log', 'w')

    for e in lines:
        xml.write(e + '\n')

    print 'log formatted'

def create_graph():
    scenario = raw_input('scenario name?')


    graph = pn.Graph('http://34.239.207.52:34199/db/data/',
                     http_port=34199,
                     bolt_port=34198,
                     user='neo4j',
                     password='springs-rules-reserve')

    xml = open('injectionv2.log')
    stack = []
    edges = set()
    nodes = set()

    for line in xml:
        if '<crhm>' in line:
            stack.append('crhm')
            nodes.add('crhm')
            q = 'create(n:System{name: "crhm", scenario: "'+ scenario+'"})'
            graph.run(q)
            # print stack

        elif '</crhm>' in line:
            stack.pop()
            # print stack

        elif '</' not in line:
            stack.append(line.strip()[1: len(line) - 3])

            parent = stack[len(stack) - 2]
            child = stack[len(stack) - 1]

            # print stack
            # print parent
            print child

            childfnameindex = child.find('@@@')
            childfname = child[childfnameindex + 4:len(child) - 9]

            if child not in nodes:
                nodes.add(child)
                q1 = 'create(n:'+ childfname +'{name:"' + child + '", scenario:"' + scenario + '"})'
                graph.run(q1)

            if ((parent, child)) not in edges:
                edges.add((parent, child))
                q2 = 'match (p), (c) where p.name ="' + parent + '" and c.name ="' + child + '" create (p)-[r:calls]->(c)'
                graph.run(q2)


        else:
            stack.pop()
            # print stack

    print stack

    print 'parsing done!'

def flush_log_source():
    f = open('c:\\injection.log', 'w')
    f.close()

    print 'log source flushed!'