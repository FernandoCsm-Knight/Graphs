import os
import re
import sys
import json
import networkx as nx
import matplotlib.pyplot as plt

def get_new_filename(directory, base_filename):
    if not os.path.exists(directory):
        os.makedirs(directory)
        print(f'Directory {directory} created.')
        return f'{base_filename}.png'
    
    files_in_directory = os.listdir(directory)
    
    pattern = re.compile(r'^' + re.escape(f'{base_filename}') + r'_(\d+)\.png$')
    max_num = -1
    
    for file in files_in_directory:
        match = pattern.match(file)
        if match:
            num = int(match.group(1))
            if num > max_num:
                max_num = num

    if max_num == -1:
        if f'{base_filename}.png' in files_in_directory:
            new_filename = f'{base_filename}_1.png'
        else:
            new_filename = f'{base_filename}.png'
    else:
        new_filename = f'{base_filename}_{max_num + 1}.png'
    
    return new_filename

def visualize_graph(json_file, show_in_a_window, png_file_name):
    with open(json_file, 'r') as file:
        data = json.load(file)

    G = nx.DiGraph() if data['directed'] else nx.Graph()

    for edge in data['edges']:
        G.add_edge(edge['source'], edge['target'], weight=edge['weight'])

    pos = nx.kamada_kawai_layout(G)
    nx.draw_networkx_nodes(G, pos, node_size=500, node_color='lightblue')
    nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold')
    nx.draw_networkx_edges(G, pos)
    edge_weights = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels={k: (v if v != 0.0 else '') for k, v in edge_weights.items()})
    plt.axis('off')
    plt.savefig(png_file_name, format='png', dpi=300, bbox_inches='tight')
    
    if show_in_a_window:
        plt.show()

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python graph_visualizer.py <json_file> <show_in_a_window>')
        sys.exit(1)

    json_file = sys.argv[1]

    if len(sys.argv) >= 3:
        show_in_a_window = sys.argv[2].lower() == 'true'
    
    if len(sys.argv) >= 4:
        png_file_name = f'img/{get_new_filename("img", (sys.argv[3] if sys.argv[3] else "graph"))}'
    else:
        png_file_name = f'img/{get_new_filename("img", "graph")}'
    
    visualize_graph(json_file, show_in_a_window, png_file_name)