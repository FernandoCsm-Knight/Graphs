import glob
import os
import math
import json
import pygame
import networkx as nx
from networkx.readwrite import json_graph

class GraphDrawer:
    WHITE = (238, 248, 255)
    BLACK = (20, 20, 20)
    LIGHT_CYAN = (209, 245, 255)
    NON_PHOTO_BLUE = (120, 227, 253)
    FLUORESCENT_CYAN = (52, 246, 242)
    SLATE_BLUE = (125, 83, 222)
    HOVER_COLOR = (100, 200, 255)
    CLICK_COLOR = (0, 128, 255)

    def __init__(self):
        if not os.path.exists('tmp/'):
            os.makedirs('tmp/')

        files = glob.glob('data/graph*')
        self.filename = f'data/graph_{len(files)}.json'
        
        pygame.init()
        self.width, self.height = 800, 600
        self.screen = pygame.display.set_mode((self.width, self.height), pygame.RESIZABLE)
        pygame.display.set_caption('Graph Editor')
        icon = pygame.image.load('src/scripts/assets/graph_drawer_logo.png')
        pygame.display.set_icon(icon)

        self.G = nx.Graph()
        self.node_id = 0
        self.node_size = 20
        self.node_color = self.NON_PHOTO_BLUE
        self.node_font = pygame.font.SysFont(None, 24)
        self.edge_color = self.BLACK
        self.edge_width = 2

        self.dragging = None
        self.is_directed = False
        self.edge_start_node = None
        self.button_clicked = False
        self.popup = None

    def draw_arrow(self, color, start, end, arrow_size):
        dx, dy = end[0] - start[0], end[1] - start[1]
        angle = math.atan2(dy, dx)
        end_line = (end[0] - arrow_size * math.cos(angle), end[1] - arrow_size * math.sin(angle))
        pygame.draw.line(self.screen, color, start, end_line, self.edge_width)
        arrow_tip = end
        arrow_left = (end_line[0] - arrow_size * math.cos(angle - math.pi / 6), 
                      end_line[1] - arrow_size * math.sin(angle - math.pi / 6))
        arrow_right = (end_line[0] - arrow_size * math.cos(angle + math.pi / 6), 
                       end_line[1] - arrow_size * math.sin(angle + math.pi / 6))
        pygame.draw.polygon(self.screen, color, [arrow_tip, arrow_left, arrow_right])

    def draw_button(self, button_text, button_pos, button_size, button_color, text_color, hover_color, click_color, clicked):
        mouse_pos = pygame.mouse.get_pos()
        button_rect = pygame.Rect(button_pos, button_size)
        button_color_current = click_color if clicked else hover_color if button_rect.collidepoint(mouse_pos) else button_color
        pygame.draw.rect(self.screen, button_color_current, button_rect, border_radius=5)
        text = self.node_font.render(button_text, True, text_color)
        text_rect = text.get_rect(center=button_rect.center)
        self.screen.blit(text, text_rect)
        return button_rect

    def save_graph(self, filename='tmp/importable.json'):
        data = {
            "directed": self.is_directed,
            "multigraph": False,
            "edges": [
                {
                    "source": u,
                    "target": v,
                    "weight": self.G[u][v].get('weight', 1.0)
                } for u, v in self.G.edges()
            ]
        }
        with open(filename, 'w') as f:
            json.dump(data, f, indent=2)

    def toggle_graph_type(self):
        self.is_directed = not self.is_directed
        self.G = self.G.to_directed() if self.is_directed else self.G.to_undirected()

    @staticmethod
    def point_line_distance(point, start, end):
        if start == end:
            return math.hypot(start[0] - point[0], start[1] - point[1])
        nom = abs((end[1] - start[1]) * point[0] - (end[0] - start[0]) * point[1] + end[0] * start[1] - end[1] * start[0])
        denom = math.hypot(end[1] - start[1], end[0] - start[0])
        return nom / denom

    def delete_edge(self, pos):
        threshold = self.edge_width + 5
        for edge in self.G.edges():
            src_pos, dest_pos = self.G.nodes[edge[0]]['pos'], self.G.nodes[edge[1]]['pos']
            if self.point_line_distance(pos, src_pos, dest_pos) < threshold:
                self.G.remove_edge(*edge)
                break

    def add_node(self, pos):
        self.node_id += 1
        self.G.add_node(self.node_id, pos=pos)

    def draw_graph(self):
        for node, data in self.G.nodes(data=True):
            pos = data['pos']
            pos = (min(self.screen.get_width() - self.node_size, pos[0]),
                   min(self.screen.get_height() - self.node_size, pos[1]))
            self.G.nodes[node]['pos'] = pos
            pygame.draw.circle(self.screen, self.node_color, pos, self.node_size)
            label = data.get('label', str(node))
            text = self.node_font.render(label, True, self.BLACK)
            text_rect = text.get_rect(center=pos)
            self.screen.blit(text, text_rect)

        for edge in self.G.edges():
            src_pos, dest_pos = self.G.nodes[edge[0]]['pos'], self.G.nodes[edge[1]]['pos']
            angle = math.atan2(dest_pos[1] - src_pos[1], dest_pos[0] - src_pos[0])
            src_pos = (src_pos[0] + self.node_size * math.cos(angle), src_pos[1] + self.node_size * math.sin(angle))
            dest_pos = (dest_pos[0] - self.node_size * math.cos(angle), dest_pos[1] - self.node_size * math.sin(angle))

            if self.is_directed:
                self.draw_arrow(self.edge_color, src_pos, dest_pos, 10)
            else:
                pygame.draw.line(self.screen, self.edge_color, src_pos, dest_pos, self.edge_width)

            mid_x, mid_y = (src_pos[0] + dest_pos[0]) / 2, (src_pos[1] + dest_pos[1]) / 2
            weight = self.G.edges[edge].get('weight', '')
            weight_text = self.node_font.render(str(weight), True, self.BLACK)
            weight_rect = weight_text.get_rect(center=(mid_x, mid_y - 15))
            self.screen.blit(weight_text, weight_rect)

    def run(self):
        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.save_graph()
                    running = False
                else:
                    self.handle_event(event)

            self.screen.fill(self.WHITE)
            self.draw_graph()

            self.draw_button(
                'Save', (10, 10), (60, 30), self.NON_PHOTO_BLUE, self.BLACK,
                self.HOVER_COLOR, self.CLICK_COLOR, self.button_clicked
            )

            self.draw_button(
                'Directed' if self.is_directed else 'Undirected',
                (80, 10), (100, 30), self.NON_PHOTO_BLUE, self.BLACK,
                self.HOVER_COLOR, self.CLICK_COLOR, False
            )

            if self.popup is not None:
                self.popup.draw(self.screen)

            pygame.display.flip()

        pygame.quit()

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            self.handle_mouse_down(event)
        elif event.type == pygame.MOUSEBUTTONUP:
            self.handle_mouse_up(event)
        elif event.type == pygame.MOUSEMOTION:
            self.handle_mouse_motion(event)
        elif event.type == pygame.KEYUP:
            self.handle_key_up(event)

        if self.popup:
            if self.popup.handle_event(event, self.G):
                self.popup.update()
            else:
                self.popup = None

    def handle_mouse_down(self, event):
        if self.popup is not None and self.popup.collidepoint(event.pos):
            return

        if self.draw_button('Save', (10, 10), (60, 30), self.NON_PHOTO_BLUE, self.BLACK,
                            self.HOVER_COLOR, self.CLICK_COLOR, False).collidepoint(event.pos):
            self.button_clicked = True
            self.save_graph(self.filename)
        elif self.draw_button('Directed' if self.is_directed else 'Undirected',
                              (80, 10), (100, 30), self.NON_PHOTO_BLUE, self.BLACK,
                              self.HOVER_COLOR, self.CLICK_COLOR, False).collidepoint(event.pos):
            self.toggle_graph_type()
        else:
            self.handle_graph_interaction(event)

    def handle_graph_interaction(self, event):
        for node in self.G.nodes():
            pos = self.G.nodes[node]['pos']
            if (pos[0] - self.node_size <= event.pos[0] <= pos[0] + self.node_size and
                pos[1] - self.node_size <= event.pos[1] <= pos[1] + self.node_size):
                if event.button == 1:
                    self.edge_start_node = None
                    self.dragging = node
                    return
                elif event.button == 3:
                    if self.edge_start_node is None:
                        self.edge_start_node = node
                    else:
                        if self.edge_start_node != node:
                            self.G.add_edge(self.edge_start_node, node)
                        self.edge_start_node = None
                    return
                elif event.button == 2:
                    self.G.remove_node(node)
                    self.dragging = None
                    return

        if event.button == 1:
            self.add_node(event.pos)
        elif event.button == 3:
            self.delete_edge(event.pos)

    def handle_mouse_up(self, event):
        if event.button == 1:
            self.button_clicked = False
            self.dragging = None

    def handle_mouse_motion(self, event):
        if self.dragging is not None:
            self.G.nodes[self.dragging]['pos'] = event.pos

    def handle_key_up(self, event):
        if event.key == pygame.K_e:
            mouse_pos = pygame.mouse.get_pos()
            self.popup = None

            for node in self.G.nodes():
                pos = self.G.nodes[node]['pos']
                if (pos[0] - self.node_size <= mouse_pos[0] <= pos[0] + self.node_size and
                    pos[1] - self.node_size <= mouse_pos[1] <= pos[1] + self.node_size):
                    self.popup = Popup(self.node_font, f'Node {node}', mouse_pos, node=node)
                    return

            for edge in self.G.edges():
                src_pos = self.G.nodes[edge[0]]['pos']
                dest_pos = self.G.nodes[edge[1]]['pos']
                distance = self.point_line_distance(mouse_pos, src_pos, dest_pos)
                if distance < self.edge_width + 5:
                    self.popup = Popup(self.node_font, f'Edge {edge[0]}-{edge[1]}', mouse_pos, edge=edge)
                    return

