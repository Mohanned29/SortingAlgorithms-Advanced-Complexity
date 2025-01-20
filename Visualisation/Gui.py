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
    width, height = 1000, 1200
    screen = pygame.display.set_mode((width, height), pygame.NOFRAME)
    pygame.display.set_caption("Sorting Algorithm Visualization")
    clock = pygame.time.Clock()

    n = 300
    arr = [random.randint(10, 1000) for _ in range(n)]

    delay = 0.01
    sorting_algorithm(arr, lambda arr, color_map: draw_array(screen, arr, color_map), delay)

    time.sleep(2)
    pygame.quit()

def sorting_menu():
    pygame.init()
    width, height = 1000, 1200
    screen = pygame.display.set_mode((width, height), pygame.NOFRAME)
    pygame.display.set_caption("Sorting Algorithm Menu")
    font = pygame.font.Font(None, 50)
    clock = pygame.time.Clock()

    menu_items = ["Bubble Sort", "Quick Sort"]
    selected_index = 0
    running = True

    while running:
        screen.fill((0, 0, 0))

        for i, item in enumerate(menu_items):
            color = (255, 255, 255)
            if i == selected_index:
                color = (0, 255, 0)
            text = font.render(item, True, color)
            screen.blit(text, (width // 2 - text.get_width() // 2, height // 2 + i * 60 - text.get_height()))

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    selected_index = (selected_index - 1) % len(menu_items)
                elif event.key == pygame.K_DOWN:
                    selected_index = (selected_index + 1) % len(menu_items)
                elif event.key == pygame.K_RETURN:
                    if menu_items[selected_index] == "Bubble Sort":
                        visualize_sorting(bubble_sort_visual)
                    elif menu_items[selected_index] == "Quick Sort":
                        visualize_sorting(quick_sort_visual)
                    running = False

        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    sorting_menu()
