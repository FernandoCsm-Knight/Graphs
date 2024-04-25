import os
import sys
import json
import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph(json_file, show_in_a_window, png_file_name):
    with open(json_file, 'r') as file:
        data = json.load(file)

    if data['directed']:
        G = nx.DiGraph()
    else:
        G = nx.Graph()

    for node in data['nodes']:
        G.add_node(node['id'])

    for edge in data['edges']:
        G.add_edge(edge['source'], edge['target'])

    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, node_size=500, node_color='lightblue', font_size=12, font_weight='bold')

    plt.axis('off')
    plt.savefig(png_file_name, format='png', dpi=300, bbox_inches='tight')
    
    if show_in_a_window:
        plt.show()

if __name__ == '__main__':
    if not os.path.exists('img'):
        os.makedirs('img')
    
    if len(sys.argv) < 2:
        print("Usage: python graph_visualizer.py <json_file> <show_in_a_window>")
        sys.exit(1)

    json_file = sys.argv[1]
    show_in_a_window = False
    png_file_name = 'img/graph_visualization.png'

    if len(sys.argv) >= 3:
        png_file_name = f'img/{sys.argv[2]}' if sys.argv[2].endswith('.png') else f'img/{sys.argv[2]}.png'
    
    if len(sys.argv) >= 4:
        show_in_a_window = sys.argv[3].lower() == 'true'
    
    visualize_graph(json_file, show_in_a_window, png_file_name)