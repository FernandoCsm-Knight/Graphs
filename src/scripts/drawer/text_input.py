import pygame

class TextInput:
    def __init__(self, font, x, y, w, h, text='', father_width=100, color=(0, 0, 0), click_color=(0, 128, 255)):
        self.rect = pygame.Rect(x, y, w, h)
        self.color = color
        self.click_color = click_color
        self.text = text
        self.font = font
        self.txt_surface = self.font.render(text, True, self.color)
        self.active = False
        self.father_width = father_width

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            self.active = self.rect.collidepoint(event.pos)
            self.color = self.click_color if self.active else self.color
        if event.type == pygame.KEYUP and self.active:
            if event.key == pygame.K_RETURN:
                return self.text
            elif event.key == pygame.K_BACKSPACE:
                self.text = self.text[:-1]
            else:
                self.text += event.unicode
            self.txt_surface = self.font.render(self.text, True, self.color)
        return None

    def update(self):
        width = max(self.father_width, self.txt_surface.get_width() + 10)
        self.rect.w = width

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect, 2)
        screen.blit(self.txt_surface, (self.rect.x + 5, self.rect.y + 5))
        
    def clear(self):
        self.text = ''
        self.txt_surface = self.font.render(self.text, True, self.color)
