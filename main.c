#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>

#define NUM_STARS 1000
#define STAR_RADIUS 2
#define WIDTH 800
#define HEIGHT 800
#define GRAV_CONST (6.67 / 1e11)
#define MOUSE_MASS 50000
#define DELTA_TIME 10000
#define FRICTION 0.1

typedef struct {
	double mass;
	double velocity_x;
	double velocity_y;
	Vector2 pos;
} Star_t;

Star_t star_array[NUM_STARS];

int random_range(int min, int max);
void init_array();
void draw_pixals();
void update_positions();
double euclidean_distance(Vector2 pos1, Vector2 pos2);

int random_range(int min, int max) {
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
} 

void init_array() {
	for (int i = 0; i < NUM_STARS; ++i) {
   		Vector2 pos = {
        	.x = random_range(0, WIDTH),
        	.y = random_range(0, HEIGHT)
    	};

		Star_t star = {
			.mass = 100,
			.velocity_x = 0.0f,
			.velocity_y = 0.0f,
			.pos = pos
		};
    	star_array[i] = star;
	}
}

void draw_pixels() {
	for (int i = 0; i < NUM_STARS; ++i) {
		DrawCircleV(star_array[i].pos, STAR_RADIUS, WHITE);
	}   
}

void update_position() {
	for(int i = 0; i < NUM_STARS; ++i) {
		if (star_array[i].pos.x > WIDTH || star_array[i].pos.x < 0) star_array[i].velocity_x = star_array[i].velocity_x * -1;
		if (star_array[i].pos.y > HEIGHT || star_array[i].pos.y < 0) star_array[i].velocity_y = star_array[i].velocity_y * -1;

		if (euclidean_distance(star_array[i].pos, GetMousePosition()) < 100) {	
			Vector2 mouse_position = GetMousePosition();
			double distance = euclidean_distance(star_array[i].pos, mouse_position) < 5 ? 5 : euclidean_distance(star_array[i].pos, mouse_position); 
			double gravitional_force = (GRAV_CONST * star_array[i].mass * MOUSE_MASS) / (distance * distance);
			double force_x = gravitional_force * (mouse_position.x - star_array[i].pos.x)/distance;
    		double force_y = gravitional_force * (mouse_position.y - star_array[i].pos.y)/distance;
			
			star_array[i].velocity_x = star_array[i].velocity_x + ((force_x/star_array[i].pos.x) * DELTA_TIME);
			star_array[i].velocity_y = star_array[i].velocity_y + ((force_y/star_array[i].pos.y) * DELTA_TIME);

		}
        star_array[i].pos.x = star_array[i].pos.x + star_array[i].velocity_x * DELTA_TIME * FRICTION;
        star_array[i].pos.y = star_array[i].pos.y + star_array[i].velocity_y * DELTA_TIME * FRICTION;
		
	}
}

double euclidean_distance(Vector2 pos1, Vector2 pos2) {
	double dx = pos2.x - pos1.x;
	double dy = pos2.y - pos1.y;
	return sqrt(dx * dx + dy * dy);
}

int main() {
	InitWindow(WIDTH, HEIGHT, "Render");
	SetTargetFPS(60);
	init_array();
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BLACK);
			//DrawFPS(0, 0);
			draw_pixels();
			update_position();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
