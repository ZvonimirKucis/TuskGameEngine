#version 330 core
const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texCoords;
layout (location = 4) in ivec3 in_jointIndices;
layout (location = 5) in vec3 in_weights;

out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 jointTransforms[MAX_JOINTS];

void main() {
    vec4 totalLocalPos = vec4(0.0);
    
    for(int i = 0; i < MAX_WEIGHTS; i++) {
        mat4 jointTransform = jointTransforms[in_jointIndices[i]];
        vec4 posePosition = jointTransform * vec4(in_position, 1.0);
        totalLocalPos += posePosition * in_weights[i];
    }

    texCoords = in_texCoords;
    normal = normalize(mat3(transpose(inverse(view * model))) * in_normal);
    fragPos = vec3(view * model * totalLocalPos);

    gl_Position = projection * view * model * totalLocalPos;
}