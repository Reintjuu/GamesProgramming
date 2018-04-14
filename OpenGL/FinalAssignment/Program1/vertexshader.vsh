#version 430 core

// Uniform matrices
uniform mat4 mv;
uniform mat4 projection;
uniform vec3 lightPos;

// Per-vertex inputs
in vec3 position;
in vec3 normal;
in vec2 uv;

out VS_OUT
{
   vec3 N;
   vec3 L;
   vec3 V;
} vs_out;
out vec2 UV;

void main()
{
    // Calculate view-space coordinate
    vec4 P = mv * vec4(position, 1.0);

    // Calculate normal in view-space
    vs_out.N = mat3(mv) * normal;

    // Calculate light vector
    vs_out.L = lightPos - P.xyz;

    // Calculate view vector;
    vs_out.V = -P.xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = projection * P;

    // Pass UV
    UV = uv;
}