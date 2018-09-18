'''py2neo v3.x.x'''
'''remote host connection test'''

import py2neo as pn
graph = pn.Graph('http://34.239.207.52:34199/db/data/',
                 http_port = 34199,
                 bolt_port = 34198,
                 user = 'neo4j',
                 password = 'springs-rules-reserve')

q = 'create (n:first_remote_node)'
graph.run(q)