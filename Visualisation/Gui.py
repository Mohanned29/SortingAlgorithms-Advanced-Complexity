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

def selection_sort_visual(arr, draw_array, delay):
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            draw_array(arr, {j: "red", min_idx: "green"})
            if arr[j] < arr[min_idx]:
                min_idx = j
            time.sleep(delay)
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
        draw_array(arr, {i: "yellow", min_idx: "yellow"})

def merge_sort_visual(arr, draw_array, delay):
    def merge_sort_recursive(arr, left, right):
        if left < right:
            mid = (left + right) // 2
            merge_sort_recursive(arr, left, mid)
            merge_sort_recursive(arr, mid + 1, right)
            merge(arr, left, mid, right)

    def merge(arr, left, mid, right):
        n1 = mid - left + 1
        n2 = right - mid
        L = arr[left:left + n1]
        R = arr[mid + 1:mid + 1 + n2]
        i = j = 0
        k = left
        while i < n1 and j < n2:
            draw_array(arr, {k: "red"})
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
            time.sleep(delay)
        while i < n1:
            arr[k] = L[i]
            draw_array(arr, {k: "yellow"})
            i += 1
            k += 1
            time.sleep(delay)
        while j < n2:
            arr[k] = R[j]
            draw_array(arr, {k: "yellow"})
            j += 1
            k += 1
            time.sleep(delay)

    merge_sort_recursive(arr, 0, len(arr) - 1)

def heap_sort_visual(arr, draw_array, delay):
    def heapify(arr, n, i):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2
        if left < n and arr[left] > arr[largest]:
            largest = left
        if right < n and arr[right] > arr[largest]:
            largest = right
        if largest != i:
            arr[i], arr[largest] = arr[largest], arr[i]
            draw_array(arr, {i: "red", largest: "yellow"})
            time.sleep(delay)
            heapify(arr, n, largest)

    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        draw_array(arr, {i: "green", 0: "red"})
        time.sleep(delay)
        heapify(arr, i, 0)

def gnome_sort_visual(arr, draw_array, delay):
    n = len(arr)
    i = 0
    while i < n:
        if i == 0 or arr[i] >= arr[i - 1]:
            i += 1
        else:
            arr[i], arr[i - 1] = arr[i - 1], arr[i]
            draw_array(arr, {i: "red", i - 1: "yellow"})
            time.sleep(delay)
            i -= 1

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

    n = 300
    arr = [random.randint(10, 1000) for _ in range(n)]

    delay = 0.001
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

    menu_items = [
        {"text": "Bubble Sort", "action": lambda: visualize_sorting(bubble_sort_visual)},
        {"text": "Quick Sort", "action": lambda: visualize_sorting(quick_sort_visual)},
        {"text": "Insertion Sort", "action": lambda: visualize_sorting(insertion_sort_visual)},
        {"text": "Selection Sort", "action": lambda: visualize_sorting(selection_sort_visual)},
        {"text": "Merge Sort", "action": lambda: visualize_sorting(merge_sort_visual)},
        {"text": "Heap Sort", "action": lambda: visualize_sorting(heap_sort_visual)},
        {"text": "Gnome Sort", "action": lambda: visualize_sorting(gnome_sort_visual)},
    ]

    font = pygame.font.Font(None, 50)
    button_width = 200
    button_height = 60
    button_margin = 20
    buttons = []

    for i, item in enumerate(menu_items):
        x = (800 - button_width) // 2
        y = 100 + i * (button_height + button_margin)
        buttons.append({"rect": pygame.Rect(x, y, button_width, button_height), "text": item["text"], "action": item["action"]})

    running = True
    while running:
        screen.fill(red)

        mouse_pos = pygame.mouse.get_pos()

        for button in buttons:
            rect = button["rect"]
            text = button["text"]
            color = hover_color if rect.collidepoint(mouse_pos) else white
            pygame.draw.rect(screen, color, rect)
            text_surface = font.render(text, True, red)
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
