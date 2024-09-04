import pygame
from .text_input import TextInput

class Popup:
    def __init__(self, font, text, pos, edge=None, node=None, bg_color=(120, 227, 253), border_color=(0, 0, 0)):
        self.font = font
        self.text = text
        self.pos = pos
        self.bg_color = bg_color
        self.border_color = border_color
        self.input_box = TextInput(font, pos[0], pos[1], 100, 30, father_width=70)
        self.edge = edge
        self.node = node
        self.padding = 10
        self.update()

    def update(self):
        self.input_box.update()
        self.popup_text = self.font.render(self.text, True, self.border_color)
        self.popup_rect = self.popup_text.get_rect(center=self.pos)
        background_width = max(self.popup_rect.width + 2 * self.padding, self.input_box.rect.width + 20)
        background_height = self.popup_rect.height + self.input_box.rect.height + 3 * self.padding
        self.background_rect = pygame.Rect(self.popup_rect.left - self.padding, 
                                           self.popup_rect.top - self.padding, 
                                           background_width, background_height)
        self.input_box.rect.topleft = (self.background_rect.left + 10, 
                                       self.background_rect.top + self.popup_rect.height + 20)

    def draw(self, screen):
        pygame.draw.rect(screen, self.bg_color, self.background_rect)
        pygame.draw.rect(screen, self.border_color, self.background_rect, 2)
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
                        element = input_text.strip()
                        if element.isnumeric():
                            element = int(element)
                        
                        graph.nodes[self.node]['label'] = element
                
        return stay
