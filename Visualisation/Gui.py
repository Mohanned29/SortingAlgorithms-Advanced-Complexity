import pygame
import random
import time

def bubble_sort_visual(arr, draw_array, delay):
    n = len(arr)
    for i in range(n):
        for j in range(n - i - 1):
            draw_array(arr, {j: "red", j + 1: "green"})
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                draw_array(arr, {j: "yellow", j + 1: "yellow"})
            time.sleep(delay)

def quick_sort_visual(arr, draw_array, delay):
    def partition(low, high):
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            draw_array(arr, {j: "red", high: "green"})
            if arr[j] < pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
                draw_array(arr, {i: "yellow", j: "yellow"})
            time.sleep(delay)
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        return i + 1

    def quick_sort_recursive(low, high):
        if low < high:
            pi = partition(low, high)
            quick_sort_recursive(low, pi - 1)
            quick_sort_recursive(pi + 1, high)

    quick_sort_recursive(0, len(arr) - 1)

def insertion_sort_visual(arr, draw_array, delay):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            draw_array(arr, {j: "red", j + 1: "yellow"})
            arr[j + 1] = arr[j]
            j -= 1
            time.sleep(delay)
        arr[j + 1] = key
        draw_array(arr, {j + 1: "green"})

def draw_array(screen, arr, color_map):
    screen.fill((0, 0, 0))
    width = screen.get_width()
    height = screen.get_height()
    bar_width = width // len(arr)
    max_val = max(arr)
    for i, val in enumerate(arr):
        color = (255, 255, 255)
        if i in color_map:
            if color_map[i] == "red":
                color = (255, 0, 0)
            elif color_map[i] == "green":
                color = (0, 255, 0)
            elif color_map[i] == "yellow":
                color = (255, 255, 0)
        pygame.draw.rect(screen, color, (i * bar_width, height - (val / max_val) * height, bar_width, (val / max_val) * height))
    pygame.display.flip()

def visualize_sorting(sorting_algorithm):
    pygame.init()
    width, height = 800, 600
    screen = pygame.display.set_mode((width, height))
    pygame.display.set_caption("Sorting Algorithm Visualization")

    n = 150
    arr = [random.randint(10, 1000) for _ in range(n)]

    delay = 0.0005
    sorting_algorithm(arr, lambda arr, color_map: draw_array(screen, arr, color_map), delay)

    time.sleep(2)
    pygame.quit()

def sorting_menu():
    pygame.init()
    screen = pygame.display.set_mode((800, 600))
    pygame.display.set_caption("Sorting Algorithm Menu")

    red = (255, 0, 0)
    white = (255, 255, 255)
    hover_color = (200, 200, 200)
    button_color = (50, 50, 50)

    menu_items = [
        {"text": "Bubble Sort", "action": lambda: visualize_sorting(bubble_sort_visual)},
        {"text": "Quick Sort", "action": lambda: visualize_sorting(quick_sort_visual)},
        {"text": "Insertion Sort", "action": lambda: visualize_sorting(insertion_sort_visual)},
    ]

    font = pygame.font.Font(None, 36)
    button_width = 200
    button_height = 50
    button_margin = 20
    buttons = []

    rows = 1 + len(menu_items) // 3
    for i, item in enumerate(menu_items):
        row = i // 3
        col = i % 3
        x = 50 + col * (button_width + button_margin)
        y = 100 + row * (button_height + button_margin)
        buttons.append({"rect": pygame.Rect(x, y, button_width, button_height), "text": item["text"], "action": item["action"]})

    running = True
    while running:
        screen.fill(red)

        mouse_pos = pygame.mouse.get_pos()

        for button in buttons:
            rect = button["rect"]
            text = button["text"]
            color = hover_color if rect.collidepoint(mouse_pos) else button_color
            pygame.draw.rect(screen, color, rect, border_radius=10)
            text_surface = font.render(text, True, white)
            text_rect = text_surface.get_rect(center=rect.center)
            screen.blit(text_surface, text_rect)

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                for button in buttons:
                    if button["rect"].collidepoint(mouse_pos):
                        button["action"]()
                        running = False

    pygame.quit()

if __name__ == "__main__":
    sorting_menu()
