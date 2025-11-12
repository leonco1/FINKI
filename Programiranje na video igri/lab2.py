import random
import sys
import pygame
from pygame.locals import *
import math

# Game Configuration
FPS = 120
WIN_WIDTH = 1280
WIN_HEIGHT = 720
SKY_COLOR = pygame.Color("#241f31")
STAR_COLOR = pygame.Color("#f6f5f4")
NUM_STARS = 200
FRAME_RATE = 60
POWER_UP_RADIUS = 15
SHIP_FRAME_COUNT = 6
NUM_POWER_DOWNS = 10

# Load spaceship animation frames
SHIP_FRAMES = [
    pygame.transform.scale(pygame.image.load(f"assets/ship/{i + 1}.png"),
                           (pygame.image.load(f"assets/ship/{i + 1}.png").get_width() // 3,
                            pygame.image.load(f"assets/ship/{i + 1}.png").get_height() // 3))
    for i in range(SHIP_FRAME_COUNT)
]


class Obstacle:

    def __init__(self, ship):
        self.radius = 75
        self.ship_safe_distance = 150  # Safe radius around the ship
        while True:
            self.x = random.randint(0, WIN_WIDTH - POWER_UP_RADIUS * 2)
            self.y = random.randint(0, WIN_HEIGHT - POWER_UP_RADIUS * 2)
            if self.distance_to(ship) > self.ship_safe_distance:
                break

    def update(self, ship):
        self.x -= ship.speed
        if self.x < -self.radius:
            while True:
                self.x = WIN_WIDTH + 25
                self.y = random.randint(0, WIN_HEIGHT - self.radius * 2)
                if self.distance_to(ship) > self.ship_safe_distance:
                    break

    def distance_to(self, ship):
        """Calculate distance to the ship."""
        return math.sqrt((self.x - ship.x) ** 2 + (self.y - ship.y) ** 2)

    def check_collision(self, ship_rect):
        """Check for circular collision with ship."""
        dist = math.sqrt(
            (self.x - ship_rect[0]) ** 2 + (self.y - ship_rect[1]) ** 2
        )
        return dist <= self.radius


class PowerUp(Obstacle):

    def __init__(self, ship):
        super().__init__(ship)
        self.width = 108
        self.height = 92
        self.energy_crystal_image = pygame.transform.scale(
            pygame.image.load("assets/obstacle/energy_crystal.png"),
            (self.width, self.height),
        )
        self.radius = self.width // 2

    def draw(self, surface):
        surface.blit(
            self.energy_crystal_image,
            (self.x - self.width // 2, self.y - self.height // 2),
        )

    def apply(self, ship):
        """Increase ship speed and play sound."""
        if ship.speed < 10:
            ship.speed += 1


class PowerDown(Obstacle):
    def __init__(self, ship):
        super().__init__(ship)
        self.meteor_image = pygame.image.load(
            "assets/obstacle/asteroid.png"
        )
        self.width = self.meteor_image.get_width() // 3
        self.height = self.meteor_image.get_height() // 3
        self.meteor_image = pygame.transform.scale(self.meteor_image, (self.width, self.height))
        self.hit_sound = pygame.mixer.Sound("sound/clash_sound.wav")

    def draw(self, surface):
        surface.blit(
            self.meteor_image,
            (self.x - self.width // 2, self.y - self.height // 2),
        )

    def apply(self, ship):
        if ship.speed > 0:
            ship.speed -= 1
        self.hit_sound.play()


class StarField:

    def __init__(self, num_stars):
        self.stars = [
            {
                "x": random.randint(0, WIN_WIDTH),
                "y": random.randint(0, WIN_HEIGHT),
            }
            for _ in range(num_stars)
        ]

    def update(self, speed):
        if speed == 0:
            return
        for star in self.stars:
            star["x"] -= speed
            if star["x"] < 0:
                star["x"] = WIN_WIDTH
                star["y"] = random.randint(0, WIN_HEIGHT)

    def draw(self, surface):
        for star in self.stars:
            pygame.draw.circle(surface, STAR_COLOR, (star["x"], star["y"]), 2)


class Ship:

    def __init__(self):
        self.x = WIN_WIDTH // 2
        self.y = WIN_HEIGHT // 2
        self.rect = pygame.Rect(
            self.x,
            self.y,
            SHIP_FRAMES[0].get_width(),
            SHIP_FRAMES[0].get_height(),
        )
        self.speed = 1
        self.frame_count = 0
        self.current_frame = 1
        self.move = {"left": False, "right": False, "up": False, "down": False}

    def handle_input(self):
        """Process keyboard input for movement and speed control."""
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == KEYDOWN:
                if event.key in [K_LEFT, K_a]:
                    self.move["left"] = True
                elif event.key in [K_RIGHT, K_d]:
                    self.move["right"] = True
                elif event.key in [K_UP, K_w]:
                    self.move["up"] = True
                elif event.key in [K_DOWN, K_s]:
                    self.move["down"] = True
                elif event.key == K_SPACE:
                    if self.speed <= 10:
                        self.speed += 1
                elif event.key in [K_LSHIFT, K_RSHIFT]:
                    if self.speed >= 0:
                        self.speed -= 1
            elif event.type == KEYUP:
                if event.key in [K_LEFT, K_a]:
                    self.move["left"] = False
                elif event.key in [K_RIGHT, K_d]:
                    self.move["right"] = False
                elif event.key in [K_UP, K_w]:
                    self.move["up"] = False
                elif event.key in [K_DOWN, K_s]:
                    self.move["down"] = False

    def update_position(self):
        """Update ship position based on current movement state."""
        if self.move["left"] and self.x > 0:
            self.x -= self.speed
        if (
                self.move["right"]
                and self.x < WIN_WIDTH - SHIP_FRAMES[0].get_width()
        ):
            self.x += self.speed
        if self.move["up"] and self.y > 0:
            self.y -= self.speed
        if (
                self.move["down"]
                and self.y < WIN_HEIGHT - SHIP_FRAMES[0].get_height()
        ):
            self.y += self.speed
        self.rect.topleft = (self.x, self.y)

    def update_animation(self, speed):
        """Update ship animation frame based on current speed."""
        adjusted_frame_rate = max(FRAME_RATE // (speed + 1), 1)
        if self.speed == 0:
            self.current_frame = 0
        elif self.speed == 10:
            self.current_frame = 4
        else:
            self.frame_count += 1
            if self.frame_count % adjusted_frame_rate == 0:
                self.current_frame = (self.current_frame + 1) % len(
                    SHIP_FRAMES
                )

    def draw(self, surface):
        """Draw ship on screen."""
        surface.blit(SHIP_FRAMES[self.current_frame], (self.x, self.y))


def display_message(surface, message):
    """Display centered message on screen.

    Args:
        surface: PyGame surface to draw on
        message (str): Message to display
    """
    font = pygame.font.SysFont("Arial", 36)
    text = font.render(message, True, pygame.Color("white"))
    text_rect = text.get_rect(center=(WIN_WIDTH // 2, WIN_HEIGHT // 2))
    surface.blit(text, text_rect)


def main():
    """Main game loop."""
    pygame.init()

    # Initialize audio
    pygame.mixer.music.load("sound/background_music.wav")
    pygame.mixer.music.play(-1)

    # Initialize game objects
    fps_clock = pygame.time.Clock()
    display_surf = pygame.display.set_mode((WIN_WIDTH, WIN_HEIGHT))
    pygame.display.set_caption("Ship")

    star_field = StarField(NUM_STARS)
    ship = Ship()
    power_up = PowerUp(ship)
    power_downs = [PowerDown(ship) for _ in range(NUM_POWER_DOWNS)]

    game_over = False
    win_message = ""

    while True:
        if game_over:
            # Handle game over state
            display_surf.fill(SKY_COLOR)
            display_message(display_surf, win_message)
            pygame.display.update()

            for event in pygame.event.get():
                if event.type == KEYDOWN:
                    # Reset game state
                    ship = Ship()
                    power_up = PowerUp(ship)
                    power_downs = [
                        PowerDown(ship) for _ in range(NUM_POWER_DOWNS)
                    ]
                    star_field = StarField(NUM_STARS)
                    game_over = False
                    break
        else:
            # Main game loop
            ship.handle_input()
            ship.update_position()

            # Update game objects
            star_field.update(ship.speed)
            power_up.update(ship)
            for power_down in power_downs:
                power_down.update(ship)

            # Handle collisions
            if power_up.check_collision(ship.rect):
                power_up.apply(ship)
                power_up = PowerUp(ship)

            for i, power_down in enumerate(power_downs):
                if power_down.check_collision(ship.rect):
                    power_down.apply(ship)
                    power_downs[i] = PowerDown(ship)

            ship.update_animation(ship.speed)

            # Check win/lose conditions
            if ship.speed == 0:
                win_message = "You lose! Press any key to restart."
                game_over = True

            if ship.speed == 10:
                # Victory animation
                acceleration_speed = 25
                while ship.x < WIN_WIDTH:
                    ship.x += acceleration_speed
                    display_surf.fill(SKY_COLOR)
                    star_field.draw(display_surf)
                    ship.draw(display_surf)
                    power_up.draw(display_surf)
                    for power_down in power_downs:
                        power_down.draw(display_surf)

                    pygame.display.update()
                    fps_clock.tick(FPS)

                win_message = "You win! Press any key to restart."
                game_over = True

            # Render game state
            display_surf.fill(SKY_COLOR)
            star_field.draw(display_surf)
            ship.draw(display_surf)
            power_up.draw(display_surf)
            for power_down in power_downs:
                power_down.draw(display_surf)

            pygame.display.update()
            fps_clock.tick(FPS)


if __name__ == "__main__":
    main()
