import glob
import os
import math
import json
import pygame
import networkx as nx
from networkx.readwrite import json_graph

WHITE = (238, 248, 255)
BLACK = (20, 20, 20)
LIGHT_CYAN = (209, 245, 255)
NON_PHOTO_BLUE = (120, 227, 253)
FLUORESCENT_CYAN = (52, 246, 242)
SLATE_BLUE = (125, 83, 222)
HOVER_COLOR = (100, 200, 255)
CLICK_COLOR = (0, 128, 255) 

def draw_arrow(screen, color, start, end, arrow_size):
    dx = end[0] - start[0]
    dy = end[1] - start[1]
    angle = math.atan2(dy, dx)

    end_line = (end[0] - arrow_size * math.cos(angle), end[1] - arrow_size * math.sin(angle))

    pygame.draw.line(screen, color, start, end_line, edge_width)

    arrow_tip = end
    arrow_left = (end_line[0] - arrow_size * math.cos(angle - math.pi / 6), end_line[1] - arrow_size * math.sin(angle - math.pi / 6))
    arrow_right = (end_line[0] - arrow_size * math.cos(angle + math.pi / 6), end_line[1] - arrow_size * math.sin(angle + math.pi / 6))

    pygame.draw.polygon(screen, color, [arrow_tip, arrow_left, arrow_right])

def draw_button(screen, button_text, button_pos, button_size, button_color, text_color, hover_color, click_color, clicked):
    mouse_pos = pygame.mouse.get_pos()
    button_rect = pygame.Rect(button_pos, button_size)
    button_color_current = button_color

    if button_rect.collidepoint(mouse_pos):
        button_color_current = hover_color
    if clicked:
        button_color_current = click_color

    pygame.draw.rect(screen, button_color_current, button_rect, border_radius=5)
    font = pygame.font.SysFont(None, 24)
    text = font.render(button_text, True, text_color)
    text_rect = text.get_rect(center=button_rect.center)
    screen.blit(text, text_rect)
    return button_rect

def save_graph(graph, filename='tmp/importable.json'):    
    data = json_graph.node_link_data(graph)
    with open(filename, 'w') as f:
        json.dump(data, f, indent=2)

def toggle_graph_type(G, directed):
    if directed:
        return G.to_directed()
    else:
        return G.to_undirected()

def point_line_distance(point, start, end):
    if start == end:
        return math.hypot(start[0] - point[0], start[1] - point[1])
    else:
        nom = abs((end[1] - start[1]) * point[0] - (end[0] - start[0]) * point[1] + end[0] * start[1] - end[1] * start[0])
        denom = math.hypot(end[1] - start[1], end[0] - start[0])
        return nom / denom

def delete_edge(G, pos, edge_width):
    threshold = edge_width + 5
    for edge in G.edges():
        src_pos = G.nodes[edge[0]]['pos']
        dest_pos = G.nodes[edge[1]]['pos']
        
        distance = point_line_distance(pos, src_pos, dest_pos)
        if distance < threshold:
            G.remove_edge(edge[0], edge[1])
            break

def add_node(G):
    pos = event.pos
    node = len(G.nodes())
    G.add_node(node, pos=pos)

def draw_graph(screen, G, directed):
    for node in G.nodes():
        pos = G.nodes[node]['pos']
        
        if screen.get_width() < pos[0] + node_size:
            pos = (screen.get_width() - node_size, pos[1])
            
        if screen.get_height() < pos[1] + node_size:
            pos = (pos[0], screen.get_height() - node_size)
        
        G.nodes[node]['pos'] = pos
        pygame.draw.circle(screen, node_color, pos, node_size)
        label = G.nodes[node].get('label', str(node))
        text = node_font.render(label, True, BLACK)
        text_rect = text.get_rect(center=pos)
        screen.blit(text, text_rect)
    
    for edge in G.edges():
        src_pos = G.nodes[edge[0]]['pos']
        dest_pos = G.nodes[edge[1]]['pos']

        angle = math.atan2(dest_pos[1] - src_pos[1], dest_pos[0] - src_pos[0])
        src_pos = (src_pos[0] + node_size * math.cos(angle), src_pos[1] + node_size * math.sin(angle))
        dest_pos = (dest_pos[0] - node_size * math.cos(angle), dest_pos[1] - node_size * math.sin(angle))

        if directed:
            draw_arrow(screen, edge_color, src_pos, dest_pos, 10)  
        else:
            pygame.draw.line(screen, edge_color, src_pos, dest_pos, edge_width)

if __name__ == '__main__':
    if not os.path.exists('tmp/'):
        os.makedirs('tmp/')
    
    files = glob.glob('data/graph*')
    filename = f'data/graph_{len(files)}.json'
    
    pygame.init()

    width, height = 800, 600
    screen = pygame.display.set_mode((width, height), pygame.RESIZABLE)
    pygame.display.set_caption("Graph Editor")

    icon = pygame.image.load('src/scripts/assets/graph_drawer_logo.png')
    pygame.display.set_icon(icon)

    G = nx.Graph()

    node_size = 20
    node_color = NON_PHOTO_BLUE
    node_font = pygame.font.SysFont(None, 24)

    edge_color = BLACK
    edge_width = 2

    running = True
    dragging = False
    start_node = None
    is_directed = False
    edge_start_node = None
    button_clicked = False

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                save_graph(G);
                running = False
            
            elif event.type == pygame.MOUSEBUTTONDOWN:
                
                if menu_button.collidepoint(event.pos):
                    button_clicked = True
                    save_graph(G, filename)
                
                elif toggle_button.collidepoint(event.pos):
                    is_directed = not is_directed
                    G = toggle_graph_type(G, is_directed)    
                
                else:
                    for node in G.nodes():
                        pos = G.nodes[node]['pos']
                        if (pos[0] - node_size <= event.pos[0] <= pos[0] + node_size and
                            pos[1] - node_size <= event.pos[1] <= pos[1] + node_size):
                            if event.button == 1: 
                                edge_start_node = None
                                dragging = True
                                start_node = node
                                G.nodes[node]['last_click_time'] = pygame.time.get_ticks()
                            
                            elif event.button == 3:
                                if edge_start_node is None:
                                    edge_start_node = node
                                else:
                                    if edge_start_node != node:
                                        G.add_edge(edge_start_node, node)
                                    edge_start_node = None
                                    
                            elif event.button == 2:
                                dragging = False
                                G.remove_node(node)
                            break
                    else:
                        if event.button == 1:
                            add_node(G)
                            
                        elif event.button == 3:
                            delete_edge(G, event.pos, edge_width)

                
            elif event.type == pygame.MOUSEBUTTONUP:
                if button_clicked:
                    button_clicked = False
                
                if event.button == 1:  
                    dragging = False
                    start_node = None
                    
            elif event.type == pygame.MOUSEMOTION:
                if dragging and start_node is not None:
                    G.nodes[start_node]['pos'] = event.pos

        screen.fill(WHITE)
        draw_graph(screen, G, is_directed)
        
        menu_button = draw_button(
            screen, 
            "Save", 
            (10, 10), 
            (60, 30), 
            NON_PHOTO_BLUE, 
            BLACK, 
            HOVER_COLOR, 
            CLICK_COLOR, 
            button_clicked
        )
        
        toggle_button_text = "Directed" if is_directed else "Undirected"
        toggle_button = draw_button(
            screen, 
            toggle_button_text, 
            (80, 10), 
            (100, 30),
            NON_PHOTO_BLUE, 
            BLACK, 
            HOVER_COLOR, 
            CLICK_COLOR, 
            False
        )
        
        pygame.display.flip()

    pygame.quit()