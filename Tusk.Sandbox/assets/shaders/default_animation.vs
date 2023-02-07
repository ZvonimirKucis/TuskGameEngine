#version 330 core
const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 4) in ivec3 aJointIndices;
layout (location = 5) in vec3 aWeights;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 jointTransforms[MAX_JOINTS];

void main() {
    vec4 totalLocalPos = vec4(0.0);
    
    for(int i = 0; i < MAX_WEIGHTS; i++) {
        mat4 jointTransform = jointTransforms[aJointIndices[i]];
        vec4 posePosition = jointTransform * vec4(aPos, 1.0);
        totalLocalPos += posePosition * aWeights[i];
    }

    TexCoords = aTexCoords; 

    gl_Position = projection * view * model * totalLocalPos; //vec4(aPos, 1.0);
}