class TextInput:
    def __init__(self, font, x, y, w, h, text='', father_width=100):
        self.rect = pygame.Rect(x, y, w, h)
        self.color = GraphDrawer.BLACK
        self.text = text
        self.font = font
        self.txt_surface = self.font.render(text, True, GraphDrawer.BLACK)
        self.active = False
        self.father_width = father_width

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            self.active = self.rect.collidepoint(event.pos)
            self.color = GraphDrawer.CLICK_COLOR if self.active else GraphDrawer.BLACK
        if event.type == pygame.KEYUP and self.active:
            if event.key == pygame.K_RETURN:
                return self.text
            elif event.key == pygame.K_BACKSPACE:
                self.text = self.text[:-1]
            else:
                self.text += event.unicode
            self.txt_surface = self.font.render(self.text, True, GraphDrawer.BLACK)
        return None

    def update(self):
        width = max(self.father_width, self.txt_surface.get_width() + 10)
        self.rect.w = width

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect, 2)
        screen.blit(self.txt_surface, (self.rect.x + 5, self.rect.y + 5))
        
    def clear(self):
        self.text = ''
        self.txt_surface = self.font.render(self.text, True, GraphDrawer.BLACK)

class Popup:
    def __init__(self, font, text, pos, edge=None, node=None):
        self.font = font
        self.text = text
        self.pos = pos
        self.input_box = TextInput(font, pos[0], pos[1], 100, 30, father_width=70)
        self.edge = edge
        self.node = node
        self.padding = 10
        self.update()

    def update(self):
        self.input_box.update()
        self.popup_text = self.font.render(self.text, True, GraphDrawer.BLACK)
        self.popup_rect = self.popup_text.get_rect(center=self.pos)
        background_width = max(self.popup_rect.width + 2 * self.padding, self.input_box.rect.width + 20)
        background_height = self.popup_rect.height + self.input_box.rect.height + 3 * self.padding
        self.background_rect = pygame.Rect(self.popup_rect.left - self.padding, 
                                           self.popup_rect.top - self.padding, 
                                           background_width, background_height)
        self.input_box.rect.topleft = (self.background_rect.left + 10, 
                                       self.background_rect.top + self.popup_rect.height + 20)

    def draw(self, screen):
        pygame.draw.rect(screen, GraphDrawer.NON_PHOTO_BLUE, self.background_rect)
        pygame.draw.rect(screen, GraphDrawer.BLACK, self.background_rect, 2)
        screen.blit(self.popup_text, self.popup_rect)
        self.input_box.draw(screen)

    def collidepoint(self, pos):
        return self.background_rect.collidepoint(pos)

    def handle_event(self, event, graph):
        stay = True
        input_text = self.input_box.handle_event(event)
        
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_RETURN:
                stay = False
                
                if input_text is not None and input_text.strip() != '':       
                    if self.edge is not None:
                        try:
                            input_text = input_text.replace(',', '.').strip()
                            weight = float(input_text)
                            graph[self.edge[0]][self.edge[1]]['weight'] = weight
                            self.input_box.clear()
                        except ValueError:
                            self.input_box.clear()
                            print('Invalid input for weight. Please enter a numeric value.')
                    elif self.node is not None:
                        graph.nodes[self.node]['label'] = input_text.strip()
                
        return stay

if __name__ == '__main__':
    graph_drawer = GraphDrawer()
    graph_drawer.run()