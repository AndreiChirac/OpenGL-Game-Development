#version 330
#define Z 932

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 v_normal;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

// Output
// TODO(student): Output values to fragment shader

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

float noise(in vec3 co){
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233,144.7272))) * 43758.5453);
}

void main()
{
    // TODO(student): Send output to fragment shader
    frag_position = v_position;
	frag_color = object_color;
	frag_texture = tex_coord;
	frag_normal = v_normal;

    vec3 posistion = v_position;
    vec3 stp = v_position;
    float acum = 0;

    for (int i = 0; i < 20; i++ ) {
        acum += noise(stp);
    }
    posistion = v_position * acum /15 * (1, 2, 1);

	vec3 help_color =  mix(vec3(0.78, 0.55, 0.55), vec3(0, 0.55, 0.55), acum / 6) * 0.67;
    frag_color =  mix(help_color, vec3(0, 0.55, 0.55), acum / 7);

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(posistion, 1.0);
}
