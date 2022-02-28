#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_position;
in vec3 frag_color;
in vec2 frag_texture;
in vec3 frag_normal;

// Output

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec3 out_texture;
layout(location = 2) out vec4 out_normal;


void main()
{
    // TODO(student): Write pixel out color
    out_color	= vec4(frag_color, 1.f);
	out_texture = vec3(frag_texture, 1.f);
	out_normal	= vec4(frag_normal, 1.f);
}