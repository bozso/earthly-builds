#include <flecs.h>

typedef struct {
    float x;
    float y;
} Position, Velocity;

void Move(ecs_iter_t *it)
{
    Position *p = ecs_column(it, Position, 1);
    Velocity *v = ecs_column(it, Velocity, 2);
  
    for (int i = 0; i < it->count; i ++) {
        p[i].x += v[i].x * it->delta_time;
        p[i].y += v[i].y * it->delta_time;
        printf("Entity %s moved!\n", ecs_get_name(it->world, it->entities[i]));
    }
}

int main(int argc, char *argv[])
{
    ecs_world_t *ecs = ecs_init();

    ECS_COMPONENT(ecs, Position);
    ECS_COMPONENT(ecs, Velocity);

    ECS_SYSTEM(ecs, Move, EcsOnUpdate, Position, [in] Velocity);

    ecs_entity_t e = ecs_set(ecs, 0, EcsName, {"MyEntity"});
    ecs_set(ecs, e, Position, {0, 0});
    ecs_set(ecs, e, Velocity, {1, 1});

    while (ecs_progress(ecs, 0)) { }
}
