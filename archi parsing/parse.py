import py2neo as pn

def delete_graph():
    graph = pn.Graph(' http://54.167.174.205:35030/db/data/',
                     http_port=35030,
                     bolt_port=35029,
                     user='neo4j',
                     password='circulation-catchers-drawer')

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


    graph = pn.Graph(' http://54.167.174.205:35030/db/data/',
                     http_port=35030,
                     bolt_port=35029,
                     user='neo4j',
                     password='circulation-catchers-drawer')

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
            print parent

            print child




            childfnameindex = child.find('@@@')
            childfname = child[childfnameindex + 4:len(child) - 9]



            if child not in nodes:
                nodes.add(child)
                q1 = 'create(n:'+ childfname +'{name:"' + child + '", scenario:"' + scenario + '"})'
                print q1

                graph.run(q1)

            if ((parent, child)) not in edges:
                edges.add((parent, child))
                q2 = 'match (p), (c) where p.name ="' + parent + '" and c.name ="' + child + '" create (p)-[r:calls]->(c)'
                print q2

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

def rename_nodes():
    graph = pn.Graph(' http://54.167.174.205:35030/db/data/',
                     http_port=35030,
                     bolt_port=35029,
                     user='neo4j',
                     password='circulation-catchers-drawer')

    q = 'match(n) return n'

    n = graph.run(q)

    for k in n:

        name = k['n']['name']

        if name != 'crhm':
            if '::' in name:
                name2 = name[name.find('::') + 2: name.find(' @@@')]
                print name
            else:
                name2 = name[0 : name.find(' @@@')]
                print name

            sq = 'match(n) where n.name = "' + name + '" set n.name2 = "' + name2 + '"'
            print sq
            graph.run(sq)

delete_graph()
format_log()
create_graph()
rename_nodes()
flush_log_source()