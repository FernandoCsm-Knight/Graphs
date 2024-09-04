import threading
from drawer.graph import GraphDrawer

def run_graph():
    graph_drawer = GraphDrawer()
    graph_drawer.run()

if __name__ == '__main__':
    graph_thread = threading.Thread(target=run_graph)
    graph_thread.start()
    graph_thread.join() 