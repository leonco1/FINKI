import pygame
import sys

pygame.init()
WIDTH, HEIGHT = 600, 600
ROWS, COLS = 5, 5
SQUARE_SIZE = WIDTH // COLS
FPS = 60
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
YELLOW = (255, 255, 0)

COLORS = [RED, BLUE, GREEN, YELLOW]

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Color Fill Puzzle")

board = [[None for _ in range(COLS)] for _ in range(ROWS)]


def draw_board():
    for row in range(ROWS):
        for col in range(COLS):
            x, y = col * SQUARE_SIZE, row * SQUARE_SIZE
            color = board[row][col] if board[row][col] else WHITE
            pygame.draw.rect(screen, color, (x, y, SQUARE_SIZE, SQUARE_SIZE))
            pygame.draw.rect(screen, BLACK, (x, y, SQUARE_SIZE, SQUARE_SIZE), 2)


def is_valid_color(row, col, color):
    neighbors = [
        (row - 1, col),  # Up
        (row + 1, col),  # Down
        (row, col - 1),  # Left
        (row, col + 1),  # Right
    ]
    for r, c in neighbors:
        if 0 <= r < ROWS and 0 <= c < COLS and board[r][c] == color:
            return False
    return True


def check_win():
    for row in range(ROWS):
        for col in range(COLS):
            if board[row][col] is None or not is_valid_color(row, col, board[row][col]):
                return False
    return True


def main():
    clock = pygame.time.Clock()
    selected_color = COLORS[0]

    running = True
    while running:
        screen.fill(WHITE)

        draw_board()

        if check_win():
            font = pygame.font.Font(None, 74)
            text = font.render("You Win!", True, BLACK)
            screen.blit(text, (WIDTH // 2 - 100, HEIGHT // 2 - 50))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                col, row = x // SQUARE_SIZE, y // SQUARE_SIZE

                if is_valid_color(row, col, selected_color):
                    board[row][col] = selected_color

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_1:
                    selected_color = COLORS[0]
                elif event.key == pygame.K_2:
                    selected_color = COLORS[1]
                elif event.key == pygame.K_3:
                    selected_color = COLORS[2]
                elif event.key == pygame.K_4:
                    selected_color = COLORS[3]

        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
