#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "geometry.h"
#include "image.h"

typedef vec4f_t vertex_shader_t(int nth_vertex, void *varyings, void *uniforms);
typedef void interp_varyings_t(vec3f_t weights, void *varyings);
typedef color_t fragment_shader_t(void *varyings, void *uniforms);

typedef struct {
    image_t *framebuffer;
    float *depthbuffer;
    mat4f_t viewport;
} context_t;

typedef struct {
    vertex_shader_t *vertex_shader;
    fragment_shader_t *fragment_shader;
    interp_varyings_t *interp_varyings;
    void *varyings;
    void *uniforms;
} program_t;

/* common matrices */
mat4f_t gfx_lookat_matrix(vec3f_t eye, vec3f_t center, vec3f_t up);
mat4f_t gfx_projection_matrix(vec3f_t eye, vec3f_t center);
mat4f_t gfx_viewport_matrix(int x, int y, int width, int height);

/* triangle rasterization */
void gfx_draw_triangle(context_t *context, program_t *program);

/* context management */
context_t *gfx_create_context(int width, int height);
void gfx_release_context(context_t *context);
void gfx_clear_buffers(context_t *context);

/* texture sampling */
color_t gfx_sample_texture(image_t *texture, float u, float v);
color_t gfx_sample_diffuse(image_t *diffuse_map, float u, float v);
vec3f_t gfx_sample_normal(image_t *normal_map, float u, float v);
float gfx_sample_specular(image_t *specular_map, float u, float v);

/* vector interpolation */
vec2f_t gfx_interp_vec2f(vec2f_t vs[3], vec3f_t weights);
vec3f_t gfx_interp_vec3f(vec3f_t vs[3], vec3f_t weights);
vec4f_t gfx_interp_vec4f(vec4f_t vs[3], vec3f_t weights);

#endif
