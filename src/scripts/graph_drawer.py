import os
import sys
import threading
from drawer.graph import GraphDrawer

def run_graph(try_import):
    graph_drawer = GraphDrawer()
    if try_import:
        graph_drawer.import_graph()
    graph_drawer.run()

def is_open(path):
    if os.path.exists(path):
        if os.path.getsize(path) > 0:
            return True
        else:
            return False
    else:
        return False

if __name__ == '__main__':
    try_import = is_open('tmp/importable.json')
    graph_thread = threading.Thread(target=run_graph, args=(try_import,))
    graph_thread.start()
    graph_thread.join() 